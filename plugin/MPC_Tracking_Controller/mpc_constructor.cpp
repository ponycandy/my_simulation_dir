﻿#include "mpc_constructor.h"
#include "QObject"

//我们更多的采用dynamics program的方法来计算矩阵
//类似matlab那样的解析形式(close form)并不是必须的
MPC_Constructor::MPC_Constructor(QObject *parent)
{
    solver=new OsqpEigen::Solver;
    solver->settings()->setVerbosity(false);
    ref_count=0;
    ref_count_local=0;
    leanrflag=0;
}

void MPC_Constructor::set_ref_target(Eigen::MatrixXd state)
{
    Eigen::MatrixXd realstate;
    realstate.resize(state_num,dec_num);
    for(int i=0;i<dec_num;i++)
    {
        realstate.block(0,i,state_num,1)=state;
    }
    set_reference(realstate,realstate,false);
}

void MPC_Constructor::set_reference(Eigen::MatrixXd state, Eigen::MatrixXd action, bool use_action)
{
    act_ref_all=action;
    ifuseaction=use_action;
    if(use_action==true)
    {
        total_predict_length=state.cols();
        //        total_predict_length=state.cols()+1;//最后面补一个平衡态参考
        //        state_ref_all.resize(state_num,total_predict_length);
        //        state_ref_all<<state,state.block(0,state.cols()-1,state_num,1);
        state_ref_all=state;
        //        Eigen::MatrixXd Equblieum;
        //        Equblieum.resize(act_num,1);
        //        Equblieum.setZero();
        //        act_ref_all.resize(act_num,total_predict_length);
        //        act_ref_all<<action,Equblieum;
        act_ref_all=action;
        last_control=action.block(0,0,act_num,1);
        //提供一个设置平衡态的接口，一般来说都设置为0
        //考虑以下的可变性：如果reference中提供平衡态的
        //控制量，上面的矩阵就需要可变
        //但是考虑到当前暂时没有这种生成轨迹的方式，暂时默认使用平衡态....
    }
    else
    {
        total_predict_length=state.cols();
        state_ref_all=state;
        for(int i=0;i<dec_num;i++)
        {
            act_ref_all.block(0,i,act_num,1)=last_control;
        }

    }
    state_ref=state_ref_all;


}



void MPC_Constructor::init_steptime(double time)
{
    steptime=time;
}

