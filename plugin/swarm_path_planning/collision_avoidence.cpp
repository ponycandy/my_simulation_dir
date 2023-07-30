#include "collision_avoidence.h"
#include "swarm_path_planningActivator.h"

Collision_Avoidence::Collision_Avoidence(int num, std::string name):ifopt::ConstraintSet(num,name)
{
//    m_service=swarm_path_planningActivator::getService<Datalogservice>("Datalogservice");
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("collision_r",collision_r);
    common_initialize(var_struct);
    actMat.resize(2*agentnum,decnum);
    stateMat.resize(3*agentnum,decnum);
    constrainnum=num;
    m_jac.resize(constrainnum,5*agentnum*decnum);
//    m_service->createlogfile("./log/optimization_process.txt",8054);

}

ifopt::Component::VectorXd Collision_Avoidence::GetValues() const
{
    m_jac.setZero();
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);
    //相互之间的碰撞距离啊....这个不是组队距离
    int m=0;
    for(int steps=0;steps<decnum;steps++)
    {
        for(int i=0;i<agentnum;i++)
        {
            for(int j=i+1;j<agentnum;j++)
            {
                double distance_error=pow(((var_struct.steps[steps])->agents[i]->posxy-
                                             (var_struct.steps[steps])->agents[j]->posxy).norm(),2)
                                        -collision_r*collision_r;

                g(m)=distance_error;
                int indexofxi=var_struct.steps[steps]->agents[i]->indexofx;
                int indexofyi=var_struct.steps[steps]->agents[i]->indexofy;
                int indexofxj=var_struct.steps[steps]->agents[j]->indexofx;
                int indexofyj=var_struct.steps[steps]->agents[j]->indexofy;
                double xi=(var_struct.steps[steps])->agents[i]->x;
                double xj=(var_struct.steps[steps])->agents[j]->x;
                double yi=(var_struct.steps[steps])->agents[i]->y;
                double yj=(var_struct.steps[steps])->agents[j]->y;

                m_jac(m,indexofxi)=2*xi-2*xj;
                m_jac(m,indexofyi)=2*yi-2*yj;
                m_jac(m,indexofxj)=2*xj-2*xi;
                m_jac(m,indexofyj)=2*yj-2*yi;
//                QString value="g("+QString::number(m)+") is " +QString::number(distance_error);
                m+=1;

//                m_service->log(value,2);
            }
        }
    }
    //碰撞约束完成,雅可比计算相对比较简单，就不用Tensor了
    return g;
}

ifopt::Component::VecBound Collision_Avoidence::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=constrainnum;i++)
    {
        b.at(i-1)=ifopt::BoundGreaterZero;
    }

    return b;
}

void Collision_Avoidence::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    GetValues();
    jac_block=m_jac.sparseView();
}

void Collision_Avoidence::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{

}
