#include "dynamics_constrain_set.h"



Dynamics_Constrain_Set::Dynamics_Constrain_Set(int constrain_nums):
    ConstraintSet(constrain_nums, "Dynamics")
{
    set_terminal_point=false;
    control_bound_flag=false;
    cons_num=constrain_nums;



}

void Dynamics_Constrain_Set::set_cons_num(int statenum, int actnum, int decisionnum)
{

    state_num=statenum;
    act_num=actnum;
    dec_num=decisionnum;
    state_num_plus_act_num=actnum+statenum;
    constrain_num=dec_num*statenum;
    constrain_num_dynamics=constrain_num;
    actMat.resize(actnum,dec_num);
    stateMat.resize(statenum,dec_num);
    actMat.setZero();
    stateMat.setZero();
    init_all_mat();
}

void Dynamics_Constrain_Set::registerODE(NMPC_ODE *odefunction)
{
    self_ode=odefunction;
}


ifopt::Component::VectorXd Dynamics_Constrain_Set::GetValues() const
{
    //这个vectorXd就是Eigen里面的Xd注意了
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    pack_variable(x);
    getqx();
    Dynamic_gx_part=s_B*qx; //这里是稀疏矩阵乘以非稀疏矩阵，得到的是dense矩阵
    //下面这两条默认用来处理终点约束的，看情况加，默认不加
    append_constrain();
    if(set_terminal_point==true)
    {

        for(int i=0;i<constrain_num_dynamics+state_num;i++)
        {
            g(i)=Combined_cons(i,0);
        }
    }
    else
    {
        for(int i=0;i<constrain_num_dynamics;i++)
        {
            g(i)=Combined_cons(i,0);
        }
    }

    //这里计算动力学
    return g;
}

void Dynamics_Constrain_Set::getqx() const
{
    int j=0;
    for(int i=1;i<=dec_num;i++)
    {
        if(i==1)
        {

            Eigen::MatrixXd elem0=-initState-
                                    steptime/2*self_ode->ode_function(actMat.block(0,0,act_num,1),initState);
            Eigen::MatrixXd elem1=stateMat.block(0,0,state_num,1)
                                    -steptime/2*self_ode->ode_function(actMat.block(0,0,act_num,1),stateMat.block(0,0,state_num,1));

            qx.block(0,0,(2*state_num),1)<<elem0,elem1;
            //上面这句话在matlab中的等效是：qx(1:1:24,1)=[elem0;elem1];
        }
        else
        {
            j=i-1;
            Eigen::MatrixXd elem0=-stateMat.block(0,j-1,state_num,1)-
                                    steptime/2*self_ode->ode_function(actMat.block(0,j-1,act_num,1),stateMat.block(0,j-1,state_num,1));
            Eigen::MatrixXd elem1=stateMat.block(0,j,state_num,1)-
                                    steptime/2*self_ode->ode_function(actMat.block(0,j,act_num,1),stateMat.block(0,j,state_num,1));


            qx.block(2*state_num*j,0,(2*state_num),1)<<elem0,elem1;
        }

    }
}

void Dynamics_Constrain_Set::append_constrain()  const
{
    Combined_cons.setZero();
    //    if(set_terminal_point)
    //    {
    Combined_cons<<Dynamic_gx_part,stateMat.block(0,dec_num-1,state_num,1)-TerminalState;
    //    }
    //    else
    //    {
    //        Combined_cons<<Dynamic_gx_part;
    //    }
}