void MPC_Constructor::init_all_mat()
{
    steptime=0.03;
    Matrix_sparser A_cons_sparser;
    A_cons_sparser.setsize(dec_num*act_num,2*dec_num*act_num);
    Matrix_sparser   s_HQp_sparser;
    s_HQp_sparser.setsize(dec_num*act_num,dec_num*act_num);
    s_HQp=s_HQp_sparser.get_sparse_mat();

    int xpos_start=0;
    int ypos_start=0;
    for(int i=1;i<=dec_num;i++)
    {
        for(int j=1;j<=act_num;j++)
        {

            A_cons_sparser.fillin(xpos_start,xpos_start,1);

            xpos_start+=1;
        }

    }
    for(int i=1;i<=dec_num;i++)
    {
        for(int j=1;j<=dec_num;j++)
        {
            if(i>=j)
            {
                for(int ii=0;ii<act_num;ii++)
                {
                    A_cons_sparser.fillin(ii+xpos_start,ii+ypos_start,1);
                }

            }
            ypos_start+=act_num;
        }
        ypos_start=0;
        xpos_start+=act_num;
    }
    s_A_cons=A_cons_sparser.get_sparse_mat();
    Eigen::MatrixXd temps_A=s_A_cons;
    X_eq.resize(dec_num*state_num+state_num,1);
    X_eq.setZero();
    Y_ref.resize(dec_num*(state_num+act_num),1);
    Y_ref.setZero();
    init_x_u_ref.resize(state_num+act_num,1);
    init_x_u_ref.setZero();
    last_control.resize(act_num,1);
    last_control.setZero();
    H_obs.resize(state_num+act_num,state_num+act_num);
    H_obs.setIdentity();
    Matrix_sparser s_H_OBS_sparser;s_H_OBS_sparser.setsize(state_num+act_num,state_num+act_num);
    for(int j=0;j<state_num+act_num;j++)
    {

        s_H_OBS_sparser.fillin(j,j,1);

    }
    s_H_OBS=s_H_OBS_sparser.get_sparse_mat();
    Qx_ref.resize(state_num,1);
    lower_deltau.resize(act_num,1);
    lower_deltau.setZero();
    high_deltau.resize(act_num,1);
    high_deltau.setZero();
    lower_u.resize(act_num,1);
    lower_u.setZero();
    high_u.resize(act_num,1);
    high_u.setZero();
    xRef.resize(state_num,1);
    xRef.setZero();
    act_ref.resize(act_num,dec_num);
    act_ref.setZero();
    Q.resize(state_num);
    Q.setIdentity(state_num); //default configuration
    Q=Q*10;
    R.resize(act_num);
    R.setIdentity(act_num); //default configuration
    calc_weight();
    dynamicMatrix.resize(state_num,state_num);dynamicMatrix.setZero();
    controlMatrix.resize(state_num,act_num);controlMatrix.setZero();
    lowerBound = Eigen::MatrixXd::Zero( act_num * dec_num*2, 1);

    upperBound = Eigen::MatrixXd::Zero(act_num * dec_num*2, 1);
    xinit.resize(state_num,1);
    xinit.setZero();
    Identity_A.resize(state_num,state_num);
    Identity_A.setIdentity();

    state_l.resize(state_num,1);
    state_l.setOnes();
    state_l=-9999*state_l;//默认无限制
    state_h=-state_l;

    lower_u.resize(act_num,1);
    lower_u.setOnes();
    lower_u=-9999*lower_u;//默认无限制
    high_u=-lower_u;


    high_deltau.resize(act_num,1);
    high_deltau.setOnes();
    high_deltau=9999*high_deltau;//默认无限制
    lower_deltau=-high_deltau;
    int counter=0;
    int length1=dec_num*act_num;
    for(int ii=0;ii<dec_num;ii++)
    {
        lowerBound.block(counter,0,act_num,1)=lower_deltau;
        upperBound.block(counter,0,act_num,1)=high_deltau;

        lowerBound.block(counter+length1,0,act_num,1)=lower_u-last_control;
        upperBound.block(counter+length1,0,act_num,1)=high_u-last_control;

        counter+=act_num;
    }


}

MPC_Trackerservice *MPC_Constructor::clone_service()
{
    MPC_Constructor *new_service=new MPC_Constructor;
    return new_service;
}

void MPC_Constructor::calc_predict()
{
    //神奇的是，我这个控制器
    //尽管还是有漏洞
    //竟然还是要比学弟的控制器性能更好......
    Matrix_sparser PHI_sparse;PHI_sparse.setsize(state_num+act_num,dec_num*(state_num+act_num));
    Matrix_sparser THETA_sparse; THETA_sparse.setsize(dec_num*(state_num+act_num),dec_num*(state_num+act_num));
    Matrix_sparser B_b_sparse;B_b_sparse.setsize(dec_num*(act_num),dec_num*(state_num+act_num));
    Matrix_sparser C_c_sparse;C_c_sparse.setsize(act_num,dec_num*(state_num+act_num));
    Eigen::MatrixXd temp_A;
    Eigen::MatrixXd A_power;
    temp_A.resize(state_num+act_num,state_num+act_num);
    temp_A=A_m_list.value(1);
    for(int i=1;i<=dec_num;i++)
    {
        if (i >= 2)
        {
            temp_A = A_m_list.value(i)*temp_A;
        }
        //        PHI_sparse.add_mat_block( s_H_OBS*temp_A,(state_num+act_num)*(i-1),0);
        //总是设置s_H_OBS为单位矩阵，大部分情况下我们不做这一次乘法
        PHI_sparse.add_mat_block(temp_A,(state_num+act_num)*(i-1),0);
        for(int  j = 1;j<=dec_num;j++)
        {
            if (i >= j)
            {
                //                A_power=s_H_OBS*Tandemride_A_list(j+1,i);//j==i的时候，也就是说所
                //j+1>i，这个时候，上面的连乘法取单位矩阵
                //总是设置s_H_OBS为单位矩阵，大部分情况下我们不做这一次乘法
                A_power=Tandemride_A_list(j+1,i);
                THETA_sparse.add_mat_block(A_power,(i-1)*(state_num+act_num),
                                           (j-1)*(state_num+act_num));
            }

        }
        C_c_sparse.add_mat_block(C_m_list.value(i),(i-1)*(state_num+act_num),0);
        B_b_sparse.add_mat_block(B_m_list.value(i),(i-1)*(state_num+act_num),(i-1)*(act_num));

        //(i-1)*(state_num+act_num)
    }

    s_PHI = PHI_sparse.get_sparse_mat();
    s_THETA = THETA_sparse.get_sparse_mat();
    s_B_b = B_b_sparse.get_sparse_mat();
    s_C_c = C_c_sparse.get_sparse_mat();

}

