#ifndef VEHICLE_H
#define VEHICLE_H
#include "SwarmAgent.h"
#include "QObject"
#include "defines/CpyDefines.h"

#include "service/Datalogservice.h"
#include "service/VehicleControlservice.h"
#include "SmoothSlidingWindowFilter.h"
#include "qtimer.h"
class vehicle:public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void setsendsig(int order);
    void implementcontrol();
    Eigen::MatrixXd make_mat(CPYDATA::mat_trans &PTtopic);
    void parse(const char *data, CPYDATA::mat_trans &PTtopic);
    void broadcastfunction() override;
    void controlfunction() override;
//    void predicitTraj(Eigen::MatrixXd &target);
    void fault_set(int option) override;
    void sendMat(Eigen::MatrixXd &mat);
    void execute( CPYDATA::mat_trans ptopic, QByteArray &sending_data);
    QMap<int , double>  nearbyagentdistance;
    char m_preassigned_mat[4000];//最大允许值,也就是一次最多传输五百个左右元素
    SwarmAgent* clone_agent() override;
    VehicleControlservice *controlservice;
    Eigen::MatrixXd state_space_equation() override;

    Eigen::MatrixXd A_;
    Eigen::MatrixXd H_;
    Eigen::MatrixXd B_;

    Eigen::MatrixXd A_2;
    Eigen::MatrixXd H_2;
    Eigen::MatrixXd B_2;

    int agentnum;
    QTimer *timer;
    int trigInterval=4;//刚好是决策数目
    int cachetrigcount=0;
    int cacheOBSclpnum;
    double cacheSigma;
    int internalcount;
    std::vector<double> calibratevec;
    Eigen::MatrixXd Trackref;
    Datalogservice *logger;
    Eigen::MatrixXd InternalState;
    SmoothSlidingWindowFilter *Filter;
    Eigen::MatrixXd state_temp;
    double lastOmega;

    bool is_first_time=true;
    Eigen::MatrixXd m_v_T;
signals:
    void sigNLPback();
public slots:
    void getsolution(Eigen::MatrixXd solution);
    void UWB_state_Update(int rID,float head_x,float head_y,float tail_x,float tail_y);
    void slot_update_target(double x, double y);
    void Oninitkalman();
    void Onstop();
    void Onspin();

//邻居状态通过neib_detect实现

};

#endif // VEHICLE_H
