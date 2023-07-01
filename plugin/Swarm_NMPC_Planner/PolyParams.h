#ifndef POLYPARAMS_H
#define POLYPARAMS_H
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <QVector>
#include <QMap>
#include <QString>
struct PointInfo
{
    int point_value_index;
    int point_value;
    int point_derivative;
    int point_derivative_index;

};
struct single_dim
{
    int phase_now;
    int dim_now;
    QVector<double_t> derivevalue;
};
struct pos_and_derivative
{
    int total_phase_num;
    PointInfo start_point;
    PointInfo end_point;
    double x0;
    double x1;
    double dx0;
    double dx1;
    double lasting_time;
    int lasting_time_index;
    double a0;
    double a1;
    double a2;
    double a3;
};
typedef QVector<pos_and_derivative> Spline;
struct single_jacob
{
    int relative_2_dec;
    Eigen::MatrixXd jacobian;
};
struct Jac_Group
{
    int total_Jac_num;
    QVector<single_jacob> jac_sets;
    void init(int num)
    {
        total_Jac_num=num;
        for(int i=0;i<num;i++)
        {
            single_jacob a_one;
            jac_sets.insert(i,a_one);
        }
    }

};
struct LastintTimeDerivative
{
    int dims;
    int phaseNow;
    QVector<single_dim> derve_value;
    void init(int dm_num)
    {
        dims=dm_num;
        for(int i=0;i<dims;i++)
        {
            single_dim newdim;
            derve_value.insert(i,newdim);
        }
    }
    void clear()
    {
        QVector<single_dim> pNullvec;
        derve_value.clear();
        derve_value.swap(pNullvec);
        init(dims);
    }

};


class  PolyParams
{
public:
    PolyParams();
    void initilization();
    void rearrange();
    void Get_Poly_Value_Mat(Eigen::MatrixXd &Polymat);
    void Copy_Dense_2_Jac(Eigen::SparseMatrix<double, Eigen::RowMajor> &jac_block, Eigen::MatrixXd &mat, int decN);
    void Init_Curve_Params();
    void Get_Single_Jacobian_form_2(double currenttime,Eigen::MatrixXd &jacmat,LastintTimeDerivative &timederive);
    void Get_pos_and_derivative_set(int phase,pos_and_derivative &set, int dim);
    void Get_Single_Value(double currenttime,double &value,int dim);
    double Get_Single_value_any(double currenttime,int dim);
    void Get_Single_derivative(double currenttime,int dim,
                               double &a2x0, double &a2x1, double &a2dx0, double &a2dx1, double &a2T,single_dim &a_dim);
    void FillinJacobian(Eigen::SparseMatrix<double, Eigen::RowMajor> &jacmat_2_go,
                        Jac_Group &First_derive);
    void packvariable(Eigen::VectorXd &x);
    void clearconstrainindex();
    void FillinJacobian_complete(Eigen::SparseMatrix<double, Eigen::RowMajor> &jacmat_2_go);
    double dxdti_calc(double phase_now,double i_phase);
    //输入第一个为整个jacobian，第二个为第一级的导数群，
    //最终，所有的一级导数会被填充到目标雅可比矩阵中
    int dims;
    int dec_num;
    int point_num;
    double steptime;
    int unit_length;
    int constrainIndex;
    QVector<Spline> Spline_Set;
    QMap<double,int> time_2_phase_map;
    QMap<double,double> time_2_summuptime_map;
    QString configfiename;
    Eigen::MatrixXd local_mat_2_params;

};


#endif // POLYPARAMS_H
