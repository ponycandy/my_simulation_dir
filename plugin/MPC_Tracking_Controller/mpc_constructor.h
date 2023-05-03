#ifndef NMPC_CONSTRUCTOR_H
#define NMPC_CONSTRUCTOR_H

#include <QObject>
#include <QWidget>

#include <Eigen/Core>
#include <Eigen/Sparse>
#include <QMap>
#include <osqp/include/osqp.h>
#include <OsqpEigen/OsqpEigen.h>

#include "service/MPC_Trackerservice.h"
#include "Matrix_sparser.h"
typedef Eigen::SparseMatrix<double> Espmat;
class MPC_Problem;
class MPC_Constructor : public QObject,public MPC_Trackerservice
{
    Q_OBJECT
public:
    explicit
        MPC_Constructor(QObject *parent = nullptr);
    void set_reference(Eigen::MatrixXd state,Eigen::MatrixXd action,bool use_action) override;
    void init_steptime(double time) override;
    void init_all_mat();
    MPC_Trackerservice* clone_service() override;
    void     calc_predict();
    void calc_weight();
    void calc_bound();

    Eigen::MatrixXd feed_Back_control(Eigen::MatrixXd state) override;
    void registerODE(MPC_ODE *odefunction) override;//这个可以通用
    void fill_in_ABC();
    void calc_H_q_cons();
    Eigen::MatrixXd H_Qp;
    int leanrflag=0;
    Eigen::MatrixXd f_Qp;
    Eigen::MatrixXd Y_ref;
    Eigen::MatrixXd init_x_u_ref;
    Eigen::MatrixXd dynamicMatrix_temp;
    Eigen::MatrixXd controlMatrix_temp;
    Eigen::MatrixXd Tandemride_A_list(int start,int end);

    void setWeightMatrices(Eigen::MatrixXd Q, Eigen::MatrixXd R) override;
    void set_state_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    void set_delta_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    //    Eigen::MatrixXd feed_Back_control(Eigen::MatrixXd state,bool *is_end) override;

    void feed_xref();
    bool xref_move_toward();
    void clear_ABC_list();

    void init_num(int statenum, int actnum, int decisionnum) override;
    Eigen::MatrixXd H_obs;
    Eigen::MatrixXd last_control;
    Eigen::MatrixXd lower_u;
    Eigen::MatrixXd lower_deltau;
    Eigen::MatrixXd high_u;
    Eigen::MatrixXd high_deltau;
    Eigen::MatrixXd state_l;
    Eigen::MatrixXd state_h;
    Eigen::MatrixXd state_ref;
    Eigen::MatrixXd state_ref_all;
    Eigen::MatrixXd act_ref;
    Eigen::MatrixXd act_ref_all;

    Eigen::MatrixXd lowerBound;
    Eigen::MatrixXd upperBound;
    Eigen::MatrixXd Identity_A;
    Eigen::MatrixXd Identity_B;
    Eigen::MatrixXd Qx_ref;
    Matrix_sparser *m_sparser;


    Eigen::DiagonalMatrix<double,Eigen::Dynamic> Q;
    Eigen::DiagonalMatrix<double,Eigen::Dynamic> R;
    Eigen::SparseMatrix<double>    s_H_OBS;
    Eigen::SparseMatrix<double>    s_A_cons;
    Eigen::SparseMatrix<double>    s_b_cons;
    Eigen::SparseMatrix<double> s_lb;
    Eigen::SparseMatrix<double> s_ub;
    Eigen::SparseMatrix<double> s_Umax;
    Eigen::SparseMatrix<double> s_Umin;
    Eigen::SparseMatrix<double> s_Q;
    Eigen::SparseMatrix<double> s_R;
Eigen::SparseMatrix<double> s_HQp;
    Eigen::VectorXd  gradient ;
    Eigen::MatrixXd xRef;
    Eigen::MatrixXd xinit;
    Eigen::MatrixXd X_eq;
    Eigen::MatrixXd dynamicMatrix;
    Eigen::MatrixXd controlMatrix;
    Eigen::SparseMatrix<double> constraintMatrix;
    Eigen::SparseMatrix<double> s_PHI;
    Eigen::SparseMatrix<double> s_THETA;
    Eigen::SparseMatrix<double> s_B_b;
    Eigen::SparseMatrix<double> s_C_c;
    QMap<int , Eigen::MatrixXd> iterationhead;
    QVector<Eigen::MatrixXd> Trade_list;;
    QVector<Eigen::MatrixXd> A_m_list;
    QVector<Eigen::MatrixXd> B_m_list;
    QVector<Eigen::MatrixXd> C_m_list;
    QVector<Eigen::MatrixXd> X_eq_list;
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
    Eigen::SparseMatrix<double> hessianMatrix;
    MPC_ODE *M_ode_funtor;

    OsqpEigen::Solver *solver;

    int ref_count;
    int ref_count_local;

signals:

};

#endif // NMPC_CONSTRUCTOR_H
