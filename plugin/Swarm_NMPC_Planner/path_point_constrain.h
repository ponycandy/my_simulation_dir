#ifndef PATH_POINT_CONSTRAIN_H
#define PATH_POINT_CONSTRAIN_H

#include <xmlcore.h>
#include <ifopt/constraint_set.h>
class Path_Point_Constrain:public ifopt::ConstraintSet
{
public:
    Path_Point_Constrain(int cons_num);
    VectorXd GetValues() const override;
    void init_num(int state_num,int agent_num,int dec_num,int point_num
                  ) const ;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;

    mutable double consta;
    mutable int statenum;
    mutable int agentnum;
    mutable int decnum;
    mutable Eigen::MatrixXd posset;
};

#endif // PATH_POINT_CONSTRAIN_H
