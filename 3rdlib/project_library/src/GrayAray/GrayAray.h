#ifndef GRAYARAY_H
#define GRAYARAY_H
#include "GRAYARAY_global.h"
#include "Eigen/Dense"
#include "greytheory.h"
class GRAYARAY_EXPORT GrayAray
{
public:
    GrayAray();
    void resize(int num);
    void storeInitial(Eigen::MatrixXd &states);
    void GetreturnState(Eigen::MatrixXd &returnstates,Eigen::MatrixXd &input);
    void predictOnce(Eigen::MatrixXd &returnstates);
    void GetCurrentValue(Eigen::MatrixXd &returnstates);
    int statenum;
    std::vector<GreyTheory *> group_vec;
};


#endif // GRAYARAY_H
