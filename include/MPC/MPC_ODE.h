#ifndef MPC_ODE_H
#define MPC_ODE_H

#include <QObject>
#include <QString>
#include <Eigen/Core>
class MPC_ODE
{
public:
    virtual ~MPC_ODE(){}
    virtual Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
    virtual void get_A_and_B(Eigen::MatrixXd act_mat,
     Eigen::MatrixXd state_mat,Eigen::MatrixXd &A_mat,Eigen::MatrixXd &B_mat)=0;

};
#endif 

