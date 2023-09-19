#ifndef AUTOCALC_H
#define AUTOCALC_H

#include <QObject>
#include <QString>
#include <Eigen/Core>
class AutoCalc
{
public:
    virtual ~AutoCalc(){}
    virtual void GetValue(Eigen::VectorXd &x,Eigen::VectorXd &returnvalue) const=0;
};
#endif 

