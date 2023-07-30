#ifndef NMPC_DYNAMIC_JACOB_H
#define NMPC_DYNAMIC_JACOB_H

#include <QObject>
#include <QString>
#include <Eigen/Core>
class NMPC_Dynamic_Jacob
{
public:
    virtual ~NMPC_Dynamic_Jacob(){}
    virtual Eigen::MatrixXd jacobica(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat)=0;
    virtual void Hession(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat,Eigen::MatrixXd &Hession_temp,int state_index) =0;
};
#endif 

