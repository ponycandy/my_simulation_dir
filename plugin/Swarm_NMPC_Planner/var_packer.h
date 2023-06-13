#ifndef VAR_PACKER_H
#define VAR_PACKER_H

#endif // VAR_PACKER_H

#pragma once
#include <Eigen/Core>
#include <PolyParams.h>
#include <xmlcore.h>
#define state_x_index(pointNum) (4*pointNum+0)
#define state_y_index(pointNum) (4*pointNum+1)
#define state_vx_index(pointNum) (4*pointNum+2)
#define state_vy_index(pointNum) (4*pointNum+3)

inline void packvariable_states_set(Eigen::VectorXd &x,Eigen::MatrixXd &statemat,int dec_num);
void packvariable_states_set(Eigen::VectorXd &x,Eigen::MatrixXd &statemat,int dec_num)
{
    for(int i=0;i<dec_num;i++)
    {
        statemat(0,i)=x(state_x_index(i));
        statemat(1,i)=x(state_y_index(i));
        statemat(2,i)=x(state_vx_index(i));
        statemat(3,i)=x(state_vy_index(i));
    }
}
