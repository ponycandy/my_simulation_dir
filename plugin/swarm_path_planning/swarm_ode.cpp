#include "swarm_ode.h"

#include "xmlcore.h"
Swarm_ODE::Swarm_ODE(QObject *parent)
{

    int agentnum;
    int decnum;
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agent_Num);
    xmlreader.xmlRead("decnum",decnum);

}


Eigen::MatrixXd Swarm_ODE::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd dstate;
    dstate.resize(3*agent_Num,1);
    dstate.setZero();
    for(int i=0;i<agent_Num;i++)
    {
        double x=state_mat(3*i+0);
        double y=state_mat(3*i+1);
        double phi=state_mat(3*i+2);

        double v=act_mat(2*i+0);
        double w=act_mat(2*i+1);
        dstate(3*i+0,0)=v*cos(phi);
        dstate(3*i+1,0)=v*sin(phi);
        dstate(3*i+2,0)=w;

    }
    return dstate;
}
