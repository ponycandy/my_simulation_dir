#include "jacobiancalc.h"
#include "xmlcore.h"
Jacobiancalc::Jacobiancalc()
{
    int agentnum;
    int decnum;
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agent_Num);
    xmlreader.xmlRead("decnum",decnum);

}

Eigen::MatrixXd Jacobiancalc::jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd returnmat;
    returnmat.resize(3*agent_Num,5*agent_Num);
    returnmat.setZero();
    Eigen::MatrixXd JacBlock;
    JacBlock.resize(3,5);
    JacBlock.setZero();

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
