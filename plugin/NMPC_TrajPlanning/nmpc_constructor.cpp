#include "nmpc_constructor.h"
#include <math.h>
#include "QtDebug"
#include <nmpc_problem.h>
//本例中所有的矩阵都必须稀疏化以加快运行速度
//但是当前为了可读性和方便编写，暂时用的都是原型dense 矩阵
NMPC_Constructor::NMPC_Constructor(QObject *parent) : QObject(parent)
{
    m_sparser=new Matrix_sparser;
    value_map_index_constrain_jac=0;
    control_bound_flag=0;
    m_problem=new NMPC_Problem;
    m_problem->nmpc=this;

    m_problem_dash=m_problem;

    ipopt_solver = new Ipopt::IpoptApplication;
    Ipopt::ApplicationReturnStatus status;
    status = ipopt_solver->Initialize();
    if (status != Ipopt::Solve_Succeeded)
    {
        qDebug()<<("\n\n*** Error during initialization!\n");

    }

}

void NMPC_Constructor::reinitialize()
{
    //想一想，如果需要添加其它的约束，写jacob的时候，如何快速获得action和state的index
    //这是实现高效封包的关键
    //生成与total_variable_num等长数组
    //生成triplet数组的绝佳位置：dynamic_jacob_fill

}

void NMPC_Constructor::finalize_result(const Ipopt::Number *x)
{
    UnpackOptimizerVector(x);
//    qDebug()<<"done";
}

void NMPC_Constructor::init_steptime(double time)
{
    steptime=time;
}

void NMPC_Constructor::init_all_mat()
{
    Matrix_sparser a_sparser;
    int x_pos=0;
    int y_pos=0;
    a_sparser.clearall();

//qx是dense矩阵
    qx.resize(2*state_num*dec_num,1);
    qx.setZero();

    //jac_mat是dense矩阵
    jac_mat.resize(state_num,state_num_plus_act_num);
    jac_mat.setZero();

//Dynamic_gx_part是dense矩阵
    Dynamic_gx_part.resize(constrain_num_dynamics,1);
    Dynamic_gx_part.setZero();

//Combined_cons是ense矩阵
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
    //D是sparse矩阵
    D.resize(state_num,state_num_plus_act_num*dec_num);D.setZero();
    a_sparser.setsize(state_num_plus_act_num*dec_num,state_num);
    for(int i=0;i<state_num;i++)
    {
        a_sparser.fillin(state_num-1-i,state_num_plus_act_num*dec_num-1-i,1);
        D(state_num-1-i,state_num_plus_act_num*dec_num-1-i)=1;

    }
    s_D=a_sparser.get_sparse_mat();
    a_sparser.clearall();
    //gg都是sparse矩阵
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
    s_gg1=a_sparser.get_sparse_mat();
    a_sparser.clearall();


    for(int k=0;k<state_num;k++)
    {
        x_pos=k;
        y_pos=k+act_num;
        a_sparser.fillin(x_pos,y_pos,1);
        gg(x_pos,y_pos)=1;
    }
    s_gg=a_sparser.get_sparse_mat();
    a_sparser.clearall();
    //初始化qx矩阵
    //jacobian是sparse矩阵
    a_sparser.setsize(dec_num*state_num_plus_act_num,2*state_num*dec_num);
    jacobian.resize(2*state_num*dec_num,dec_num*state_num_plus_act_num);
    jacobian.setZero();
//jacobian2是sparse矩阵
    a_sparser.setsize(dec_num*state_num_plus_act_num,state_num*(dec_num+1));
    jacobian2.resize(state_num*(dec_num+1),dec_num*state_num_plus_act_num);
    jacobian2.setZero();
    int start_x,start_y;
    for(int i=0;i<state_num;i++)
    {
        start_x=state_num*(dec_num+1)-i -1;
        start_y=state_num_plus_act_num*dec_num-i -1;

        jacobian2(start_x,start_y)=1;
    }

    value_mat_trans_x.clear();
    value_mat_trans_y.clear();
}

NMPCservice *NMPC_Constructor::clone_service()
{
    NMPCservice *newservice=new NMPC_Constructor;
    return newservice;
}

void NMPC_Constructor::registerODE(NMPC_ODE *odefunction)
{

    self_ode=odefunction;
}

void NMPC_Constructor::set_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{
    //例子 如果控制量为[X;X]，那么lower就为[lower1;lower2],higher就为[higher1;higher2]
    m_lower=lower;
    m_higher=higher;
    control_bound_flag=1;
}

