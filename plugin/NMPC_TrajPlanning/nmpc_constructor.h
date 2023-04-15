#ifndef NMPC_CONSTRUCTOR_H
#define NMPC_CONSTRUCTOR_H

#include <QObject>
#include <QWidget>
#include <NMPC/NMPC_Mat_IJ.h>
#include <NMPC/NMPC_ODE.h>
#include <NMPC/NMPC_dynamic_Jacob.h>
#include <NMPC/NMPC_Extra_Constrain.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include "IpTNLP.hpp"
#include <QMap>
#include "IpIpoptApplication.hpp"
#include "IpSolveStatistics.hpp"
#include "service/NMPCservice.h"
#include "Matrix_sparser.h"
typedef Eigen::SparseMatrix<double> Espmat;
class NMPC_Problem;
class NMPC_Constructor : public QObject,public NMPCservice
{
    Q_OBJECT
public:
    explicit
        NMPC_Constructor(QObject *parent = nullptr);
    void reinitialize();
    void finalize_result(const Ipopt::Number *x);
    void init_steptime(double time) override;
    void init_all_mat();
    NMPCservice* clone_service() override;
    void registerODE(NMPC_ODE *odefunction) override;
    void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    void registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob) override;
    void register_constrain(NMPC_Extra_Constrain *constrain) override;
    void solve_problem() override;
    void init_num(int statenum, int actnum, int decisionnum) override;
    void init_all_x(int method, Eigen::MatrixXd input) override;
    void init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate) override;
    void UnpackOptimizerVector(const Ipopt::Number *opt_x);
    Eigen::MatrixXd calc_single_jacobia(int timestep);
    Eigen::MatrixXd get_actMat() override;
    Eigen::MatrixXd get_stateMat() override;
    void InitStart_point(Ipopt::Number *x);
    void setBound(Ipopt::Number *x_l,Ipopt::Number *x_u,Ipopt::Number *g_l,Ipopt::Number *g_u);
    Ipopt::Number calc_cost(const Ipopt::Number *x);
    void calc_gx_dynamic(Ipopt::Number *g,const Ipopt::Number *x,bool isnew);
    void getqx();
    void append_constrain(int method);
    void calc_Dynamic_Jacob_overall(bool isnew,const Ipopt::Number *x,Ipopt::Number *values);
    void calc_dynamic_constrain_Jacobian();
    void Eval_grad_f(bool isnew,Ipopt::Number *grad_f,const Ipopt::Number *x);
    void calc_cost_jacbobia();
    void pack_nececssary(bool isnew,const Ipopt::Number *x);
    int get_action_ipopt_number_index(int time_step,int action_index);
    Ipopt::Index getVariablenum();
    Ipopt::Index getConstrainNum();
    Ipopt::Index get_jac_g_num();
    void Constrain_Jac_index_confirm(Ipopt::Index *iRow, Ipopt::Index *jCol);
    void fill_in_jac_cons(int start_x,int start_y,Ipopt::Index *iRow, Ipopt::Index *jCol);
    void generate_g_jac_sparse();
    NMPC_ODE *self_ode;
    NMPC_Dynamic_Jacob *self_ode_jacob;
    Ipopt::SmartPtr<Ipopt::IpoptApplication> ipopt_solver;

    QMap<int,mat_ij*> value_mat_trans;
    QMap<mat_ij*,int> mat_value_trans;
    QMap<int,int> value_mat_trans_x;
    QMap<int,int> value_mat_trans_y;

    Matrix_sparser *m_sparser;
    int state_num;//状态变量的维度
    int act_num;//控制变量的维度
    int state_num_plus_act_num;
    int total_varaible_num;
    int constrain_num;
    int constrain_num_dynamics;
    int dec_num;//从轨迹开始到结束的总步长
    int value_map_index_constrain_jac;
    int control_bound_flag;
    double steptime; //单位时间步长，典型为30ms
    Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    Eigen::MatrixXd act_array;//控制量向量，尺寸为：act_num*1
    Eigen::MatrixXd state_array;//状态量向量，尺寸为：state_num*1
    Eigen::MatrixXd jac_mat;//动力学单个雅可比矩阵，尺寸为：state_num*state_num_plus_act_num
    Eigen::MatrixXd initState;//初始列向量状态向量，尺寸为：state_num*1
    Eigen::MatrixXd TerminalState;//目标列向量状态向量，尺寸为：state_num*1
    Eigen::MatrixXd jac_mat_cost;
    Eigen::MatrixXd init_all_variable;
    //对应的mat，顶端的表头为cost（f(x)）左端的表头为opt_x各变量
    //现在，我们暂时不设置任何的cost变量，也想不到这种变量
    //最小化control努力不是很有必要，所以不考虑
    double mat_cost;
    //损失函数标量f(x)值

    Eigen::MatrixXd qx;
    Eigen::MatrixXd B;
    Eigen::MatrixXd D;
    Eigen::MatrixXd Combined_cons;
    Eigen::MatrixXd Dynamic_gx_part;
    Eigen::MatrixXd jacobian;
    Eigen::MatrixXd jacobian2;
    Eigen::MatrixXd m_lower;
    Eigen::MatrixXd m_higher;
    Eigen::MatrixXd gg;
    Eigen::MatrixXd gg1;

    Ipopt::SmartPtr<Ipopt::TNLP> m_problem_dash ;
    NMPC_Problem *m_problem;

    Espmat s_qx;
    Espmat s_B;
    Espmat s_D;
    Espmat s_Combined_cons;
    Espmat s_Dynamic_gx_part;
    Espmat s_jacobian;
    Espmat s_jacobian2;
    Espmat s_m_lower;
    Espmat s_m_higher;
    Espmat s_gg;
    Espmat s_gg1;


signals:

};

#endif // NMPC_CONSTRUCTOR_H
