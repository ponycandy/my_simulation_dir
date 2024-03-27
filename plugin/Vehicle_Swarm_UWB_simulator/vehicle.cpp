#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <Vehicle_Swarm_UWB_simulatorActivator.h>
#include "OSGIEVENT.h"
Eigen::MatrixXd originalvector;
int counter=0;

inline double ValueOperator(Eigen::MatrixXd value)
{
    return abs(calculateAngleBetweenVectors(originalvector,value));
}
vehicle::vehicle():SwarmAgent()
{
    calibratevec.push_back(0.77);//jetson nano 2的误差
    calibratevec.push_back(-0.649585);//SCOUT_V1的误差
    calibratevec.push_back(0);//SCOUT_V2的误差

    timer=new QTimer;
    Filter=new SmoothSlidingWindowFilter;
    Filter->SetWindowLength(10);
    state_temp.resize(3,1);
    cacheOBSclpnum=0;
    internalcount=0;
    cacheSigma=1;
    status_num=3;
    action_num=2;
    act_vector.resize(2,1);
    act_vector<<0,0;
    state_vector.resize(3,1);

    A_.resize(1,1);
    A_(0,0)=1;
    B_.resize(1,1);
    B_(0,0)=0.02;
    H_.resize(1,1);
    H_(0,0)=1;

    A_2.resize(2,2);
    A_2.setIdentity();
    A_2=A_2;
    B_2=A_2*0.02;
    H_2.resize(2,2);
    H_2.setIdentity();

    QString filename="D:/QT/prjdir/OSGIMODULE/my_simulation_dir/build/config/DistributedMPC/swarmUWB.xml";

    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    TriggerEvent();
    //动力学不变
    selfETM.resize(5,1);
    selfETM.setZero();
    xmlreader.xmlRead("collision_r",collision_r);

    Vehicle_Swarm_UWB_simulatorActivator::subscribeslot(this,
                                                        SLOT(UWB_state_Update(int  ,float  ,float ,float  ,float  )),
                                                        OSGIEVENT::UWB_AGENT_STATE_UPDATE,
                                                        Qt::QueuedConnection);
    controlservice=Vehicle_Swarm_UWB_simulatorActivator::getService<VehicleControlservice>("VehicleControlservice");
    connect(timer,SIGNAL(timeout()),this,SLOT(Oninitka
                                                     lman()));
    timer->start(5000);
}


void vehicle::state_update()
{

    heading_angle=normalize( state_vector(2,0));
    state_vector(2,0)=heading_angle;
    pos_xy(0,0)=state_vector(0,0);
    pos_xy(1,0)=state_vector(1,0);
    vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
    vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
    selfETM<<pos_xy(0,0),pos_xy(1,0),heading_angle,act_vector(0,0),act_vector(1,0);


}

void vehicle::sensorfunction()
{

}
void vehicle::broadcastfunction()
{


}

void vehicle::controlfunction()
{
    // if(ID==1)
    if(1)
    {
        //领导者的轨迹

       controlservice->sendVehicleCommand(ID-1,act_vector(0,0),act_vector(1,0));
        // 仿真器中ID从1开始，但是上位机软件中ID从0开始
    }
    else
    {

    }

}







void vehicle::setsendsig(int order)
{



}

void vehicle::implementcontrol()
{

}

void vehicle::fault_set(int option)
{


}


SwarmAgent *vehicle::clone_agent()
{
    vehicle *new_vehicle=new vehicle;
    return new_vehicle;
}

Eigen::MatrixXd vehicle::state_space_equation()
{
    //不需要，按照实际情况来
    Eigen::MatrixXd d_state;
    d_state.resize(3,1);
    d_state.setZero();


    return d_state;

}

void vehicle::getsolution(Eigen::MatrixXd solution)
{
    act_vector=solution.eval();
    emit sigNLPback();
}

