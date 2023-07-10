#ifndef MASS_CENTER_CONSTRAIN_H
#define MASS_CENTER_CONSTRAIN_H
#include <QObject>
#include "ifopt/cost_term.h"
#include "PolyParams.h"
class mass_center_constrain:public ifopt::ConstraintSet
{
public:
    mass_center_constrain(int num);
    VectorXd GetValues() const override;
    void init_num(int state_num,int agent_num,int dec_num,int pointnum,double step) const ;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void FillinG(Eigen::VectorXd &g) const;
    void formactmat() const;

    mutable QVector<PolyParams> m_polys;
    mutable QVector<Eigen::MatrixXd> ActMats;
    mutable int statenum;
    mutable int agentnum;
    mutable int actnum;
    mutable int dims;
    mutable int pointnum;
    mutable int decnum;
    mutable int current_agent;
    mutable Eigen::MatrixXd states;
    mutable Eigen::MatrixXd actMat;
    mutable double minimalD;


};

#endif // MASS_CENTER_CONSTRAIN_H
