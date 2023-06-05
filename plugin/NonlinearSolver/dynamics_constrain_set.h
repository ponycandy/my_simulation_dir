#ifndef DYNAMICS_CONSTRAIN_SET_H
#define DYNAMICS_CONSTRAIN_SET_H
#include <ifopt/constraint_set.h>
#include <NMPC/NMPC_Mat_IJ.h>
#include <NMPC/NMPC_ODE.h>
#include <NMPC/NMPC_dynamic_Jacob.h>
#include <NMPC/NMPC_Extra_Constrain.h>
#include "Matrix_sparser.h"
typedef Eigen::SparseMatrix<double> Espmat;
class Dynamics_Constrain_Set: public ifopt::ConstraintSet
{
public:
    Dynamics_Constrain_Set(int constrain_nums);

    // This constraint set just contains 1 constraint, however generally
    // each set can contain multiple related constraints.
    void set_cons_num(int statenum, int actnum, int decisionnum) ;
    void registerODE(NMPC_ODE *odefunction) ;
    // The constraint value minus the constant value "1", moved to bounds.
    VectorXd GetValues() const override;
    void getqx() const ;
    void append_constrain()  const ;
    void init_all_mat() ; //这里后面不要添加const，否则会无法改变内变量
    void pack_variable(ifopt::Component::VectorXd x) const;
    // The only constraint in this set is an equality constraint to 1.
    // Constant values should always be put into GetBounds(), not GetValues().
    // For inequality constraints (<,>), use Bounds(x, inf) or Bounds(-inf, x).
    VecBound GetBounds() const override;

    // This function provides the first derivative of the constraints.
    // In case this is too difficult to write, you can also tell the solvers to
    // approximate the derivatives by finite differences and not overwrite this
    // function, e.g. in ipopt.cc::use_jacobian_approximation_ = true
    // Attention: see the parent class function for important information on sparsity pattern.
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void calc_dynamic_constrain_Jacobian() const;
    void init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate);
    Eigen::MatrixXd calc_single_jacobia(int timestep) const;
    void set_use_terminal(bool istrue);
    bool set_terminal_point;
    bool control_bound_flag;
    mutable  Eigen::MatrixXd act_array;//控制量向量，尺寸为：act_num*1
    mutable  Eigen::MatrixXd state_array;//状态量向量，尺寸为：state_num*1
    mutable  Eigen::MatrixXd jac_mat;
    NMPC_Dynamic_Jacob *self_ode_jacob;
    int cons_num;
    int state_num;//状态变量的维度
    int act_num;//控制变量的维度
    int state_num_plus_act_num;
    int total_varaible_num;
    int constrain_num;
    int constrain_num_dynamics;
    int dec_num;//从轨迹开始到结束的总步长
    double steptime; //单位时间步长，典型为30ms


    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable  Eigen::MatrixXd initState;//初始列向量状态向量，尺寸为：state_num*1
    mutable  Eigen::MatrixXd TerminalState;//目标列向量状态向量，尺寸为：state_num*1
    mutable  Eigen::MatrixXd qx;
    mutable  Eigen::MatrixXd B;
    mutable  Eigen::MatrixXd Combined_cons;
    mutable  Eigen::MatrixXd Dynamic_gx_part; //加入mutable确保能够在const下面更改
    mutable  Eigen::MatrixXd D;


    mutable  Espmat s_B;
    mutable  Espmat s_D;

    NMPC_ODE *self_ode;


    mutable  Eigen::MatrixXd jacobian;

    Eigen::MatrixXd m_lower;
    Eigen::MatrixXd m_higher;
    mutable  Eigen::MatrixXd gg;
    mutable  Eigen::MatrixXd gg1;

    mutable  Espmat s_jacobian;
    Espmat s_jacobian2;
    mutable  Espmat jacobian2;
};


#endif // DYNAMICS_CONSTRAIN_SET_H
