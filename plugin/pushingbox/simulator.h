#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QThread>
#include <Eigen/Core>
#include <include/GL_2D/ODE_functor.h>
#include <include/GL_2D/GL2Dcommon.h>
#include <service/CollisionDetectservice.h>
class Simulator : public QObject,public ODE_functor
{
    Q_OBJECT
public:
    Simulator(QObject *parent = nullptr);
    void init();//初始化公共变量
    void detect_neibor(Eigen::MatrixXd state_mat);
    void detect_collision();
    bool within_range(Eigen::MatrixXd state,single_obstacle *obs);

    void ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
   void control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat) override;
    void sensor(Eigen::MatrixXd state_mat) override;

    void broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor) override;

    void randonize_state();
    void randonize_obs();
    void update_obs();
    double get_angle(double vx,double vy);


    double delta_t;
    Eigen::MatrixXd Amat;
    Eigen::MatrixXd Bmat;
    Eigen::MatrixXd Cmat;
    Eigen::MatrixXd state;
    Eigen::MatrixXd control_0;
    Eigen::MatrixXd sense_0;



signals:
    void sig_agent_state_update(QVector<double> state);

};

#endif // SIMULATOR_H
