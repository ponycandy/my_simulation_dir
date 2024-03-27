#ifndef VEHICLE_H
#define VEHICLE_H
#include "SwarmAgent.h"
#include "QObject"

#include "service/Datalogservice.h"
#include "SwarmAgent.h"
class vehicle:public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void setsendsig(int order);
    void implementcontrol();

    void broadcastfunction() override;
    void controlfunction() override;
    //    void predicitTraj(Eigen::MatrixXd &target);
    void fault_set(int option) override;
    void sendMat(Eigen::MatrixXd &mat);

    QMap<int , double>  nearbyagentdistance;
    char m_preassigned_mat[4000];//最大允许值,也就是一次最多传输五百个左右元素
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;

    int agentnum;
    int trigInterval=4;//刚好是决策数目
    int cachetrigcount=0;
    int cacheOBSclpnum;
    double cacheSigma;
    int internalcount;
    Eigen::MatrixXd Trackref;
    Datalogservice *logger;

    Eigen::MatrixXd InternalState;

signals:
    void sigNLPback();
public slots:
    void getsolution(Eigen::MatrixXd solution);


};

#endif // VEHICLE_H
