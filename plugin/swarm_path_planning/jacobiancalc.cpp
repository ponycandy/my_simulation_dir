#include "jacobiancalc.h"
#include "xmlcore.h"
Jacobiancalc::Jacobiancalc()
{
    int agentnum;
    int decnum;
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agent_Num);
    xmlreader.xmlRead("decnum",decnum);

    returnmat.resize(3*agent_Num,5*agent_Num);
    returnmat.setZero();

    JacBlock.resize(3,5);
    JacBlock.setZero();

}

Eigen::MatrixXd Jacobiancalc::jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{


    for(int i=0;i<agent_Num;i++)
    {
        double x=state_mat(3*i+0);
        double y=state_mat(3*i+1);
        double phi=state_mat(3*i+2);

        double v=act_mat(2*i+0);
        double w=act_mat(2*i+1);

        returnmat.block(3*i,2*i,3,2)<<cos(phi) , 0 ,
            sin(phi) , 0 ,
            0      , 1 ;
        returnmat.block(3*i,2*agent_Num+3*i,3,3)<< 0 , 0 , -v*sin(phi),
            0 , 0 , v*cos(phi),
            0  ,  0  ,0 ;
    }
    return returnmat;
}

void Jacobiancalc::Hession(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &Hession_temp, int state_index)
{
    int agentindex=state_index/3;
    int state=state_index-3*agentindex;
    double phi=state_mat(3*agentindex+2,0);
    double x=state_mat(3*agentindex+2,0);
    double y=state_mat(3*agentindex+2,0);
    double v=act_mat(2*agentindex+0,0);
    if(state==0)
    {
        //v phi
        Hession_temp(agentindex*2,agent_Num*2+3*agentindex+2)=-sin(phi);
        //phi phi
        Hession_temp(agent_Num*2+3*agentindex+2,agent_Num*2+3*agentindex+2)=-v*cos(phi);
        return;
    }
    if(state==1)
    {
        //v phi
        Hession_temp(agentindex*2,agent_Num*2+3*agentindex+2)=cos(phi);
        //phi phi
        Hession_temp(agent_Num*2+3*agentindex+2,agent_Num*2+3*agentindex+2)=-v*sin(phi);
        return;
    }
    if(state==2)
    {
        //v phi
        Hession_temp.setZero();
        return;
    }
}
