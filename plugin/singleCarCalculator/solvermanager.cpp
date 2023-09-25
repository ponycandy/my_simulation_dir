#include "solvermanager.h"
#include "singleCarCalculatorActivator.h".h"
#include "xmlcore.h"
Solvermanager::Solvermanager()
{
    m_solver=singleCarCalculatorActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_decode=singleCarCalculatorActivator::getService<CPYcoderservice>("CPYcoderservice");
    xmlCore xmlreader("./config/DistributedMPC/swarm.xml");
    xmlreader.xmlRead("selfID",selfID);
    xmlreader.xmlRead("decnum",decnum);
    int portnum;
    cached_control.resize(2,1);
    cached_control<<1,0;
    std::string Ip;
    xmlreader.xmlRead("portnum_self",portnum);
    xmlreader.xmlRead("IP",Ip);
    xmlreader.xmlRead("shiftgate",shiftgate);
    m_decode=m_decode->cloneservice();
    m_decode->Client_mode_connect(QString::fromStdString(Ip),portnum);
    m_decode->Bind_Slot(this,SLOT(solvenow(Eigen::MatrixXd)));

    ode=new Swarm_ODE;
    Jac=new Jacobiancalc;

    m_solver->registerODE(ode);
    Eigen::MatrixXd agent_mat;
    agent_mat.resize(1,3);
    Eigen::MatrixXd initstate;
    initstate.resize(3*1,1);
    initstate.setZero();
    Eigen::MatrixXd terminalstate=initstate;
    //展平agentmat作为initstate的值
    m_solver->registerODEJacob(Jac);
    m_solver->init_state(initstate,terminalstate);
    m_solver->init_num(1*3,1*2,decnum);
    m_solver->init_steptime(30*0.001);//此处时间单位为秒
    m_solver->setuseterminal(false);
    m_solver->Use_BuildIn_Dynamics_Cons(true);
    Eigen::MatrixXd lowerbound;
    Eigen::MatrixXd higherbound;
    lowerbound.resize(2,1);
    lowerbound<<0,-2;
    higherbound.resize(2,1);
    higherbound<<2.5,2;
    m_solver->set_control_bound(lowerbound,higherbound);
    cached_x.resize(5*decnum,1);
    cached_x.setRandom();
    initflag=0;
    costset=new minimize_Topology("minimize_Topology");

}

void Solvermanager::optimize(Eigen::MatrixXd &input, Eigen::MatrixXd &output)
{


    //1.预测邻居的未来轨迹
    int totalnum=input(0,0);//这个neib包含所有的对象
    int obsPointnum=input(0,1);
    Eigen::MatrixXd selfinitstate;
    Eigen::MatrixXd xinitial;
    selfinitstate.resize(3,1);
    xinitial.resize(5*decnum,1);
    selfinitstate<<input(selfID,1),input(selfID,2),input(selfID,3);
    costset->selfinitstate=selfinitstate;
    costset->obs_num=obsPointnum;
    costset->ObstripR.resize(obsPointnum,5);
    costset->ObstripR.setZero();
    for(int j=1;j<=obsPointnum;j++)
    {
        costset->ObstripR(j-1,0)=input(totalnum+j,0);
        costset->ObstripR(j-1,1)=input(totalnum+j,1);
        costset->ObstripR(j-1,2)=3;//设计的回避半径,应该足够看出回避效果了
        costset->ObstripR(j-1,3)=input(totalnum+j,2);//速度x
        costset->ObstripR(j-1,4)=input(totalnum+j,3);//速度y
    }

    costset->PredictMat.resize(3*totalnum,decnum);//包含所有对象的预测
    costset->totalNum=totalnum;
    for(int j=1;j<=totalnum;j++)
    {
        double x=input(j,1);
        double y=input(j,2);
        double phi=input(j,3);
        double vel=input(j,4);
        double omega=input(j,5);
        for(int i=0;i<decnum;i++)
        {
            x+=vel*cos(phi)*0.03;
            y+=vel*sin(phi)*0.03;
            phi+=omega*0.03;
            costset->PredictMat(3*(j-1),i)=x;
            costset->PredictMat(3*(j-1)+1,i)=y;
            costset->PredictMat(3*(j-1)+2,i)=input(j,6);//该值等于0表示不是拓朴邻居
            if(j>selfID)
            {
                //尝试把目标的轨迹作为初始优化点
                xinitial(5*i+0)=vel;
                xinitial(5*i+1)=omega;
                xinitial(5*i+2)=x;
                xinitial(5*i+3)=y;
                xinitial(5*i+4)=phi;
            }
        }

    }

    if(initflag==0)
    {
        std::shared_ptr<ifopt::ConstraintSet> consptr2(costset);
        m_solver->AddCostSet(consptr2);
        m_solver->constructNLP();
        initflag=1;
    }
    Eigen::MatrixXd noise;
    noise=xinitial;
    noise.setRandom();
    xinitial+=noise;
    for(int i=0;i<decnum-1;i++)
    {
        for(int index=0;index<5;index++)
        {
            cached_x(5*decnum-i*5-index-1-5,0)= cached_x(5*decnum-i*5-index-1,0);
        }
    }
    //数组左移
    cached_x.setRandom();//防止上一时刻错误值侵犯
    std::shared_ptr<Eigen::MatrixXd> initptr = std::make_shared<Eigen::MatrixXd>(cached_x);
    //看来，解太过于接近目标也不行
    m_solver->ReinitState(selfinitstate,selfinitstate);
    m_solver->init_all_x(0,initptr);
    //好的，现在将预测轨迹输入到x的所有初始值中
    int status=0;
    status=m_solver->crack_and_return();

    if (status ==-1 || status ==-2)
    {
        //超出循环数或者无解restoration failed
        //这个情况下，直接返回之前一个循环的速度和角速度
        output=cached_control.eval();
        return;
    }
    if (status == 0)
    {
        printf("\n\n*** The problem was successfully solved!\n");
        //这里还需要识别local minimum的情况
        //也就是虽然接出来最优，但是无法维持编队的情况
        //一个可行方法是观测cost，如果cost过大，说明就是局部最优
        //这个时候切换到传统控制方法
        if(costset->costNow>shiftgate)//这个判定的参数需要仔细调节
        {
            TradintionControl(output,input);
//            output=cached_control.eval();
            return;
        }
        else
        {
            Eigen::MatrixXd temp=m_solver->get_actMat();
            m_solver->GetVariable("action_state_set1",cached_x);

            //    double cost=costset->GetCost();
            output=temp.block(0,0,2,1);
            //        cached_control=output.eval();
            return;
        }
    }
    if (status == -2) //restoration failed
    {
        printf("\n\n*** The problem was successfully solved!\n");
        Eigen::MatrixXd temp=m_solver->get_actMat();
        m_solver->GetVariable("action_state_set1",cached_x);

        //    double cost=costset->GetCost();
        output=temp.block(0,0,2,1);
        //        cached_control=output.eval();
        return;
    }

}