void Dynamics_Constrain_Set::init_all_mat()
{
    //以下是纯动力学约束所需的全部矩阵
    Matrix_sparser a_sparser;
    int x_pos=0;
    int y_pos=0;
    a_sparser.clearall();

    //qx是dense矩阵
    qx.resize(2*state_num*dec_num,1);
    qx.setZero();

    //Dynamic_gx_part是dense矩阵
    Dynamic_gx_part.resize(constrain_num_dynamics,1);
    Dynamic_gx_part.setZero();

    //Combined_cons是dense矩阵
    Combined_cons.resize(constrain_num_dynamics+state_num,1);
    Combined_cons.setZero();
    //B是sparse矩阵
    a_sparser.setsize(2*dec_num*state_num,dec_num*state_num);
    for(int i=1;i<=dec_num;i++)
    {
        for(int j=1;j<=2;j++)
        {
            if(j==1)
            {
                for(int k=0;k<state_num;k++)
                {
                    x_pos=state_num*(i-1)+k;
                    y_pos=2*state_num*(i-1)+k;
                    a_sparser.fillin(x_pos,y_pos,1);
                }


            }
            else
            {
                for(int k=0;k<state_num;k++)
                {
                    x_pos=state_num*(i-1)+k;
                    y_pos=2*state_num*(i-1)+k+state_num;
                    a_sparser.fillin(x_pos,y_pos,1);
                }
            }
        }
    }
    s_B=a_sparser.get_sparse_mat();
    a_sparser.clearall();

    //以下为jacobian矩阵计算所需：

    //    SparseMatrix<double> mat(rows,cols);

    D.resize(state_num,state_num_plus_act_num*dec_num);D.setZero();
    a_sparser.setsize(state_num_plus_act_num*dec_num,state_num);
    for(int i=0;i<state_num;i++)
    {
        a_sparser.fillin(state_num-1-i,state_num_plus_act_num*dec_num-1-i,1);
        D(state_num-1-i,state_num_plus_act_num*dec_num-1-i)=1;

    }
    s_D=a_sparser.get_sparse_mat();
    a_sparser.clearall();


    gg1.resize(state_num,state_num_plus_act_num);
    gg.resize(state_num,state_num_plus_act_num);
    gg1.setZero();
    gg.setZero();
    a_sparser.setsize(state_num_plus_act_num,state_num);
    for(int k=0;k<state_num;k++)
    {
        x_pos=k;
        y_pos=k+act_num;
        a_sparser.fillin(x_pos,y_pos,-1);
        gg1(x_pos,y_pos)=-1;
    }
    a_sparser.clearall();


    for(int k=0;k<state_num;k++)
    {
        x_pos=k;
        y_pos=k+act_num;
        a_sparser.fillin(x_pos,y_pos,1);
        gg(x_pos,y_pos)=1;
    }
    a_sparser.clearall();



}

void Dynamics_Constrain_Set::pack_variable(VectorXd opt_x) const
{
    int i=1; //此为opt_x列向量的index,记得调用时减1
    int current_time_step=0;//hint此时矩阵元素所处时刻
    int act_vec_flag=0;
    while (i<=state_num_plus_act_num*dec_num)
    {
        if (act_vec_flag==0)
        {
            for(int actIndex=0;actIndex<act_num;actIndex++)
            {
                actMat(actIndex,current_time_step)=opt_x(i-1);
                i=i+1;
            }
            act_vec_flag=1;
        }
        else
        {
            for(int stateIndex=0;stateIndex<state_num;stateIndex++)
            {
                stateMat(stateIndex,current_time_step)=opt_x(i-1);
                i=i+1;
            }
            act_vec_flag=0;
            current_time_step++;
        }
    }
}

ifopt::Component::VecBound Dynamics_Constrain_Set::GetBounds() const
{
    //全部都是等式约束，所以都用等号
    //当然，更改目的约束也是可以的...
    VecBound b(GetRows());
    int upper=0;
    if(set_terminal_point)
    {
        upper=state_num*(dec_num+1);
    }
    else
    {
        upper=state_num*(dec_num);
    }
    //优化变量的约束，在varaible set里面给出
    for(int i=1;i<=upper;i++)
    {
        b.at(i-1)=ifopt::Bounds(0.0, 0.0);
    }

    return b;
}

void Dynamics_Constrain_Set::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    //填写jacobian矩阵
    if (var_set == "action_state_set1")
    {
        VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
        Matrix_sparser a_sparser;
        pack_variable(x);
        calc_dynamic_constrain_Jacobian();
        //        jac_block=a_sparser.make_dense_sparse(jacobian2.transpose());
        //这里矩阵无需转置，其定义是和我们一致的（参照ifopt的例子）
        //问题是，这里是不能够直接copy整个对象的，而必须单独赋值
        int upper_rows=0;
        int lower_rows=0;
        double value_now=0;
        for (int k=0; k<jacobian2.outerSize(); ++k)
        {
            for (Eigen::SparseMatrix<double>::InnerIterator it(jacobian2,k); it; ++it)
            {
                upper_rows=it.row();
                lower_rows=it.col();
                value_now=it.value();
                //                fillin(it.row(),it.col(),it.value());//不确定这里要不要减1
                jac_block.coeffRef(upper_rows,lower_rows)=value_now;
            }
        }

    }



}

void Dynamics_Constrain_Set::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{

}

