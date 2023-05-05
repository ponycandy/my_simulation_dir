
#ifndef TWOTWOODE_H
#define TWOTWOODE_H


#include <QObject>
#include "include/GL_2D/ODE_functor.h"
#include "MPC/MPC_ODE.h"

class twotwoode : public QObject,public MPC_ODE
{
    Q_OBJECT
public:
    explicit twotwoode(QObject *parent = nullptr);
    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat);
    Eigen::MatrixXd stepin();
    void get_A_and_B(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &A_mat, Eigen::MatrixXd &B_mat) override;
    void sensor(Eigen::MatrixXd state_mat) ;
    void control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat) ;
    void broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor) ;
    Eigen::MatrixXd state;
    Eigen::MatrixXd control_0;
signals:

};

#endif // TWOTWOODE_H
