
#ifndef DYNAMIC_FUNCTION_H
#define DYNAMIC_FUNCTION_H


#include <QObject>

#include <include/MPC/MPC_ODE.h>
class dynamic_function : public QObject,public MPC_ODE
{
    Q_OBJECT
public:
    explicit dynamic_function(QObject *parent = nullptr);
    void get_A_and_B(Eigen::MatrixXd act_mat,
                     Eigen::MatrixXd state_mat,Eigen::MatrixXd &A_mat,Eigen::MatrixXd &B_mat) override;
    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
signals:

};

#endif // DYNAMIC_FUNCTION_H
