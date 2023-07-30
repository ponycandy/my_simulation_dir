#include "topology_constrain.h"


Topology_Constrain::Topology_Constrain(int num, std::string name):ifopt::ConstraintSet(num,name)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("collision_r",collision_r);
    common_initialize(var_struct);
    actMat.resize(2*agentnum,decnum);
    stateMat.resize(3*agentnum,decnum);
    constrainnum=num;
    m_jac.resize(constrainnum,5*agentnum*decnum);
}

ifopt::Component::VectorXd Topology_Constrain::GetValues() const
{
    m_jac.setZero();
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);
    //相互之间的碰撞距离啊....这个不是组队距离
    double error=0;
    int m=0;
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
                g(m)=Dis*Dis;


                m_jac(m,var_struct.steps[steps]->agents[i]->indexofx)+=4*Dis*((var_struct.steps[steps])->agents[i]->x-neib->x);
                m_jac(m,var_struct.steps[steps]->agents[i]->indexofy)+=4*Dis*((var_struct.steps[steps])->agents[i]->y-neib->y);
                m_jac(m,var_struct.steps[steps]->agents[ID-1]->indexofx)+=4*Dis*(-(var_struct.steps[steps])->agents[i]->x+neib->x);
                m_jac(m,var_struct.steps[steps]->agents[ID-1]->indexofy)+=4*Dis*(-(var_struct.steps[steps])->agents[i]->y+neib->y);
                m+=1;
            }
        }
    }
    return g;
}

ifopt::Component::VecBound Topology_Constrain::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=constrainnum;i++)
    {
        b.at(i-1)=ifopt::Bounds(-0.1,0.1);
    }

    return b;
}

void Topology_Constrain::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{

}

void Topology_Constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    GetValues();
    jac_block=m_jac.sparseView();
}
