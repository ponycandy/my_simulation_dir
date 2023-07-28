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
    xmlreader.xmlRead("obs_num",obs_num);
    common_initialize(var_struct);
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

ifopt::Component::VectorXd Obs_Avoidence::GetValues() const
{
    m_jac.setZero();
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);

    //第一步，预测未来时刻的所有最近点
    predict_beta_agent();
    //第二步，约束最近点到目标点的最小值
    double error=0;
    int m=0;
    for(int steps=0;steps<decnum;steps++)//N为预测的总长度
    {
        error=0.1;
        for(int j=0;j<agentnum;j++)
        {
            single_vehicle_data *vehicleN=var_struct.steps[steps]->agents[j];
            if(vehicleN->betaAgentNum>0)
            {
                BetaAgent *newbeta=vehicleN->clsp[0];
                double distance=pow((newbeta->posxy-vehicleN->posxy).norm(),2);
                error=distance-collision_r*collision_r;
                g(m)=error;
                m_jac(m,var_struct.steps[steps]->agents[j]->indexofx)=2*(var_struct.steps[steps])->agents[j]->x-2*newbeta->x;
                m_jac(m,var_struct.steps[steps]->agents[j]->indexofy)=2*(var_struct.steps[steps])->agents[j]->y-2*newbeta->y;

            }
            else
            {
                g(m)=error;


            }
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
        b.at(i-1)=ifopt::BoundGreaterZero;
    }

    return b;
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
        for(int j=1;j<=obs_num;j++)
        {
            SwarmObstacle *obs=obsbounding_group.value(j);
            for(int i=0;i<agentnum;i++)
            {
                single_vehicle_data * vehicleN=var_struct.steps[k]->agents[i];
                vehicleN->betaAgentNum=0;
                collison_result result=m_service->polygen_circle_detect(vehicleN->x,
                                                                          vehicleN->y,collision_r,obs->vertex_map);
                if(result.flag==1)
                {
                    vehicleN->clsp[0]->x=result.closest_point.x;
                    vehicleN->clsp[0]->y=result.closest_point.y;
                    vehicleN->clsp[0]->posxy<<result.closest_point.x,result.closest_point.y;
                    vehicleN->betaAgentNum=1;
                    //Eigen probelm
                }
            }
        }
    }

}
