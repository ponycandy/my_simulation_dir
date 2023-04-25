#ifndef NMPC_DEFINE_H
#define NMPC_DEFINE_H

#include <QObject>
#include <QString>
#include <Eigen/Core>
class NMPC_Extra_Constrain
{
public:
    virtual ~NMPC_Extra_Constrain(){}
    virtual Eigen::MatrixXd GetCost(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
    virtual Eigen::MatrixXd GetCost(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
};
#endif 

