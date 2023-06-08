#include "jac_of_animals.h"

Jac_of_animals::Jac_of_animals()
{

}

Eigen::MatrixXd Jac_of_animals::jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd dydx;

    dydx.resize(4,6);
    dydx.setZero();
    dydx(0,4)=1;
    dydx(1,5)=1;
    dydx(2,0)=1;
    dydx(3,1)=1;
    return dydx;//非常有必要将jacobia改成稀疏的！
}