void NMPC_Constructor::registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob)
{
    //此处的jacob，需要注意上端表头，是act在前，state在后，组成的statenum+actnum长度表头
    self_ode_jacob=Dynamic_Jacob;
}

void NMPC_Constructor::register_constrain(NMPC_Extra_Constrain *constrain)
{

}



void NMPC_Constructor::solve_problem()
{
    //大部分的时间花在function evaluation上了（也就是这里的矩阵计算）
    //在矩阵计算里面的时间大概是优化器里面时间的四倍，所以这一点若能够优化
    //就能够做出极高速度的NMPC控制器
    ipopt_solver->Options()->SetNumericValue("tol",1e-4);
    //轨迹规划问题有时不需要那么高的规划精度，-3~-4就够了
    //    ipopt_solver->Options()->SetStringValue("linear_solver","ma77");
    //    ipopt_solver->Options()->SetStringValue("linear_solver","ma27");
    ipopt_solver->Options()->SetStringValue("linear_solver","ma57");
    //一般来说，我们的常用问题尺度下，MA57性能最佳
    //    ipopt_solver->Options()->SetStringValue("linear_solver","ma86");
    //    ipopt_solver->Options()->SetStringValue("linear_solver","ma97");
    //    ipopt_solver->Options()->SetStringValue("linear_solver","pardisomkl");
    //    ipopt_solver->Options()->SetStringValue("linear_solver","mumps");

    Ipopt::ApplicationReturnStatus status = ipopt_solver->OptimizeTNLP(m_problem_dash);

    if (status == Ipopt::Solve_Succeeded)
    {
        // Retrieve some statistics about the solve
        Ipopt::Index iter_count = ipopt_solver->Statistics()->IterationCount();
        QString textnow;
        qDebug()<<"\n\n*** The problem solved in "+QString::number(iter_count)+" iterations!\n";

    }
    //    暂时只能看结果，没有做成控制器
}

void NMPC_Constructor::init_num(int statenum, int actnum, int decisionnum)
{
    state_num=statenum;
    act_num=actnum;
    dec_num=decisionnum;
    state_num_plus_act_num=actnum+statenum;
    constrain_num=dec_num*statenum;
    constrain_num_dynamics=constrain_num;
    total_varaible_num=state_num_plus_act_num*dec_num;
    actMat.resize(actnum,dec_num);
    stateMat.resize(statenum,dec_num);
    actMat.setZero();
    stateMat.setZero();
    Eigen::MatrixXd randoms;
    init_all_x(0,randoms);

    init_all_mat();
}

//以下函数不需要在调用服务的地方使用，
//此时会使用默认初始化方式

void NMPC_Constructor::init_all_x(int method, Eigen::MatrixXd input)
{
    //输入input不一定是初始的所有矩阵，有可能是几个初始点，随机种子
    //这样，用户既可以在外部从最底层实现x的初始化，也可以使用
    //服务中预先定义的初始化方式
    //也可以在服务中添加其它的通用初始化方式（比如说正态初始化）
    if(method==0)
    {
        init_all_variable.resize(total_varaible_num,1);
        init_all_variable.setZero();

    }
    if(method==1)
    {
        init_all_variable.resize(total_varaible_num,1);
        init_all_variable=input;
    }


}

void NMPC_Constructor::init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate)
{
    initState=initstate;
    TerminalState=terminalstate;

}

void NMPC_Constructor::UnpackOptimizerVector(const Ipopt::Number *opt_x)
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
                actMat(actIndex,current_time_step)=opt_x[i-1];
                i=i+1;
            }
            act_vec_flag=1;
        }
        else
        {
            for(int stateIndex=0;stateIndex<state_num;stateIndex++)
            {
                stateMat(stateIndex,current_time_step)=opt_x[i-1];
                i=i+1;
            }
            act_vec_flag=0;
            current_time_step++;
        }
    }

}



