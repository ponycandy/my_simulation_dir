#ifndef COMMONSTRUCTANDFUNCTION_H
#define COMMONSTRUCTANDFUNCTION_H
#include "Eigen/core"
#include "QVector"
#include "xmlcore.h"
struct edge
{
    int start_Node_ID;
    int End_Node_ID;
    double length;

};
struct BetaAgent
{
    double x;
    double y;
    Eigen::Vector2d posxy;
};
struct single_vehicle_data
{
    Eigen::Vector2d posxy;
    double x;
    double y;
    double phi;
    double v;
    double w;
    int indexofx;
    int indexofy;
    int indexofphi;
    int indexofv;
    int indexofw;
    int ID;
    int edgenum;
    QVector<edge *> Edg;
    int betaAgentNum;
    QVector<BetaAgent *> clsp;
    //里面总是放最近的agent
};
struct single_time_data
{
    QVector<single_vehicle_data*> agents;

};
struct swarmvehicle
{
    QVector<single_time_data*> steps;
};

inline void pack_variable(Eigen::VectorXd &opt_x,int state_num_plus_act_num,
                          int dec_num,int act_num,int state_num,
                          Eigen::MatrixXd &actMat,Eigen::MatrixXd &stateMat);
inline void  unpackvariable(Eigen::VectorXd &opt_x,int state_num_plus_act_num,
                           int dec_num,int act_num,int state_num,int agentnum,Eigen::MatrixXd &actMat,
                           Eigen::MatrixXd &stateMat,
                           swarmvehicle &var_struct);
inline void common_initialize(swarmvehicle &var_struct);


void pack_variable(Eigen::VectorXd &opt_x,int state_num_plus_act_num,
                   int dec_num,int act_num,int state_num,
                   Eigen::MatrixXd &actMat,Eigen::MatrixXd &stateMat)
{
    int i=1; //此为opt_x列向量的index,记得调用时减1
    int current_time_step=0;//hint此时矩阵元素所处时刻
    int act_vec_flag=0;
    while (i<=state_num_plus_act_num*dec_num)
    {
        if (act_vec_flag==0)
        {
            for(int actIndex=0;actIndex<act_num;actIndex++)
            {
                actMat(actIndex,current_time_step)=opt_x(i-1);
                i=i+1;
            }
            act_vec_flag=1;
        }
        else
        {
            for(int stateIndex=0;stateIndex<state_num;stateIndex++)
            {
                stateMat(stateIndex,current_time_step)=opt_x(i-1);
                i=i+1;
            }
            act_vec_flag=0;
            current_time_step++;
        }
    }
}
void common_initialize(swarmvehicle &var_struct)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");
    int agentnum=0;
    xmlreader.xmlRead("agent_num",agentnum);
    int decnum=0;
    xmlreader.xmlRead("decnum",decnum);
    Eigen::MatrixXd relationmatrix;
    relationmatrix.resize(agentnum,agentnum);
    xmlreader.xmlRead("relationmatrix",relationmatrix);
    for(int k=0;k<=decnum-1;k++)
    {
        single_time_data *std=new single_time_data;
        for(int i=1;i<=agentnum;i++)
        {
            single_vehicle_data *sv=new single_vehicle_data;
            sv->ID=i;
            sv->edgenum=0;
            for(int sp=0;sp<agentnum;sp++)
            {
                if(relationmatrix(i-1,sp)!=0)
                {
                    sv->edgenum+=1;
                    edge * newedge=new edge;
                    newedge->start_Node_ID=i;
                    newedge->End_Node_ID=sp+1;
                    newedge->length=relationmatrix(i-1,sp);
                    sv->Edg.push_back(newedge);
                }
            }
             std->agents.push_back(sv);
        }
        var_struct.steps.push_back(std);
    }

}
void unpackvariable(Eigen::VectorXd &opt_x,int state_num_plus_act_num,
                    int dec_num,int act_num,int state_num,int agentnum,Eigen::MatrixXd &actMat,
                    Eigen::MatrixXd &stateMat,
                    swarmvehicle &var_struct)
{

    pack_variable(opt_x,state_num_plus_act_num,
                  dec_num,act_num,state_num,
                  actMat,stateMat);
    //现在actMat和stateMat里面就是按照时间顺序排列的值了，我们需要再分一次到每个agent
    for(int k=0;k<dec_num;k++)
    {
        for(int i=0;i<agentnum;i++)
        {
            single_vehicle_data* a_vehicle=var_struct.steps[k]->agents[i];//不是插入，而是更改
            a_vehicle->x=stateMat(3*i+0,k);a_vehicle->indexofx=k*5*agentnum+3*i+agentnum*2;
            a_vehicle->y=stateMat(3*i+1,k);a_vehicle->indexofy=k*5*agentnum+3*i+agentnum*2+1;
            a_vehicle->phi=stateMat(3*i+2,k);a_vehicle->indexofphi=k*5*agentnum+3*i+agentnum*2+2;
            a_vehicle->v=actMat(2*i+0,k);a_vehicle->indexofv=k*5*agentnum+2*i+0;
            a_vehicle->w=stateMat(2*i+1,k);a_vehicle->indexofw=k*5*agentnum+2*i+1;
            a_vehicle->posxy<<a_vehicle->x,a_vehicle->y;
        }

    }
}

#endif // COMMONSTRUCTANDFUNCTION_H
