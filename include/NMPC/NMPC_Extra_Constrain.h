#ifndef NMPC_EXTRA_CONSTRAIN_H
#define NMPC_EXTRA_CONSTRAIN_H

#include <QObject>
#include <QString>
#include <Eigen/Core>
class NMPC_Extra_Constrain
{
public:
    virtual ~NMPC_Extra_Constrain(){}
    virtual Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
};
#endif 