void Solvermanager::TradintionControl(Eigen::MatrixXd &control, Eigen::MatrixXd &input)
{
    //按照课本设计传统控制率就行了
    control.setZero();
    //1.斥力
    Eigen::MatrixXd avergae_vel;
    Eigen::MatrixXd act_vector_2ndorder;
    Eigen::MatrixXd act_vector_1storder;
    Eigen::MatrixXd veltemp;
    Eigen::MatrixXd postemp;
    Eigen::MatrixXd posself;
    Eigen::MatrixXd velself;
    Eigen::MatrixXd concencus;
    Eigen::MatrixXd gradient_term;
    double angleerror=0;
    avergae_vel.resize(2,1);
    avergae_vel.setZero();
    veltemp=avergae_vel;
    postemp=avergae_vel;
    posself=avergae_vel;
    concencus=avergae_vel;
    gradient_term=avergae_vel;
    velself=avergae_vel;
    act_vector_2ndorder=avergae_vel;
    act_vector_1storder=avergae_vel;

    avergae_vel<<input(selfID,4)*cos(input(selfID,3)),input(selfID,4)*sin(input(selfID,3));
    posself<<input(selfID,1),input(selfID,2);
    angleerror=normalize(input(selfID,3)-input(costset->totalNum,3));
    velself=avergae_vel;
    for(int j=1;j<=costset->totalNum;j++)//总agent数目
    {
        if(j!=selfID)//非自己
        {

            if(input(j,6)!=0)//等于0则不是邻居关系，跳过
            {
                double distance=input(j,6);
                veltemp<<input(j,4)*cos(input(j,3)),input(j,4)*sin(input(j,3));
                postemp<<input(j,1),input(j,2);
                avergae_vel+=veltemp;
                Eigen::MatrixXd n_ij=postemp-posself;
                concencus+=veltemp-velself;
                double norm_2=n_ij.norm();
                qDebug()<<norm_2-distance;
                Eigen::MatrixXd grad=(norm_2-distance)*n_ij.normalized();
                gradient_term+=10*grad;
            }
        }


    }

    act_vector_1storder=(gradient_term);
    act_vector_2ndorder=(concencus+gradient_term);
    control(0,0)=act_vector_1storder(0,0)*cos(input(selfID,3))+act_vector_1storder(1,0)*sin(input(selfID,3));
    //第一个控制量
    double dux=act_vector_2ndorder(0,0);
    double duy=act_vector_2ndorder(1,0);
    double ux=act_vector_1storder(0,0);
    double uy=act_vector_1storder(1,0);
    double targetangle=get_angle(ux,uy);
    angleerror=normalize(input(selfID,3)-targetangle);
    double dthetadi=0;
    if(ux==uy && ux==0)
    {
        dthetadi=0;
    }
    else
    {
        dthetadi=duy*ux/(pow(ux,2)+pow(uy,2))
                   -dux*uy/(pow(ux,2)+pow(uy,2));
    }

    control(1,0)=-4*angleerror;

}
void Solvermanager::solvenow(Eigen::MatrixXd targetmat)
{

    Eigen::MatrixXd solution;
    solution.resize(2,1);
    solution<<1,0;
    optimize(targetmat,solution);
    m_decode->sendMAT(solution);
}