void MPC_Constructor::calc_weight()
{
    Matrix_sparser Q_sparser;
    Matrix_sparser R_sparser;
    R_sparser.setsize(dec_num*act_num,dec_num*act_num);
    Q_sparser.setsize(dec_num*(state_num+act_num),dec_num*(state_num+act_num));
    int count=0;
    int count_r=0;
    for(int i=0;i<dec_num;i++)
    {
        for(int j=0;j<state_num;j++)
        {
            Q_sparser.fillin(count,count, Q.diagonal()[j]);
            count+=1;
        }
        for(int j=0;j<act_num;j++)
        {
            R_sparser.fillin(count_r,count_r, R.diagonal()[j]);
            count_r+=1;
            count+=1;
        }
    }
    s_Q=Q_sparser.get_sparse_mat();
    s_R=R_sparser.get_sparse_mat();
}

void MPC_Constructor::calc_bound()
{

    int counter=0;
    int length1=dec_num*act_num;
    for(int ii=0;ii<dec_num;ii++)
    {
        lowerBound.block(counter+length1,0,act_num,1)=lower_u-last_control;
        upperBound.block(counter+length1,0,act_num,1)=high_u-last_control;
        counter+=act_num;
    }

}

Eigen::MatrixXd MPC_Constructor::feed_Back_control(Eigen::MatrixXd state)
{
    //从这里开始是控制了，开始构建！

    xref_move_toward();
    xinit=state;
    init_x_u_ref<<xinit,last_control;
    clear_ABC_list();


    fill_in_ABC();
    calc_predict();
    calc_bound();
    calc_H_q_cons();




    // set the initial data of the QP solver

    solver->updateHessianMatrix(s_HQp);//H_Qp需要稀疏化
    solver->updateGradient(f_Qp.transpose());
    solver->updateUpperBound(upperBound);
    solver->updateLowerBound(lowerBound);


    // instantiate the solver

    // controller input and QPSolution vector

    Eigen::VectorXd QPSolution;

    // solve the QP problem
    solver->solveProblem() ;
    if (solver->solveProblem() == OsqpEigen::ErrorExitFlag::NoError)
    {
        // get the controller input
        QPSolution = solver->getSolution();
        last_control=last_control+QPSolution.block(0, 0, act_num, 1);

        last_mv_seqc.block(0,0,act_num,1)=last_control
                                               + QPSolution.block(1*act_num, 0, act_num, 1);//已经添加过的！
        for(int i=1;i<dec_num-1;i++)
        {
            last_mv_seqc.block(0,i,act_num,1)=
                last_mv_seqc.block(0,i-1,act_num,1)+
                QPSolution.block(i*act_num+act_num, 0, act_num, 1);
        }
        last_mv_seqc.block(0,dec_num-1,act_num,1)=
            last_mv_seqc.block(0,dec_num-2,act_num,1);


        return last_control;
    }
    else
    {
        return last_control;
    }
}


void MPC_Constructor::registerODE(MPC_ODE *odefunction)
{
    M_ode_funtor=odefunction;
}

