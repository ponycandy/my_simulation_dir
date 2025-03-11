#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
#include "QObject"
#include <DeadReckon.h>
#include <xmlcore.h>
#include "service/Datalogservice.h"
class vehicle:public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void timerEvent(QTimerEvent *event) override;
    void setsendsig(int order);
    void to_steering(Eigen::MatrixXd &mat);
    void Get_sync_error(Eigen::MatrixXd &mat);//计算综合误差变量
    void broadcastfunction() override;
    void controlfunction() override;
    bool stable_judgement() ;
    void predicitTraj();
    void Getcontrol();
    void Getlookaheadpoint();
    void fault_set(int option) override;
    QMap<int , double>  nearbyagentdistance;
    QVector<DeadReckon *>  predictguy;
    QVector<Eigen::MatrixXd>  Cachegrey;
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
    Eigen::MatrixXd refpos;
    Eigen::MatrixXd lastpos_xy;
    Eigen::MatrixXd formationmat;
    Eigen::MatrixXd cacheETM;
    int agentnum;
    int cacheOBSclpnum;
    double cacheSigma;
    double sigma=0.1;
    int predictedN;
    int internalcount=0;
    int chache_idx=0;
    double omega=0;
    double linear=0;
    Eigen::MatrixXd m_e_T;
    Eigen::MatrixXd syncP;
    Eigen::MatrixXd m_v_T;
    Eigen::MatrixXd m_v_n;
    Eigen::MatrixXd leader_act_temp;
    Eigen::MatrixXd leader_pos_temp;
    Eigen::MatrixXd leader_vel_temp;
    Eigen::MatrixXd pathpoint;
    double lookahead_dist_;  // 预瞄距离
    int pathpointnum;
    Datalogservice *logger;
    xmlCore *xmlreader;
    int m_timerid1;
    int formationid=0;

signals:
    void updatetarget(double x,double y,double phi);
    void LeaderBroadcast(Eigen::MatrixXd e_T,Eigen::MatrixXd v_T,Eigen::MatrixXd v_n,Eigen::MatrixXd othersignal);
public slots:
    void Broadcastupdate(Eigen::MatrixXd e_t,Eigen::MatrixXd v_t,Eigen::MatrixXd v_n,Eigen::MatrixXd othersignal);


};

#endif // VEHICLE_H