Eigen::MatrixXd NMPC_Constructor::calc_single_jacobia(int timestep)
{
    int j=0;
    if(timestep==1)
    {
        act_array=actMat.block(0,0,act_num,1);
        state_array=initState;
        jac_mat=self_ode_jacob->jacobica(act_array,state_array);
        jac_mat=-steptime*jac_mat/2;
        return jac_mat;
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

Eigen::MatrixXd NMPC_Constructor::get_actMat()
{
    return actMat;
}

Eigen::MatrixXd NMPC_Constructor::get_stateMat()
{
    return stateMat;
}

void NMPC_Constructor::InitStart_point(Ipopt::Number *x)
{
    for(int i=0;i<total_varaible_num;i++)
    {
        x[i]=init_all_variable(i,0);
    }
}
void NMPC_Constructor::setBound(Ipopt::Number *x_l, Ipopt::Number *x_u, Ipopt::Number *g_l, Ipopt::Number *g_u)
{
    //动力学恒等约束，包括末端终点态约束
    //后继改动可以把末端终点约束删掉
    for(int i=1;i<=state_num*(dec_num+1);i++)
    {
        g_l[i-1]=0.0;
        g_u[i-1]=0.0;
    }
    //优化变量的约束，必须加，否则默认为0.无解
    //上下界为INf

    for(int i=1;i<=total_varaible_num;i++)
    {
        x_l[i-1]=-1.0e19;
        x_u[i-1]=+1.0e19;
    }

    //如果用户给出了上下界的约束,就在上面的基础上添加
    if(control_bound_flag==1)
    {

        for(int i=1;i<=dec_num;i++)
        {
            for(int j=0;j<act_num;j++)
            {
                x_l[get_action_ipopt_number_index(i,j)]=m_lower(j,0);
                x_u[get_action_ipopt_number_index(i,j)]=m_higher(j,0);
            }

        }
    }
}

Ipopt::Number NMPC_Constructor::calc_cost( const Ipopt::Number *x)
{
    return 0;//暂时没有其他的最优化目标后续再升级这个模块吧
}

void NMPC_Constructor::calc_gx_dynamic(Ipopt::Number *g, const Ipopt::Number *x, bool isnew)
{
    pack_nececssary(isnew,x);
    getqx();
    Dynamic_gx_part=s_B*qx; //这里是稀疏矩阵乘以非稀疏矩阵，得到的是什么？
    append_constrain(0);
    for(int i=0;i<constrain_num_dynamics+state_num;i++)//此处可能有bug,当增加constrain的时候，确保这个数值不能够变动
    {
        g[i]=Combined_cons(i,0);
    }

}

void NMPC_Constructor::getqx()
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
            //上面这句话在matlab中的等效：
            //qx((24*j+1):1:(24*j+24),1)=[elem0;elem1];
        }

    }
}

void NMPC_Constructor::append_constrain(int constrain_method=0)
{
    //添加动力学以外的约束，默认添加终点约束量，也是我们最熟悉的终点约束类型
    if(constrain_method==0)
    {
        //一般来说，不要对所有的终点变量都约束死
        //所以最好还是使用自定义的register_constrain对象来计算终点约束

        //        cons=[cv;y(1,end)-xf;y(2,end)-yf;y(3,end)-zf;y(4,end)-vxf;y(5,end)-vyf;y(6,end)-vzf;y(7,end)-alphaf;y(8,end)-betaf;y(9,end)-gamaf;y(10,end)-pf;y(11,end)-qf;y(12,end)-rf];
        Combined_cons.setZero();
        Combined_cons<<Dynamic_gx_part,stateMat.block(0,dec_num-1,state_num,1)-TerminalState;

    }
}

void NMPC_Constructor::calc_Dynamic_Jacob_overall(bool isnew,const Ipopt::Number *x, Ipopt::Number *values)
{

    //当然，我们希望后面添加其它的约束
    //目前暂时只使用动力学约束
    pack_nececssary(isnew,x);
    UnpackOptimizerVector(x);
    calc_dynamic_constrain_Jacobian();
    int x_cor;
    int y_cor;
    for(int i=0;i<value_map_index_constrain_jac;i++)
    {
        x_cor=value_mat_trans_x.value(i)-1;
        y_cor=value_mat_trans_y.value(i)-1;//-1是因为实际数据位置为C_Style的
        //插入方法错误，导致x,y均为超级负数或者超级大
        values[i]=jacobian2(x_cor,y_cor);
    }
}


void NMPC_Constructor::calc_dynamic_constrain_Jacobian()
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
    Eigen::MatrixXd mid=s_B*s_jacobian;
    jacobian2<<mid,D;
    //考虑到这里，进行重新计算：
}

void NMPC_Constructor::Eval_grad_f(bool isnew, Ipopt::Number *grad_f, const Ipopt::Number *x)
{
    pack_nececssary(isnew,x);//在所有的eval之前判断是否需要重新解包
    calc_cost_jacbobia();
    for(int i=0;i<total_varaible_num;i++)
    {
        grad_f[i]=jac_mat_cost(0,i);
    }
}


void NMPC_Constructor::pack_nececssary(bool isnew,const Ipopt::Number *x)
{
    if(isnew)
    {
        UnpackOptimizerVector(x);
    }
    else
    {

    }
}

