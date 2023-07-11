#include "automated_gradient.h"
Automated_Gradient::Automated_Gradient()
{

}

void Automated_Gradient::GetGradient(Eigen::VectorXd &x, const AutoCalc *calculator, Eigen::MatrixXd &jacob)
{
    Eigen::VectorXd value;
    calculator->GetValue(x,value);

    int maxnum=value.rows();
    int varnum=x.size();
    double step=0.0001;
    jacob.resize(maxnum,varnum);
    jacob.setZero();
    Eigen::VectorXd consmat;
    consmat.resize(maxnum,1);
    consmat.setZero();

    for(int i=0;i<varnum;i++)
    {
        Eigen::VectorXd y_var=x;
        y_var(i)+=step;
        calculator->GetValue(y_var,consmat);
        jacob.block(0,i,maxnum,1)=(consmat-value)/step;
    }
}