void MPC_Constructor::fill_in_ABC()
{
    dynamicMatrix_temp=dynamicMatrix;
    controlMatrix_temp=controlMatrix;
    X_eq.block(0,0,state_num,1)=xinit;
    for(int i=1;i<=dec_num;i++)
    {
        Eigen::MatrixXd u_eq =act_ref.block(0,i-1,act_num,1);
        //act_ref全部取上一个控制量堆叠，或者取NMPC的控制预测
        Eigen::MatrixXd current_state;
        Eigen::MatrixXd d_state;

        current_state=X_eq_list.value(i);
        X_eq.block(state_num*i,0,state_num,1)=current_state;
        M_ode_funtor->get_A_and_B(u_eq,current_state,dynamicMatrix_temp,controlMatrix_temp);

        dynamicMatrix=Identity_A+dynamicMatrix_temp*steptime;
        controlMatrix=controlMatrix_temp*steptime;
        d_state = M_ode_funtor->ode_function(u_eq,current_state);
        Eigen::MatrixXd C_m;

        C_m.resize(state_num+act_num,1);C_m.setZero();
        C_m.block(0,0,state_num,1) = (d_state-dynamicMatrix_temp*current_state-controlMatrix_temp*u_eq)*steptime;
        current_state=current_state+d_state*steptime;
        X_eq_list.insert(i+1,current_state);
        Eigen::MatrixXd A_m;//A不能进行sparse化，否则会导致后面的计算出现问题
        Eigen::MatrixXd B_m;
        A_m.resize(state_num+act_num,state_num+act_num);A_m.setZero();
        B_m.resize(state_num+act_num,act_num);B_m.setZero();
        A_m.block(0,0,state_num,state_num)=dynamicMatrix;
        A_m.block(0,state_num,state_num,act_num)=controlMatrix;
        B_m.block(0,0,state_num,act_num)=controlMatrix;
        for(int i=0;i<act_num;i++)
        {
            A_m(state_num+act_num-1-i,state_num+act_num-1-i)=1;
            B_m(state_num+act_num-1-i,act_num-1-i)=1;
        }
        A_m_list.insert(i,A_m);
        B_m_list.insert(i,B_m);
        C_m_list.insert(i,C_m);

    }

}

void MPC_Constructor::calc_H_q_cons()
{
    Eigen::MatrixXd sbtemp=s_B_b;
    Eigen::MatrixXd s_THETAtemp=s_THETA;
    Eigen::MatrixXd s_Qtemp=s_Q;
    Eigen::MatrixXd s_Rtemp=s_R;
    Eigen::MatrixXd s_PHItemp=s_PHI;
    Eigen::MatrixXd s_C_ctemp=s_C_c;

    H_Qp = s_B_b.transpose()*s_THETA.transpose()*s_Q*s_THETA*s_B_b + s_R;//计算有问题
    Eigen::MatrixXd E = s_PHI*init_x_u_ref+ s_THETA*s_C_c -Y_ref;//Y_ref:纵向堆叠的状态列向量
    f_Qp =2* E.transpose()*s_Q*s_THETA*s_B_b;
    Matrix_sparser HQP_sparser;
    s_HQp=HQP_sparser.make_dense_sparse(H_Qp);
}

Eigen::MatrixXd MPC_Constructor::Tandemride_A_list(int start, int end)
{
    Eigen::MatrixXd multiA;
    multiA.resize(state_num+act_num,state_num+act_num);
    multiA.setIdentity();
    if(start>end)
    {
        return multiA;
    }
    else
    {
        if(iterationhead.contains(start))
        {
            multiA=iterationhead.value(start);
            multiA=A_m_list.value(end)*multiA;
            iterationhead.insert(start,multiA);
            return multiA;
        }
        else
        {

            multiA=A_m_list.value(start);

            iterationhead.insert(start,multiA);
            return multiA;
        }
    }
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
    calc_weight();

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
    int counter=0;
    int length1=dec_num*act_num;
    for(int ii=0;ii<dec_num;ii++)
    {
        lowerBound.block(counter,0,act_num,1)=lower_deltau;
        upperBound.block(counter,0,act_num,1)=high_deltau;

        lowerBound.block(counter+length1,0,act_num,1)=lower_u-last_control;
        upperBound.block(counter+length1,0,act_num,1)=high_u-last_control;

        counter+=act_num;
    }

}

void MPC_Constructor::set_delta_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{

}




