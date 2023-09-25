#ifndef SWARM_ODE_H
#define SWARM_ODE_H
//说明：这里面有多组无人车，并不是单车ODE
//具体的数值通过xmlcore阅读初始化
#include "include/NMPC/NMPC_ODE.h"
class Swarm_ODE :public QObject,public NMPC_ODE
{
    Q_OBJECT
public:
    explicit Swarm_ODE(QObject *parent = nullptr);

    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
    int agent_Num;
    Eigen::MatrixXd dstate;
signals:

};
#endif
