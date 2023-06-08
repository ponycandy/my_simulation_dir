#ifndef JAC_OF_ANIMALS_H
#define JAC_OF_ANIMALS_H

#include "Eigen/Core"
#include "include/NMPC/NMPC_dynamic_Jacob.h"
class Jac_of_animals:public NMPC_Dynamic_Jacob
{
public:
    Jac_of_animals();
    Eigen::MatrixXd jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat) override;

};

#endif // JAC_OF_ANIMALS_H
