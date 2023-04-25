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
    Eigen::MatrixXd feed_Back_control(Eigen::MatrixXd state,bool *is_end) override;
    void registerODE(MPC_ODE *odefunction) override;//这个可以通用
    void setWeightMatrices(Eigen::MatrixXd Q, Eigen::MatrixXd R) override;
    void set_state_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    void set_delta_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;
    //    Eigen::MatrixXd feed_Back_control(Eigen::MatrixXd state,bool *is_end) override;
    void castMPCToQPHessian();
    void castMPCToQPGradient();
    void feed_xref();
    bool xref_move_toward();
    void castMPCToQPConstraintMatrix();
    void castMPCToQPConstraintVectors();
    void init_num(int statenum, int actnum, int decisionnum) override;
    Eigen::MatrixXd lower_u;
    Eigen::MatrixXd lower_deltau;
    Eigen::MatrixXd high_u;
    Eigen::MatrixXd high_deltau;
    Eigen::MatrixXd state_l;
    Eigen::MatrixXd state_h;
    Eigen::MatrixXd state_ref;
    Eigen::MatrixXd state_ref_all;
    Eigen::MatrixXd act_ref;
    Eigen::MatrixXd lowerBound;
    Eigen::MatrixXd upperBound;
Eigen::MatrixXd Identity_A;
    Eigen::MatrixXd Identity_B;

    Eigen::Matrix<double, 1, 1> Qx_ref;
    Matrix_sparser *m_sparser;


    Eigen::DiagonalMatrix<double,1> Q;
    Eigen::DiagonalMatrix<double,1> R;
    Eigen::VectorXd  gradient ;
    Eigen::Matrix<double, 1, 1> xRef;
    Eigen::Matrix<double, 1, 1> xinit;
    Eigen::MatrixXd dynamicMatrix;
    Eigen::MatrixXd controlMatrix;
    Eigen::SparseMatrix<double> constraintMatrix;

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
