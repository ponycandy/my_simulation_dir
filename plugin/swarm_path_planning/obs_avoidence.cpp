#include "obs_avoidence.h"

#include "include/GL_2D/GL2Dcommon.h"
#include "swarm_path_planningActivator.h"
Obs_Avoidence::Obs_Avoidence(int num, std::string name):ifopt::ConstraintSet(num,name)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");
    constrainnum = num;
    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("collision_r",collision_r);
    xmlreader.xmlRead("communication_range",communication_range);
    xmlreader.xmlRead("maximumPotential",maximumPotential);
    xmlreader.xmlRead("obs_num",obs_num);
    common_initialize(var_struct);
    m_Hession.resize(5*agentnum*decnum,5*agentnum*decnum);
    for(int i=0;i<constrainnum;i++)
    {
        Hession_Tensor.push_back(m_Hession);
    }
    actMat.resize(2*agentnum,decnum);
    stateMat.resize(3*agentnum,decnum);
    m_service=swarm_path_planningActivator::getService<CollisionDetectservice>("CollisionDetectservice");
    //初始化场景障碍物
    Eigen::MatrixXd obs_mat;
    for(int i=1;i<=obs_num;i++)
    {
        SwarmObstacle *new_obs=new SwarmObstacle;
        QString obs_term_name="OBS_"+QString::number(i)+"_vertexnum";
        xmlreader.xmlRead(obs_term_name.toStdString(),new_obs->vertex_num);
        new_obs->ID=i;
        obs_mat.resize(new_obs->vertex_num,2);
        obs_term_name="OBS_"+QString::number(i)+"_vertexparams";
        std::vector<double> point_x_vec;
        std::vector<double> point_y_vec;
        xmlreader.xmlRead(obs_term_name.toStdString(),obs_mat);
        for(int j=1;j<=new_obs->vertex_num;j=j+1)
        {
            double x= obs_mat(j-1,0);
            double y= obs_mat(j-1,1);
            point_x_vec.push_back(x);
            point_y_vec.push_back(y);
            new_obs->vertex_map<<QPointF(x,y);
        }

        obsbounding_group.insert(i,new_obs);
    }
    m_jac.resize(constrainnum,5*agentnum*decnum);

}

double Obs_Avoidence::PotentialCalc(double z, double &first, double &second) const
{
    double output;
    if (z<1)
    {
        output=-pow((z-1),3);
        first =-3*pow((z-1),2);
        second =-6*(z-1);
    }
    else
    {
        output=0;
        first =0;
        second =0;
    }
    return output;
}

ifopt::Component::VectorXd Obs_Avoidence::GetValues() const
{
    m_Hession.setZero();
    m_jac.setZero();
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);

    //第一步，预测未来时刻的所有最近点
    predict_beta_agent();
    //第二步，约束单个点的每个时刻的总势能小于某个值
    double potential=0;
    double first;
    double second;
    double Dzdx=0;
    double Dzdy=0;
    int m=0;
    for(int steps=0;steps<decnum;steps++)//N为预测的总长度
    {
        m_Hession.setZero();
        for(int j=0;j<agentnum;j++)
        {
            single_vehicle_data *vehicleN=var_struct.steps[steps]->agents[j];
            potential=0;
            for (int i = 0; i < vehicleN->clsp.size(); i++)
            {
                BetaAgent *agent = vehicleN->clsp[i];
                double z=pow((agent->posxy-vehicleN->posxy).norm()/communication_range,2);
                potential+=(PotentialCalc(z,first,second));
                Dzdx=2/(communication_range*communication_range)*(vehicleN->x-agent->x);
                Dzdy=2/(communication_range*communication_range)*(vehicleN->y-agent->y);

                m_jac(m,vehicleN->indexofx)+=first*Dzdx;
                m_jac(m,vehicleN->indexofy)+=first*Dzdy;
                if(z<1)
                {
                    double valuex =
                        -6/(communication_range*communication_range)*(z-1)*
                        (4/(communication_range*communication_range)*pow(vehicleN->x-agent->x,2)
                         +(z-1));
                    double valuey =
                        -6/(communication_range*communication_range)*(z-1)*
                        (4/(communication_range*communication_range)*pow(vehicleN->y-agent->y,2)
                         +(z-1));
                    double valuexy =-24/(pow(communication_range,4))*
                                     (z-1)*(vehicleN->y-agent->y)*(vehicleN->x-agent->x);
                    fillsymetrix(m_Hession,vehicleN->indexofx,vehicleN->indexofx,
                                 valuex);
                    fillsymetrix(m_Hession,vehicleN->indexofy,vehicleN->indexofy,
                                 valuey);
                    fillsymetrix(m_Hession,vehicleN->indexofx,vehicleN->indexofy,
                                 valuexy);
                }
            }

            Hession_Tensor[m]=m_Hession;
            g(m)=potential-maximumPotential;

            m++;
        }
    }
    //碰撞约束完成,雅可比计算相对比较简单，就不用Tensor了
    return g;
}

ifopt::Component::VecBound Obs_Avoidence::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=constrainnum;i++)
    {
        b.at(i-1)=ifopt::BoundSmallerZero;
    }

    return b;
}

void Obs_Avoidence::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{
    GetValues();
    jac_block=Hession_Tensor[irow].sparseView();
}

void Obs_Avoidence::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    GetValues();
    jac_block=m_jac.sparseView();
}

void Obs_Avoidence::predict_beta_agent() const
{
    for(int k=0;k<decnum;k++)
    {
        for(int i=0;i<agentnum;i++)
        {
            single_vehicle_data * vehicleN=var_struct.steps[k]->agents[i];
            vehicleN->betaAgentNum=0;
            vehicleN->clsp.clear();
            for(int j=1;j<=obs_num;j++)
            {
                //初始化的轨迹不能够在障碍物内部
                SwarmObstacle *obs=obsbounding_group.value(j);



                collison_result result=m_service->polygen_circle_detect(vehicleN->x,
                                                                          vehicleN->y,collision_r,obs->vertex_map);
                if(result.flag==1)
                {
                    BetaAgent *newbeta=new BetaAgent;
                    newbeta->x=result.closest_point.x;
                    newbeta->y=result.closest_point.y;
                    newbeta->posxy<< newbeta->x, newbeta->y;

                    vehicleN->clsp.push_back(newbeta);



                    vehicleN->betaAgentNum+=1;
                    //Eigen probelm
                    //默认只有一个障碍物
                    //多个障碍物取势能总和
                    //然后总势能必须小于一个值
                    //因为势能函数是二阶连续的，这样优化就会简单很多
                }
            }
        }
    }

}
