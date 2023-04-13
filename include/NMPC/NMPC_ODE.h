#ifndef NMPC_ODE_H
#define NMPC_ODE_H

#include <QObject>
#include <QString>
#include <Eigen/Core>
class NMPC_ODE
{
public:
    virtual ~NMPC_ODE(){}
    virtual Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
};
#endif 