void Dynamics_Constrain_Set::calc_dynamic_constrain_Jacobian() const
{
    int j=0;
    //测试用代码
    int x_total_size=0;
    int y_total_size=0;
    //测试用代码
    Matrix_sparser newsparser;

    newsparser.setsize(dec_num*state_num_plus_act_num,2*state_num*dec_num);


    for (int i=1;i<=2*dec_num;i++)
    {
        if (i<=2)
        {
            newsparser.add_mat_block(calc_single_jacobia(i),state_num*(i-1),0);
            //            self_ode_jacob->jacobica(actMat,stateMat);
            //一个block的尺寸是state_num*state_num_plus_act_num
            //总共的block数目：2*dec_num
        }
        else
        {
            j=floor((i+0.1)/2); //+0.1防止程序偶尔出现的bug
            //上面可以近似为除以2向下取整

            newsparser.add_mat_block(calc_single_jacobia(i),state_num*(i-1),state_num_plus_act_num*(j-1));
            //我们希望jacobica不需要再度对此时的步时进行判断,且一般不需要内置任何东西
        }
    }
    s_jacobian=newsparser.get_sparse_mat();
    newsparser.clearall();
    //这里还不太对，需要乘以B矩阵才是真实矩阵
    //所以，总共的非0entry数目为：2*dec_num*state_num*state_num_plus_act_num
    //下面B矩阵为1 1序列阵。
    //    Espmat mid=s_B*s_jacobian;
    jacobian2=s_B*s_jacobian;
    //矩阵乘法的输出取决于输出的类型.....em....
    if(set_terminal_point==true)
    {
        //        jacobian2<<mid,D;
        //这里不再采取上面的方式，计算太过于低效，采取直接赋值1的方法
        //            newsparser.fillin(state_num-1-i,state_num_plus_act_num*dec_num-1-i,1);
        //            jacobian2(state_num-1-i,state_num_plus_act_num*dec_num-1-i)=1;
        //            jacobian2.coeffRef(constrain_num_dynamics+
        //                                   state_num-1-i,state_num_plus_act_num*dec_num-1-i)=1;
        jacobian2=newsparser.stack_vertical_blok(jacobian2,s_D);
    }
    else
    {
        //                jacobian2=mid;
    }

    //考虑到这里，进行重新计算：
}

void Dynamics_Constrain_Set::init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate)
{
    initState=initstate;
    TerminalState=terminalstate;

}

Eigen::MatrixXd Dynamics_Constrain_Set::calc_single_jacobia(int timestep) const
{
    //看来需要小改一下这个
    int j=0;
    if(timestep==1)
    {
        act_array=actMat.block(0,0,act_num,1);
        state_array=initState;
        jac_mat=self_ode_jacob->jacobica(act_array,state_array);
        jac_mat=-steptime*jac_mat/2;
        return jac_mat;//返回值会报错，果然还是矢量问题
    }
    else
    {
        if(timestep%2==0)
        {
            j=floor((timestep+0.1)/2);
            act_array=actMat.block(0,j-1,act_num,1);
            state_array=stateMat.block(0,j-1,state_num,1);
            jac_mat=self_ode_jacob->jacobica(act_array,state_array);
            jac_mat=-steptime*jac_mat/2+gg;
            return jac_mat;

        }
        else
        {
            j=floor((timestep+0.1)/2);
            act_array=actMat.block(0,j-1,act_num,1);
            state_array=stateMat.block(0,j-1,state_num,1);
            jac_mat=self_ode_jacob->jacobica(act_array,state_array);
            jac_mat=-steptime*jac_mat/2+gg1;
            return jac_mat;
        }
    }
}

void Dynamics_Constrain_Set::set_use_terminal(bool istrue)
{
    set_terminal_point=istrue;
    //    if(set_terminal_point==true)
    //    {
    //        jacobian2.resize(state_num*(dec_num+1),dec_num*state_num_plus_act_num);
    //        jacobian2.setZero();
    //        int start_x,start_y;
    //        for(int i=0;i<state_num;i++)
    //        {
    //            start_x=state_num*(dec_num+1)-i -1;
    //            start_y=state_num_plus_act_num*dec_num-i -1;

    //            jacobian2(start_x,start_y)=1;
    //        }
    //    }
    //    else
    //    {
    //        jacobian2.resize(state_num*(dec_num),dec_num*state_num_plus_act_num);
    //        jacobian2.setZero();
    //    }
}
