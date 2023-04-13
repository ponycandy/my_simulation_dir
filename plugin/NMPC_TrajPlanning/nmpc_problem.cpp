#include "nmpc_problem.h"
#include "nmpc_constructor.h"
NMPC_Problem::NMPC_Problem(QObject *parent) : QObject(parent)
{
}


bool NMPC_Problem::get_variables_linearity(Ipopt::Index n, Ipopt::TNLP::LinearityType *var_types)
{
    return false;
}

bool NMPC_Problem::get_warm_start_iterate(Ipopt::IteratesVector &warm_start_iterate)
{
    return true;
}

bool NMPC_Problem::get_constraints_linearity(Ipopt::Index m, Ipopt::TNLP::LinearityType *const_types)
{
    return true;
}
bool NMPC_Problem::get_list_of_nonlinear_variables(Ipopt::Index num_nonlin_vars, Ipopt::Index *pos_nonlin_vars)
{
    return true;
}
bool NMPC_Problem::get_scaling_parameters(Ipopt::Number &obj_scaling, bool &use_x_scaling, Ipopt::Index n, Ipopt::Number *x_scaling, bool &use_g_scaling, Ipopt::Index m, Ipopt::Number *g_scaling)
{
    return true;
}
bool NMPC_Problem::intermediate_callback(Ipopt::AlgorithmMode mode, Ipopt::Index iter, Ipopt::Number obj_value, Ipopt::Number inf_pr, Ipopt::Number inf_du, Ipopt::Number mu, Ipopt::Number d_norm, Ipopt::Number regularization_size, Ipopt::Number alpha_du, Ipopt::Number alpha_pr, Ipopt::Index ls_trials, const Ipopt::IpoptData *ip_data, Ipopt::IpoptCalculatedQuantities *ip_cq)
{
    return true;
}
bool NMPC_Problem::eval_f(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Number &obj_value)
{
    obj_value =nmpc->calc_cost(x);//每个周期只被解包一次
    return true;
}

bool NMPC_Problem::eval_g(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Index m, Ipopt::Number *g)
{

    nmpc->calc_gx_dynamic(g,x,new_x);
//已经验证了正确性........虽然还是好慢

    return true;
}

bool NMPC_Problem::eval_grad_f(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Number *grad_f)
{
    // return the gradient of the objective function grad_{x} f(x)

    nmpc->Eval_grad_f(new_x,grad_f,x);

    return true;
}


bool NMPC_Problem::get_bounds_info(Ipopt::Index n, Ipopt::Number *x_l, Ipopt::Number *x_u, Ipopt::Index m, Ipopt::Number *g_l, Ipopt::Number *g_u)
{


    nmpc->setBound(x_l,x_u,g_l,g_u);

    return true;
}

bool NMPC_Problem::get_nlp_info(Ipopt::Index &n, Ipopt::Index &m, Ipopt::Index &nnz_jac_g, Ipopt::Index &nnz_h_lag, Ipopt::TNLP::IndexStyleEnum &Index_style)
{

    n=nmpc->getVariablenum();
    m=nmpc->getConstrainNum(); //包含所有动力学约束和终点约束
//nn——jac_h是不是也得赋值才行？不然就是-261241当然会造成内存溢出
    nnz_h_lag=0;
//    nnz_jac_g=0;
    nnz_jac_g=nmpc->get_jac_g_num();//共有dec_num个period，每个period都有导数
    //做实验确定最快
    Index_style = FORTRAN_STYLE;
    //果然是这个问题吗...........
    //可是,h这样计算真的可以吗
    //此外，我们想要一个自动梯度计算的库
    //不然就只能先接受每次都需要手动生成jacobian

    return true;
}

bool NMPC_Problem::eval_jac_g(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Index m, Ipopt::Index nele_jac, Ipopt::Index *iRow, Ipopt::Index *jCol, Ipopt::Number *values)
{
    if (values == NULL)
    {
        //告知求解器,jacobian是几行几列的
        //这里jacobian左端的表头是g(x)，上端的表头是x1,x2。。。。。
        //这里要把所有不为空的jacobian全部占满(注意，所谓的non_zero是指
        //所有我们填入了值的矩阵位置，而不是真的非0位置)

        nmpc->Constrain_Jac_index_confirm(iRow,jCol);
    }
    else
    {
        //填入jacob矩阵
        nmpc->calc_Dynamic_Jacob_overall(new_x,x,values);
    }
//好歹是没有报成功了，说明动力学约束已经加载上了
    return true;
}

bool NMPC_Problem::get_starting_point(Ipopt::Index n, bool init_x, Ipopt::Number *x, bool init_z, Ipopt::Number *z_L, Ipopt::Number *z_U, Ipopt::Index m, bool init_lambda, Ipopt::Number *lambda)
{
    nmpc->InitStart_point(x);

    return true;
}


bool NMPC_Problem::eval_h(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Number obj_factor, Ipopt::Index m, const Ipopt::Number *lambda, bool new_lambda, Ipopt::Index nele_hess, Ipopt::Index *iRow, Ipopt::Index *jCol, Ipopt::Number *values)
{
    //我们暂时不用hession矩阵，这个矩阵在
    //NMPC中的求解是非常困难的,现有做法是不使用automated differentiation

    return true;
}



void NMPC_Problem::finalize_solution(Ipopt::SolverReturn status, Ipopt::Index n, const Ipopt::Number *x, const Ipopt::Number *z_L, const Ipopt::Number *z_U, Ipopt::Index m, const Ipopt::Number *g, const Ipopt::Number *lambda, Ipopt::Number obj_value, const Ipopt::IpoptData *ip_data, Ipopt::IpoptCalculatedQuantities *ip_cq)
{
    nmpc->finalize_result(x);
}
