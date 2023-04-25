#include "mpc_constructor.h"
#include "QObject"
MPC_Constructor::MPC_Constructor(QObject *parent)
{
    solver=new OsqpEigen::Solver;
    ref_count=0;
    ref_count_local=0;
}

void MPC_Constructor::set_reference(Eigen::MatrixXd state, Eigen::MatrixXd action, bool use_action)
{
    if(use_action==true)
    {
        state_ref=state;

    }
    else
    {
        state_ref=state;
        act_ref=action;
    }
}



void MPC_Constructor::init_steptime(double time)
{
    steptime=time;
}

void MPC_Constructor::init_all_mat()
{
    Qx_ref.resize(state_num,1);
    lower_deltau.resize(act_num,1);lower_deltau.setZero();
    high_deltau.resize(act_num,1);high_deltau.setZero();
    lower_u.resize(act_num,1);lower_u.setZero();
    high_u.resize(act_num,1);high_u.setZero();
    xRef.resize(state_num,1);xRef.setZero();
    constraintMatrix.resize(state_num * (dec_num + 1) +
                                state_num * (dec_num + 1) + act_num * dec_num, state_num * (dec_num + 1) + act_num * dec_num);
    Q.resize(state_num);Q.setIdentity(); //default configuration
    R.resize(act_num);R.setIdentity(); //default configuration
    dynamicMatrix.resize(state_num,state_num);dynamicMatrix.setZero();
    controlMatrix.resize(state_num,act_num);controlMatrix.setZero();
    castMPCToQPHessian();
    lowerBound = Eigen::MatrixXd::Zero(2 * state_num * (dec_num + 1) + act_num * dec_num, 1);
    upperBound = Eigen::MatrixXd::Zero(2 * state_num * (dec_num + 1) + act_num * dec_num, 1);
    xinit.resize(state_num,1);
    xinit.setZero();
    Identity_A.resize(state_num,state_num);
    Identity_A.setIdentity();
}

MPC_Trackerservice *MPC_Constructor::clone_service()
{
    MPC_Constructor *new_service=new MPC_Constructor;
    return new_service;
}

Eigen::MatrixXd MPC_Constructor::feed_Back_control(Eigen::MatrixXd state, bool *is_end)
{
    //从这里开始是控制了，开始构建！
    xref_move_toward();
    castMPCToQPGradient();
    castMPCToQPConstraintMatrix();
    castMPCToQPConstraintVectors();

    solver->settings()->setWarmStart(true);

    // set the initial data of the QP solver
    solver->data()->setNumberOfVariables(12 * (dec_num + 1) + 4 * dec_num);
    solver->data()->setNumberOfConstraints(2 * 12 * (dec_num + 1) + 4 * dec_num);
    solver->data()->setHessianMatrix(hessianMatrix);
    solver->data()->setGradient(gradient);
    solver->data()->setLinearConstraintsMatrix(constraintMatrix);
    solver->data()->setLowerBound(lowerBound);
    solver->data()->setUpperBound(upperBound);

    // instantiate the solver
    solver->initSolver();

    // controller input and QPSolution vector


    Eigen::VectorXd QPSolution;

    // solve the QP problem
    solver->solveProblem() ;

    // get the controller input
    QPSolution = solver->getSolution();
    return QPSolution.block(state_num * (dec_num + 1), 0, act_num, 1);
}

void MPC_Constructor::registerODE(MPC_ODE *odefunction)
{
    M_ode_funtor=odefunction;
}

void MPC_Constructor::setWeightMatrices(Eigen::MatrixXd Q_in, Eigen::MatrixXd R_in)
{
    int Q_width=Q_in.rows();
    int R_width=R_in.rows();
    Q.resize(Q_width);Q.setZero();
    R.resize(R_width);R.setZero();
    for(int i=0;i<Q_width;i++)
    {
        Q.diagonal()[i]=Q_in(i,i);
    }
    for(int i=0;i<R_width;i++)
    {
        R.diagonal()[i]=R_in(i,i);
    }

    gradient = Eigen::VectorXd::Zero(state_num * (dec_num + 1) + act_num * dec_num, 1);

}

void MPC_Constructor::set_state_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{
    state_l=lower;
    state_h=higher;
}

void MPC_Constructor::set_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{
    lower_u=lower;
    high_u=higher;
}

void MPC_Constructor::set_delta_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{

}

void MPC_Constructor::castMPCToQPHessian()
{
    hessianMatrix.resize(state_num * (dec_num + 1) + act_num * dec_num, state_num * (dec_num + 1) + act_num * dec_num);

    //populate hessian matrix
    for (int i = 0; i < state_num * (dec_num + 1) + act_num * dec_num; i++) {
        if (i < state_num * (dec_num + 1)) {
            int posQ = i % state_num;
            float value = Q.diagonal()[posQ];
            if (value != 0)
                hessianMatrix.insert(i, i) = value;
        }
        else {
            int posR = i % act_num;
            float value = R.diagonal()[posR];
            if (value != 0)
                hessianMatrix.insert(i, i) = value;
        }
    }
}

