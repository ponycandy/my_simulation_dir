#include "minimize_topology.h"


minimize_Topology::minimize_Topology(std::string name):ifopt::CostTerm(name)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");
    obspos<<7.5,12;
    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("Incp",Incp);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("collision_r",collision_r);
    xmlreader.xmlRead("communication_range",communication_range);


    common_initialize(var_struct);
    initilize_Traj(Target_Traj);
    actMat.resize(2*agentnum,decnum);
    stateMat.resize(3*agentnum,decnum);
    m_jac.resize(1,5*agentnum*decnum);
    m_Hession.resize(5*agentnum*decnum,5*agentnum*decnum);

}

double minimize_Topology::GetCost() const
{
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    m_jac.setZero();
    m_Hession.setZero();
    //这才是组队距离

    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);
    double error=0;
    double koef=100*agentnum*decnum;
    for(int steps=0;steps<decnum;steps++)
    {
        for(int i=0;i<agentnum;i++)
        {
            //agent_num最后一个agent是leader需要追踪预测出来的目标轨迹
            if(i!=agentnum-1)
            {
                int edge_num=(var_struct.steps[steps])->agents[i]->edgenum;
                for(int j=0;j<edge_num;j++)
                {
                    int ID=var_struct.steps[steps]->agents[i]->Edg[j]->End_Node_ID;
                    double length=var_struct.steps[steps]->agents[i]->Edg[j]->length;
                    single_vehicle_data *neib=var_struct.steps[steps]->agents[ID-1];
                    double Dis=pow((var_struct.steps[steps]->agents[i]->posxy-neib->posxy).norm(),2)-length*length;
                    double xi=var_struct.steps[steps]->agents[i]->posxy(0,0);
                    double yi=var_struct.steps[steps]->agents[i]->posxy(1,0);
                    double xj=neib->posxy(0,0);
                    double yj=neib->posxy(1,0);
                    error+=(Dis*Dis)/(koef);

                    m_jac(0,var_struct.steps[steps]->agents[i]->indexofx)+=4*Dis*((var_struct.steps[steps])->agents[i]->x-neib->x)/(koef);
                    m_jac(0,var_struct.steps[steps]->agents[i]->indexofy)+=4*Dis*((var_struct.steps[steps])->agents[i]->y-neib->y)/(koef);
                    m_jac(0,var_struct.steps[steps]->agents[ID-1]->indexofx)+=4*Dis*(-(var_struct.steps[steps])->agents[i]->x+neib->x)/(koef);
                    m_jac(0,var_struct.steps[steps]->agents[ID-1]->indexofy)+=4*Dis*(-(var_struct.steps[steps])->agents[i]->y+neib->y)/(koef);
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 var_struct.steps[steps]->agents[i]->indexofx,
                                 2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 neib->indexofx,
                                 2/koef*(-4*(xi-xj)*(xi-xj)-2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[ID-1]->indexofx,
                                 var_struct.steps[steps]->agents[ID-1]->indexofx,
                                 2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));

                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofy,
                                 var_struct.steps[steps]->agents[i]->indexofy,
                                 2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofy,
                                 var_struct.steps[steps]->agents[ID-1]->indexofy,
                                 2/koef*(-4*(yi-yj)*(yi-yj)-2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[ID-1]->indexofy,
                                 var_struct.steps[steps]->agents[ID-1]->indexofy,
                                 2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));

                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 neib->indexofy,
                                 2/koef*(4*(xi-xj)*(yj-yi))); //xiyj
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 var_struct.steps[steps]->agents[i]->indexofy,
                                 2/koef*(4*(xi-xj)*(yi-yj)));//xiyi
                    fillsymetrix(m_Hession,neib->indexofx,
                                 neib->indexofy,
                                 2/koef*(4*(xj-xi)*(yj-yi)));//xjyj
                    fillsymetrix(m_Hession,neib->indexofx,
                                 var_struct.steps[steps]->agents[i]->indexofy,
                                 2/koef*(4*(xj-xi)*(yi-yj)));//xjyi
                    //it's really error prone!
                }
            }
            else
            {
                single_vehicle_data *leader=var_struct.steps[steps]->agents[i];
                Eigen::Vector2d postarget=Target_Traj[steps];
                double Dis=pow((var_struct.steps[steps]->agents[i]->posxy-postarget).norm(),2)-Incp*Incp;
                double xi=leader->posxy(0,0);
                double yi=leader->posxy(1,0);
                double xj=postarget(0,0);
                double yj=postarget(1,0);
                error+=(Dis*Dis)/(koef);

                m_jac(0,leader->indexofx)+=4*Dis*((xi-xj)/(koef));
                m_jac(0,leader->indexofy)+=4*Dis*((yi-yj)/(koef));

                //xixi
                fillsymetrix(m_Hession,leader->indexofx,
                             leader->indexofx,
                             2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));
                //yiyi
                fillsymetrix(m_Hession,leader->indexofy,
                             leader->indexofy,
                             2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));

                //xiyi
                fillsymetrix(m_Hession,leader->indexofx,
                             leader->indexofy,
                             2/koef*(4*(xi-xj)*(yi-yj)));//xiyi

                //作为leader的目标是减小和目标物体轨迹的差距
            }
            //下面添加对障碍物避障的最小项
            single_vehicle_data *agent=(var_struct.steps[steps])->agents[i];
            double z=pow((agent->posxy-obspos).norm()/communication_range,2);
            double first,second;

            //            potential+=(PotentialCalc(z,first,second));

            error+=(20*PotentialCalc(z,first,second));

            double Dzdx=2/(communication_range*communication_range)*(agent->x-obspos(0,0));
            double Dzdy=2/(communication_range*communication_range)*(agent->y-obspos(1,0));

            m_jac(0,agent->indexofx)+=20*first*Dzdx;
            m_jac(0,agent->indexofy)+=20*first*Dzdy;
            if(z<1)
            {
                double valuex =
                    -6/(communication_range*communication_range)*(z-1)*
                    (4/(communication_range*communication_range)*pow(agent->x-obspos(0,0),2)
                     +(z-1));
                double valuey =
                    -6/(communication_range*communication_range)*(z-1)*
                    (4/(communication_range*communication_range)*pow(agent->y-obspos(1,0),2)
                     +(z-1));
                double valuexy =-24/(pow(communication_range,4))*
                                 (z-1)*(agent->y-obspos(1,0))*(agent->x-obspos(0,0));
                fillsymetrix(m_Hession,agent->indexofx,agent->indexofx,
                             20*valuex);
                fillsymetrix(m_Hession,agent->indexofy,agent->indexofy,
                             20*valuey);
                fillsymetrix(m_Hession,agent->indexofx,agent->indexofy,
                             20*valuexy);
                //他们是连续的
            }
            //上面添加对障碍物避障的最小项
        }


    }
    //碰撞约束完成,雅可比计算相对比较简单，就不用Tensor了
    return error;
}

void minimize_Topology::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{
    GetCost();
    jac_block=m_Hession.sparseView();
}

void minimize_Topology::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    GetCost();
    jac=m_jac.sparseView();
}

