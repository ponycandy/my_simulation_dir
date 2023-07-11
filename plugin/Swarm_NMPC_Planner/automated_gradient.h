#ifndef AUTOMATED_GRADIENT_H
#define AUTOMATED_GRADIENT_H
#include <Eigen/Core>
#include <include/Autogradient/AutoCalc.h>
class Automated_Gradient
{
public:
    Automated_Gradient();
    void GetGradient(int constrainNum,Eigen::VectorXd &x,const AutoCalc *calculator,Eigen::MatrixXd &jacob);
};

#endif // AUTOMATED_GRADIENT_H