int NMPC_Constructor::get_action_ipopt_number_index(int time_step, int action_index)
{
    //控制变量是按照u x u x相间给出的
    return state_num_plus_act_num*(time_step-1)+action_index;
}

void NMPC_Constructor::calc_cost_jacbobia()
{
    jac_mat_cost.resize(1,total_varaible_num);
    jac_mat_cost.setZero();
}

Ipopt::Index NMPC_Constructor::getVariablenum()
{
    return total_varaible_num;
    //    //    x0=zeros(16*n,1);% 最好令初始化的区间接近于目标区间，0初始化只是为了方便
}
Ipopt::Index NMPC_Constructor::getConstrainNum()
{
    return constrain_num+state_num;
}

Ipopt::Index NMPC_Constructor::get_jac_g_num()
{

    int num= dec_num*2*(state_num*state_num_plus_act_num)
              -state_num*state_num_plus_act_num+state_num;
    //从matlab的jac计算的，基本能够保证正确性，用的是实验法，这样最可靠

    return num;
}

void NMPC_Constructor::Constrain_Jac_index_confirm(Ipopt::Index *iRow, Ipopt::Index *jCol)
{
    int start_x=0;//第几行
    int start_y=0;//第几列
    int j=0;
    //以下矩阵从1开始
    value_map_index_constrain_jac=0;//记录jac的对应映射
    //并且生成sparse矩阵所需三元组
    for(int i=1;i<=dec_num;i++)
    {
        if (i<dec_num)
        {
            start_y+=state_num_plus_act_num;
            start_x+=state_num;
            fill_in_jac_cons(state_num*(i-1),state_num_plus_act_num*(i-1),iRow,jCol);

        }
        else
        {
            for(int raws=1;raws<=state_num;raws++)
            {
                for(int cols=1;cols<=state_num_plus_act_num;cols++)
                {
                    mat_ij *ijpair=new mat_ij;
                    ijpair->x=raws+start_x;
                    ijpair->y=cols+start_y;
                    iRow[value_map_index_constrain_jac]=ijpair->x;
                    jCol[value_map_index_constrain_jac]=ijpair->y;
                    value_mat_trans_x.insert(value_map_index_constrain_jac,ijpair->x);
                    value_mat_trans_y.insert(value_map_index_constrain_jac,ijpair->y);
                    value_map_index_constrain_jac++;
                }
            }
            for(int i=0;i<state_num;i++)
            {
                start_x=state_num*(dec_num+1)-i;
                start_y=state_num_plus_act_num*dec_num-i;
                value_mat_trans_x.insert(value_map_index_constrain_jac,start_x);
                value_mat_trans_y.insert(value_map_index_constrain_jac,start_y);
                iRow[value_map_index_constrain_jac]=start_x;
                jCol[value_map_index_constrain_jac]=start_y;
                value_map_index_constrain_jac++;
            }





            //这个是最后一块单位矩阵（final state）
        }

    }




}

void NMPC_Constructor::fill_in_jac_cons(int start_x, int start_y, Ipopt::Index *iRow, Ipopt::Index *jCol)
{
    //此处记录value[n]到jac[x,y]的映射！！
    for(int raws=1;raws<=2*state_num;raws++)
    {
        for(int cols=1;cols<=state_num_plus_act_num;cols++)
        {
            mat_ij ijpair;
            ijpair.x=raws+start_x;
            ijpair.y=cols+start_y;
            iRow[value_map_index_constrain_jac]=ijpair.x;
            jCol[value_map_index_constrain_jac]=ijpair.y;
            value_mat_trans_x.insert(value_map_index_constrain_jac,ijpair.x);
            value_mat_trans_y.insert(value_map_index_constrain_jac,ijpair.y);

            value_mat_trans.insert(value_map_index_constrain_jac,&ijpair);
            mat_value_trans.insert(&ijpair,value_map_index_constrain_jac);
            value_map_index_constrain_jac++;
        }
    }
}

void NMPC_Constructor::generate_g_jac_sparse()
{
    std::vector<Eigen::Triplet<double>> tripletList;
    //    tripletList.reserve(estimation_of_entries);
    //保留的大致entries数目，要稍大于实际数目，防止错误
    for(int i=0;i<value_map_index_constrain_jac;i++)
    {
        // ...
        tripletList.push_back(Eigen::Triplet<double>(
            value_mat_trans_x.value(i),
            value_mat_trans_y.value(i),
            1));
    }
    //生成jacob的占位符
}
