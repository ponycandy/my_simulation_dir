#ifndef ODE_FUNCTOR_H
#define ODE_FUNCTOR_H

#include <QObject>
#include <QString>
#include <3rdlib/Eigen/Core>
class ODE_functor
{
public:
    virtual ~ODE_functor(){}
    virtual void ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
    virtual void sensor(Eigen::MatrixXd state_mat)=0;
    virtual void control(Eigen::MatrixXd sensor,Eigen::MatrixXd state_mat)=0;
    virtual void broad_cast(Eigen::MatrixXd state_mat,Eigen::MatrixXd act_mat,Eigen::MatrixXd sensor)=0;
//    virtual void test()=0;
};
#endif 

