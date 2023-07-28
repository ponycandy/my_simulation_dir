#include "minimize_topology.h"


minimize_Topology::minimize_Topology(std::string name):ifopt::CostTerm(name)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("collision_r",collision_r);
    common_initialize(var_struct);
    actMat.resize(2*agentnum,decnum);
    stateMat.resize(3*agentnum,decnum);
    m_jac.resize(1,5*agentnum*decnum);

}

double minimize_Topology::GetCost() const
{
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    m_jac.setZero();
    //这才是组队距离

    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);
    double error=0;
    for(int steps=0;steps<decnum;steps++)
    {
        for(int i=0;i<agentnum;i++)
        {
            int edge_num=(var_struct.steps[steps])->agents[i]->edgenum;
            for(int j=0;j<edge_num;j++)
            {
                int ID=var_struct.steps[steps]->agents[i]->Edg[j]->End_Node_ID;
                double length=var_struct.steps[steps]->agents[i]->Edg[j]->length;
                single_vehicle_data *neib=var_struct.steps[steps]->agents[ID-1];
                double Dis=pow((var_struct.steps[steps]->agents[i]->posxy-neib->posxy).norm(),2)-length*length;

                error+=Dis;

                m_jac(0,var_struct.steps[steps]->agents[i]->indexofx)+=2*(var_struct.steps[steps])->agents[i]->x;
                m_jac(0,var_struct.steps[steps]->agents[i]->indexofy)+=2*(var_struct.steps[steps])->agents[i]->y;
                m_jac(0,var_struct.steps[steps]->agents[j]->indexofx)+=2*(var_struct.steps[steps])->agents[j]->x;
                m_jac(0,var_struct.steps[steps]->agents[j]->indexofy)+=2*(var_struct.steps[steps])->agents[j]->y;

            }
        }
    }
    //碰撞约束完成,雅可比计算相对比较简单，就不用Tensor了
    return error;
}

void minimize_Topology::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    GetCost();
    jac=m_jac.sparseView();
}
