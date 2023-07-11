#include "automated_gradient.h"
Automated_Gradient::Automated_Gradient()
{

}

void Automated_Gradient::GetGradient(int constrainNum,Eigen::VectorXd &x,const AutoCalc *calculator,Eigen::MatrixXd &jacob)
{
    int maxnum=constrainNum;
    int varnum=x.size();
    double step=0.0001;
    Eigen::MatrixXd value;
    value.resize(maxnum,1);
    value.setZero();
    Eigen::MatrixXd consmat;
    consmat.resize(maxnum,1);
    consmat.setZero();
    calculator->GetValue(x,value);
    for(int i=0;i<varnum;i++)
    {
        Eigen::VectorXd y_var=x;
        y_var(i)+=step;
        calculator->GetValue(y_var,consmat);
        jacob.block(0,i,maxnum,1)=(consmat-value)/step;
    }
}