void MPC_Constructor::castMPCToQPGradient()//这一步必须反复迭代，因为gradient随着变化的追踪状态而变化
{
    gradient.setZero();
    //这一步不对，不想要单独的xRef，想要全部的ref
    int posQ =0;
    float value = 0;
    ref_count_local=0;
    for(int i = 0; i < (dec_num + 1); i++)
    {
        feed_xref();
        Qx_ref = Q * (-xRef);
        for(int j = 0; j < state_num; i++)
        {
            value = Qx_ref(j, 0);
            gradient(posQ, 0) = value;
            posQ+=1;
        }
    }
}

void MPC_Constructor::feed_xref()
{
    xRef=state_ref.block(0,ref_count_local,state_num,1);
    ref_count_local+=1;
}

bool MPC_Constructor::xref_move_toward()
{
    //这里的移动规则是，不断平移所有的参考状态（不包括控制状态）
    //一般来说，在终点阈值以后，参考轨迹均为最后一个点

    int pointer=ref_count;
    if(ref_count<dec_num)
    {
        for(int i=0;i<dec_num;i++)
        {
            state_ref.block(0,i,state_num,1)=
                state_ref_all.block(0,pointer,state_num,1);
        //我们一般不追踪目标动作值,所以不移动act_ref
            if(pointer==dec_num-1)
            {
            }
            else
            {
                pointer+=1;
            }
        }

    }
    else
    {
    //无需更改任何参考矩阵！！
    }
    xinit=state_ref.block(0,0,state_num,1);
    return true;
}

void MPC_Constructor::castMPCToQPConstraintMatrix()
{

    // populate linear constraint matrix
    for (int i = 0; i < state_num * (dec_num + 1); i++)
    {
        constraintMatrix.insert(i, i) = -1;
    }

    for (int i = 0; i < dec_num; i++)
    {
        M_ode_funtor->get_A_and_B(act_ref.block(0,i,act_num,1)
                                  ,state_ref.block(0,i,state_num,1),dynamicMatrix,controlMatrix);
        dynamicMatrix=Identity_A+dynamicMatrix*steptime;
        controlMatrix=controlMatrix*steptime;
        for (int j = 0; j < state_num; j++)
        {
            for (int k = 0; k < state_num; k++)
            {
                double value = dynamicMatrix(j, k); //A矩阵
                if (value != 0) {
                    constraintMatrix.insert(state_num * (i + 1) + j, state_num * i + k) = value;
                }
            }
            for (int k = 0; k < act_num; k++)
            {
                double value = controlMatrix(j, k);
                if (value != 0) {
                    constraintMatrix.insert(state_num * (i + 1) + j,
                                            act_num * i + k + state_num * (dec_num + 1)) = value;
                }
            }
        }
    }

    for (int i = 0; i < state_num * (dec_num + 1) + act_num * dec_num; i++)
    {
        constraintMatrix.insert(i + (dec_num + 1) * state_num, i) = 1;
    }
}

void MPC_Constructor::castMPCToQPConstraintVectors()
{
    Eigen::VectorXd lowerInequality = Eigen::MatrixXd::Zero(state_num * (dec_num + 1) + act_num * dec_num, 1);
    Eigen::VectorXd upperInequality = Eigen::MatrixXd::Zero(state_num * (dec_num + 1) + act_num * dec_num, 1);
    for (int i = 0; i < dec_num + 1; i++)
    {
        lowerInequality.block(state_num * i, 0, state_num, 1) = state_h;
        upperInequality.block(state_num * i, 0, state_num, 1) = state_l;
    }
    for (int i = 0; i < dec_num; i++)
    {
        lowerInequality.block(act_num * i + state_num * (dec_num + 1), 0, act_num, 1) = lower_u;
        upperInequality.block(act_num * i + state_num * (dec_num + 1), 0, act_num, 1) = high_u;
    }

    // evaluate the lower and the upper equality vectors
    Eigen::VectorXd lowerEquality = Eigen::MatrixXd::Zero(state_num * (dec_num + 1), 1);
    Eigen::VectorXd upperEquality;
    lowerEquality.block(0, 0, state_num, 1) = -xinit;
    upperEquality = lowerEquality;
    lowerEquality = lowerEquality;

    // merge inequality and equality vectors
    lowerBound << lowerEquality,
        lowerInequality;

    upperBound << upperEquality,
        upperInequality;
}

void MPC_Constructor::init_num(int statenum, int actnum, int decisionnum)
{
    state_num=statenum;
    act_num=actnum;
    dec_num=decisionnum;


    init_all_mat();

}
