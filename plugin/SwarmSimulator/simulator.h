#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QThread>
#include <Eigen/Core>
#include <include/GL_2D/ODE_functor.h>
#include <include/GL_2D/GL2Dcommon.h>
#include <service/CollisionDetectservice.h>
#include <SwarmAgent.h>
#include <SwarmObstacle.h>
class Simulator : public QObject,public ODE_functor
{
    Q_OBJECT
public:
    Simulator(QObject *parent = nullptr);
    void init(int ID);//初始化公共变量
    void detect_neibor(Eigen::MatrixXd state_mat);
    void detect_collision();
    bool within_range(Eigen::MatrixXd posxy,SwarmObstacle *obs);

    void ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
   void control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat) override;
    void sensor(Eigen::MatrixXd state_mat) override;

    void broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor) override;

    void update_obs();

    //    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat);
    //精度需求并不高，没有必要使用和matlab ode45相同的仿真求解器
    //一些重要的公共变量放置在下面，移植simulator的时候可以改变下面的值
    //下面就是可变值
    //那，能不能就继承run接口和ode接口呢？然后给一个主流程的控制口
    //ode自己写，然后再写一个update_state的接口，也是自己的内容
    //也就是：ode--->detect---->control--->signal
    //以上步骤被simulator库写死
    //然后允许对其中的各个子组件进行修改
    int agent_num;
    int obs_num;
    int neib_seq;
    double delta_t;double agent_communication_range;double collision_r;

    CollisionDetectservice *m_service;
    QMap<int,SwarmAgent*> Agents_group;
    QMap<int,SwarmObstacle*> obsbounding_group;
    Eigen::MatrixXd Amat;
    Eigen::MatrixXd Bmat;
    Eigen::MatrixXd neib_array;
    Eigen::MatrixXd state_array;
    Eigen::MatrixXd act_array;

    int thread_ID;

signals:
    void sig_agent_state_update(QMap<int,SwarmAgent*> Agents_group_s);
    void sig_obs_state_update(QMap<int,SwarmObstacle*> obs_group_s);

};

#endif // SIMULATOR_H
