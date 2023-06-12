#ifndef CLOSE_POINT_CONSTRAIN_H
#define CLOSE_POINT_CONSTRAIN_H
#include "ifopt/constraint_set.h"
#include "PolyParams.h"
class close_point_constrain:public ifopt::ConstraintSet
{
public:
    close_point_constrain(int thisagentorder,int consNum,std::string name);
    VectorXd GetValues() const override;
    void init_num(int state_num,int agent_num,int dec_num) const ;
    VecBound GetBounds() const override;
     void FillinG(Eigen::VectorXd &g);
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
     void formactmat();
    mutable double consta;
    mutable int statenum;
    mutable int actnum;
    mutable int agentnum;
    mutable int decnum;
    mutable Eigen::MatrixXd posset;
    mutable Eigen::MatrixXd actMat;
    mutable QVector<PolyParams> m_polys;
    mutable double radius;
    mutable int self_agent_order;
    mutable int pointnum;
};

#endif // CLOSE_POINT_CONSTRAIN_H
