#ifndef NMPC_PROBLEM_H
#define NMPC_PROBLEM_H

#include <QObject>
#include "IpTNLP.hpp"
class NMPC_Constructor;
class NMPC_Problem : public QObject,public Ipopt::TNLP
{
    Q_OBJECT
public:
    explicit NMPC_Problem(QObject *parent = nullptr);
    bool get_variables_linearity(Ipopt::Index n, LinearityType *var_types)override;

    bool get_warm_start_iterate(Ipopt::IteratesVector &warm_start_iterate) override;
    bool get_constraints_linearity(Ipopt::Index m, LinearityType *const_types) override;
    bool get_list_of_nonlinear_variables(Ipopt::Index num_nonlin_vars, Ipopt::Index *pos_nonlin_vars) override;
    bool get_scaling_parameters(Ipopt::Number &obj_scaling, bool &use_x_scaling, Ipopt::Index n, Ipopt::Number *x_scaling, bool &use_g_scaling, Ipopt::Index m, Ipopt::Number *g_scaling) override;
    bool intermediate_callback(Ipopt::AlgorithmMode mode, Ipopt::Index iter, Ipopt::Number obj_value, Ipopt::Number inf_pr, Ipopt::Number inf_du, Ipopt::Number mu, Ipopt::Number d_norm, Ipopt::Number regularization_size, Ipopt::Number alpha_du, Ipopt::Number alpha_pr, Ipopt::Index ls_trials, const Ipopt::IpoptData *ip_data, Ipopt::IpoptCalculatedQuantities *ip_cq) override;

    bool eval_f(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Number &obj_value)override;
    bool eval_g(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Index m, Ipopt::Number *g)override;
    bool eval_grad_f(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Number *grad_f) override;


    bool get_bounds_info(Ipopt::Index n, Ipopt::Number *x_l, Ipopt::Number *x_u, Ipopt::Index m, Ipopt::Number *g_l, Ipopt::Number *g_u) override;
    bool get_nlp_info(Ipopt::Index &n, Ipopt::Index &m, Ipopt::Index &nnz_jac_g, Ipopt::Index &nnz_h_lag, IndexStyleEnum &Index_style)override;
    bool eval_jac_g(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Index m, Ipopt::Index nele_jac, Ipopt::Index *iRow, Ipopt::Index *jCol, Ipopt::Number *values)override;
    bool get_starting_point(Ipopt::Index n, bool init_x, Ipopt::Number *x, bool init_z, Ipopt::Number *z_L, Ipopt::Number *z_U, Ipopt::Index m, bool init_lambda, Ipopt::Number *lambda) override;


    bool eval_h(Ipopt::Index n, const Ipopt::Number *x, bool new_x, Ipopt::Number obj_factor, Ipopt::Index m, const Ipopt::Number *lambda, bool new_lambda, Ipopt::Index nele_hess, Ipopt::Index *iRow, Ipopt::Index *jCol, Ipopt::Number *values)override;
    void finalize_solution(Ipopt::SolverReturn status, Ipopt::Index n, const Ipopt::Number *x, const Ipopt::Number *z_L, const Ipopt::Number *z_U, Ipopt::Index m, const Ipopt::Number *g, const Ipopt::Number *lambda, Ipopt::Number obj_value, const Ipopt::IpoptData *ip_data, Ipopt::IpoptCalculatedQuantities *ip_cq) override;
    NMPC_Constructor *nmpc;
signals:

};

#endif // NMPC_PROBLEM_H
