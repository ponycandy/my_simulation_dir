#ifndef DYNAMICS_VARAIBLE_SET_H
#define DYNAMICS_VARAIBLE_SET_H

#include <ifopt/variable_set.h>
class Dynamics_varaible_Set : public ifopt::VariableSet
{
public:
    // Every variable set has a name, here "var_set1". this allows the constraints
    // and costs to define values and Jacobians specifically w.r.t this variable set.
    Dynamics_varaible_Set(int num);

    // Here is where you can transform the Eigen::Vector into whatever
    // internal representation of your variables you have (here two doubles, but
    // can also be complex classes such as splines, etc..
    void SetVariables(const VectorXd& x);
    void init_parents();
    void set_cons_num(int statenum, int actnum, int decisionnum);
    void set_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher);
    int get_action_ipopt_number_index(int time_step, int action_index) const;
    // Here is the reverse transformation from the internal representation to
    // to the Eigen::Vector
    VectorXd GetValues() const override;
    // Each variable has an upper and lower bound set here
    VecBound GetBounds() const override;

    bool control_bound_flag;

    int cons_num;
    int state_num;//状态变量的维度
    int act_num;//控制变量的维度
    int state_num_plus_act_num;
    int total_varaible_num;
    int constrain_num;
    int constrain_num_dynamics;
    int dec_num;//从轨迹开始到结束的总步长

    Eigen::VectorXd all_variable;
    Eigen::MatrixXd m_lower;
    Eigen::MatrixXd m_higher;

};

#endif // DYNAMICS_VARAIBLE_SET_H
