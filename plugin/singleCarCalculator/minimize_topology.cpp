#include "minimize_topology.h"


#include <Eigen/Sparse>

minimize_Topology::minimize_Topology(std::string name):ifopt::CostTerm(name)
{
    xmlCore xmlreader("./config/DistributedMPC/swarm.xml");
    //我们是需要更改代码去适配的，这就是下午的工作
    xmlreader.xmlRead("agent_num",agentnum);
    //这里的agentnum用来初始化拓扑图
    //卧槽，要改的还不少
    xmlreader.xmlRead("decnum",decnum);


    totalNum=agentnum;

    actMat.resize(2,decnum);
    stateMat.resize(3,decnum);
    m_jac.resize(1,5*decnum);
    m_Hession.resize(5*decnum,5*decnum);
    TriggerSur=1;
    costNow=0;
}


double minimize_Topology::GetCost() const
{
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    m_jac.setZero();
    m_Hession.setZero();
    //初始化
    double error=0;
    double koef=0.3;
    pack_variable(x,5,decnum,2,3,actMat,stateMat);
    //第一，最小控制量
    for(int steps=0;steps<decnum;steps++)
    {
        double c1=0.8;double c2=0.7;//把这一项搞到近似为0，看一下？
        error+= c1*(actMat(0,steps)*actMat(0,steps)+c2*actMat(1,steps)*actMat(1,steps));
        //填充一阶导数
        m_jac(0,steps*5+0)=2*c1*actMat(0,steps);
        m_jac(0,steps*5+1)=2*c2*actMat(1,steps);
        //填充二阶导数
        m_Hession(steps*5+0,steps*5+0)=2*c1;
        m_Hession(steps*5+1,steps*5+1)=2*c2;

    }
    //第二避障项,z的大小决定目标追踪任务是否执行
    int TargetTrackingflag=0;
    //可以的，这一项决定项，在前几个iter里面表现得还行
    //需要规定最大iteration，然后根据返回值，如果没有得到最优解，就按照先前的方式运行
    for(int steps=0;steps<decnum;steps++)
    {
        for(int io=1;io<=obs_num;io++)
        {
            obspos<<ObstripR(io-1,0),ObstripR(io-1,1);//障碍物位置
            double colliR=ObstripR(io-1,2);//障碍物等效半径

            Eigen::MatrixXd posself;
            posself.resize(2,1);
            posself=stateMat.block(0,steps,2,1);
            double z=pow((posself-obspos).norm()/colliR,2);
            if(z<0.5)
            {
                TargetTrackingflag=1;//只要有一个时刻，一个障碍物触发了此项，就会不考虑维持拓扑
            }

            double first,second;
            double coef=1;//避障完全无反应！！
            double value=PotentialCalc(z,first,second);
            error+=(coef*value);
            //可以考虑把势场换成更光滑的cos对底函数

            //不行,比起光滑,更重要的是保证目标函数是凸的

            double Dzdx=2/(colliR*colliR)*(posself(0,0)-obspos(0,0));
            double Dzdy=2/(colliR*colliR)*(posself(1,0)-obspos(1,0));

            m_jac(0,5*steps+2)+=coef*first*Dzdx;
            m_jac(0,5*steps+3)+=coef*first*Dzdy;
            if(z<1)
            {
                double valuex =2/(colliR*colliR)*first+second*pow(Dzdx,2);
                double valuey =2/(colliR*colliR)*first+second*pow(Dzdy,2);
                double valuexy =second*Dzdx*Dzdy;
                fillsymetrix(m_Hession,5*steps+2,5*steps+2,
                             coef*valuex);
                fillsymetrix(m_Hession,5*steps+3,5*steps+3,
                             coef*valuey);
                fillsymetrix(m_Hession,5*steps+2,5*steps+3,
                             coef*valuexy);
                //他们是连续的
            }
        }
    }
    //第三，最小化未来拓扑
    koef=0.3;
    if(TargetTrackingflag==0)
    {

        for(int j=0;j<totalNum;j++)
        {
            int ID=j+1;
            //我们希望优先追踪leader
            if(ID==agentnum)
            {
                koef=0.1;
            }
            else
            {
                koef=0.3;
            }
            double length=PredictMat(3*(ID-1)+2,0);//拓扑图邻居
            if(length>0)
            {
                for(int steps=0;steps<decnum;steps++)
                {

                    double Dis=pow((stateMat.block(0,steps,2,1)-PredictMat.block(3*(ID-1),steps,2,1)).norm(),2)-length*length;
                    double xi=stateMat(0,steps);
                    double yi=stateMat(1,steps);
                    double xj=PredictMat(3*(ID-1),steps);
                    double yj=PredictMat(3*(ID-1)+1,steps);
                    error+=(Dis*Dis)/(koef);
                    //填充一阶导数
                    m_jac(0,5*steps+2)+=4*Dis*((xi-xj)/(koef));
                    m_jac(0,5*steps+3)+=4*Dis*((yi-yj)/(koef));
                    //填充二阶导数
                    fillsymetrix(m_Hession,5*steps+2,5*steps+2,2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));
                    fillsymetrix(m_Hession,5*steps+3,5*steps+3,2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));
                    fillsymetrix(m_Hession,5*steps+2,5*steps+3,2/koef*(4*(xi-xj)*(yi-yj)));//xiyi
                    //it's really error prone!
                }
            }
        }
    }
    //可能需要包含速度一致项,也就是说，尽量减小agent之间的速度差或者方向差
    //更确切的来说，是到leader的速度方向差，
    //尽量为凸！！

    //备用项,追踪障碍物环绕
    if(TriggerSur==1)
    {
        koef=0.005;
        Eigen::MatrixXd predict;
        predict.resize(2,decnum);
        predict.setZero();
        for(int io=1;io<=obs_num;io++)
        {
            get_predicted_value(io, predict);
            for(int steps=0;steps<decnum;steps++)
            {

                double Dis=pow((stateMat.block(0,steps,2,1)-predict.block(0,steps,2,1)).norm(),2);
                double xi=stateMat(0,steps);
                double yi=stateMat(1,steps);
                double xj=predict(0,steps);
                double yj=predict(1,steps);

                error+=(Dis*Dis)/(koef);
                //填充一阶导数
                m_jac(0,5*steps+2)+=4*Dis*((xi-xj)/(koef));
                m_jac(0,5*steps+3)+=4*Dis*((yi-yj)/(koef));
                //填充二阶导数
                fillsymetrix(m_Hession,5*steps+2,5*steps+2,2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));
                fillsymetrix(m_Hession,5*steps+3,5*steps+3,2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));
                fillsymetrix(m_Hession,5*steps+2,5*steps+3,2/koef*(4*(xi-xj)*(yi-yj)));//xiyi
                //it's really error prone!

                //第二部分,提高速度一致性
                //                double vxself=actMat(0,steps)*cos(stateMat(2,steps));
                //                double vyself=actMat(0,steps)*sin(stateMat(2,steps));

            }
        }


    }
    costNow=error;
    return error;
}

void minimize_Topology::get_predicted_value(int OBSID, Eigen::MatrixXd &predictMat) const
{
    predictMat.resize(2,decnum);
    predictMat.setZero();

    Eigen::MatrixXd obsvel;
    obsvel=obspos;
    obsvel.setZero();


    int io=OBSID;
    obspos<<ObstripR(io-1,0),ObstripR(io-1,1);//障碍物位置
    obsvel<<ObstripR(io-1,3),ObstripR(io-1,4);//障碍物速度

    double x=selfinitstate(0,0);
    double y=selfinitstate(1,0);
    double vel_x=obsvel(0,0);
    double vel_y=obsvel(1,0);
    //速度和方向一致性....
    for(int i=0;i<decnum;i++)
    {
        x+=vel_x*0.1;
        y+=vel_y*0.1;

        predictMat(0,i)=x;
        predictMat(1,i)=y;
    }

}

void minimize_Topology::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{
    GetCost();
    jac_block=m_Hession.sparseView();
    //最好用copy的方式,不然容易导致内存故障
}

void minimize_Topology::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    GetCost();
    jac=m_jac.sparseView();
}