void vehicle::UWB_state_Update(int rID, float head_x, float head_y, float tail_x, float tail_y)
{
    // qDebug()<<"触发接收信号";
    // qDebug()<<rID;
    if(rID==ID-1)
    {
        // qDebug()<<"ID正确";
        if(is_first_time)
        {
            Eigen::VectorXd x_;
            x_.resize(1,1);x_(0,0)=get_angle(head_x-tail_x,head_y-tail_y);

            Eigen::MatrixXd P_;
            P_.resize(1,1);P_(0,0)=1.8e-6;

            Eigen::MatrixXd R_;
            R_.resize(1,1);R_(0,0)=0.01;

            Eigen::MatrixXd Q_;
            Q_.resize(1,1);Q_(0,0)=0.01;

            Eigen::VectorXd x_2;
            x_2.resize(2,1);
            x_2(0,0)=(head_x+tail_x)/2;
            x_2(1,0)=(head_y+tail_y)/2;

            Eigen::MatrixXd P_2;
            P_2.resize(2,2);
            P_2.setIdentity();
            P_2=P_2*1.8e-6;

            Eigen::MatrixXd R_2;
            R_2.resize(2,2);
            R_2.setIdentity();
            R_2=R_2*0.01;

            Eigen::MatrixXd Q_2;
            Q_2.resize(2,2);
            Q_2.setIdentity();
            Q_2=Q_2*0.01;

            // Kfilter
            is_first_time=false;
            // Kfilter->init(x_,P_,R_,Q_);//如果是恒定触发,那么预测

            // posKfilter->init(x_2,P_2,R_2,Q_2);

            state_vector(1,0)=(head_y+tail_y)/2;
            state_vector(0,0)=(head_x+tail_x)/2;
            state_vector(2,0)=calibratevec[rID]+get_angle(head_y-tail_y,head_x-tail_x);
            Filter->FilterData(state_vector);//角度单独滤波，只能希望够用！
            state_update();
            qDebug()<<"x: "<<pos_xy(0,0)<<" y:"<<pos_xy(1,0)<<" angle:"<<state_vector(2,0);//记录两个位置的平均位置

            return;
        }
        // Eigen::VectorXd action;action.resize(1);
        // action(0)=act_vector(1,0);//角速度
        // Eigen::VectorXd z_meas;
        // z_meas.resize(1);
        // z_meas(0)=get_angle(-head_y+tail_y,-head_x+tail_x);
        // Eigen::VectorXd results;results.resize(1);
        // results=Kfilter->predict( A_, B_,action);
        // results=Kfilter->getupdatedvalue(H_,z_meas);
        // Eigen::VectorXd action2;action2.resize(2);
        // action2(0)= vel_xy(0,0);//x方向速度
        // action2(1)= vel_xy(1,0);//y方向速度
        // Eigen::VectorXd z_meas2;
        // z_meas2.resize(2);
        // z_meas2(0)=(head_x+tail_x)/2;
        // z_meas2(1)=(head_y+tail_y)/2;
        // Eigen::VectorXd results2;results2.resize(2);
        // results2=posKfilter->predict(A_2, B_2,action2);
        // results2=posKfilter->getupdatedvalue(H_2,z_meas2);

        // qDebug()<<state_vector(2,0);
        // if(abs(heading_angle-results(0))>0.1)
        // {
        //     //滤除异常角度跳动，这个非常重要
        //     // qDebug()<<"跳动！";
        //     // qDebug()<<abs(heading_angle-state_vector(2,0));
        //     return;
        // }

        //只能是接收一下异常点了
        // state_vector(0,0)=results2(0);
        // state_vector(1,0)=results2(1);
        // state_vector(2,0)=results(0);
        state_temp<<    (head_y+tail_y)/2,(head_x+tail_x)/2,calibratevec[rID]+ get_angle(head_y-tail_y,head_x-tail_x);
        state_vector=Filter->FilterData(state_temp);
        if(ID==2)
        {
            qDebug()<<"x : "<<pos_xy(0,0)<<" y:"<<pos_xy(1,0)<<" angle:"<<state_vector(2,0);//记录两个位置的平均位置

        }

        state_update();
    }
}

void vehicle::slot_update_target(double x, double y)
{

}

void vehicle::Oninitkalman()
{
    is_first_time=true;
    timer->stop();
}

void vehicle::Onstop()
{
    act_vector.setZero();
}

void vehicle::Onspin()
{
 act_vector<<0,0.15;
}