bool MPC_Constructor::xref_move_toward()
{
    //这里的移动规则是，不断平移所有的参考状态（不包括控制状态）
    //一般来说，在终点阈值以后，参考轨迹均为最后一个点
    //一个重大的bug：实际上线性化预测高度依赖于
    //act_ref，所以，如果是纯NMPC预测的轨迹
    //如果不带有维持平衡点处所需的reference_act
    //那么，最后一个last_control会大的可怕
    //进而可能造成无法维持重点状态
    //所以，在setreference的时候，务必在后面补一个平衡态的actref....
    //state_ref也务必补一个平衡态的ref

    //另一个可行的方法是
    //当ref_count+dec_num>=total_predict_length的时候
    //也就是开始载入非reference部分的时候
    //更改优化问题的尺寸，不再进行全序列优化
    //也不太行，最大的困难是确定平衡态的尺寸和位置
    //或许可以在邻近终点的时候减小预测步长
    int pointer=ref_count;
    //    if(ref_count+dec_num>=total_predict_length)
    //    {
    //        qDebug()<<1;
    //    }
    if(ifuseaction)
    {
        if(ref_count<total_predict_length)
        {
            int pointer_1=pointer;
            if(ifuseaction)
            {
                last_control=act_ref_all.block(0,pointer,act_num,1);
            }

            for(int i=0;i<dec_num;i++)
            {

                if(pointer_1>=total_predict_length-1)
                {
                    //                    act_ref.block(0,i,act_num,1)=
                    //                        act_ref_all.block(0,pointer_1,act_num,1);
                    act_ref.block(0,i,act_num,1)=
                        last_mv_seqc.block(0,i,act_num,1);
                }
                else
                {
                    act_ref.block(0,i,act_num,1)=
                        act_ref_all.block(0,pointer_1,act_num,1);
                    pointer_1+=1;
                }
            }
        }
        else
        {
            for(int i=0;i<dec_num;i++)
            {
                //所以轨迹规划必须包含一部分平衡的轨迹
                //  不然就要后面补....
                act_ref.block(0,i,act_num,1)=
                    last_control;
                //            act_ref.block(0,i,act_num,1)<<0;
            }
        }
    }
    else
    {
        act_ref=last_mv_seqc;
    }



    for(int i=0;i<dec_num;i++)
    {
        //        Y_ref.block(i*(state_num+act_num)+state_num,0,act_num,1)
        //            = act_ref.block(0,i,act_num,1);
        Y_ref.block(i*(state_num+act_num)+state_num,0,act_num,1)<<0;
    }
    if(ref_count<total_predict_length)
    {
        for(int i=0;i<dec_num;i++)
        {
            Y_ref.block(i*(state_num+act_num),0,state_num,1)=
                state_ref_all.block(0,pointer,state_num,1);
            //            Y_ref.block(i*(state_num+act_num)+state_num,0,act_num,1)
            //                = act_ref_all.block(0,pointer,act_num,1);
            if(pointer>=total_predict_length-1)
            {

            }
            else
            {
                pointer+=1;
            }
        }
        ref_count++;

    }
    //    else
    //    {

    //    }
    return true;
}

void MPC_Constructor::clear_ABC_list()
{
    QVector<Eigen::MatrixXd> pNullVector;  //局部变量
    QVector<Eigen::MatrixXd> pNullVector2;  //局部变量
    QVector<Eigen::MatrixXd> pNullVector4;  //局部变量
    QVector<Eigen::MatrixXd> pNullVector3;  //局部变量
    QVector<Eigen::MatrixXd> pNullVector5;  //局部变量
    QMap<int , Eigen::MatrixXd> pNullVector6;
    A_m_list.clear(); B_m_list.clear(); C_m_list.clear(); X_eq_list.clear();
    Trade_list.clear();
    A_m_list.swap(pNullVector);
    B_m_list.swap(pNullVector2);
    C_m_list.swap(pNullVector4);
    X_eq_list.swap(pNullVector3);//要线性化的一系列点
    Trade_list.swap(pNullVector5);
    iterationhead.swap(pNullVector6);
    X_eq_list.insert(0,xinit);
    X_eq_list.insert(1,xinit);
    A_m_list.insert(0,xinit);
    B_m_list.insert(0,xinit);
    C_m_list.insert(0,xinit);
    Trade_list.insert(0,xinit);
    iterationhead.insert(0,xinit);
}


void MPC_Constructor::init_num(int statenum, int actnum, int decisionnum)
{
    state_num=statenum;
    act_num=actnum;
    dec_num=decisionnum;

    last_mv_seqc.resize(act_num,dec_num);
    last_mv_seqc.setZero();
    init_all_mat();

    solver->data()->setNumberOfVariables(act_num*dec_num);
    solver->data()->setNumberOfConstraints(act_num*dec_num*2);
    solver->settings()->setWarmStart(true);

    // dec_num*(act_num)
    Eigen::MatrixXd temp_qp;
    temp_qp.resize(dec_num*(act_num),1);
    solver->data()->setHessianMatrix(s_HQp);//H_Qp需要稀疏化
    solver->data()->setGradient(temp_qp);
    solver->data()->setLinearConstraintsMatrix(s_A_cons);

    solver->data()->setLowerBound(lowerBound);
    solver->data()->setUpperBound(upperBound);

    // instantiate the solver
    solver->initSolver();

}
