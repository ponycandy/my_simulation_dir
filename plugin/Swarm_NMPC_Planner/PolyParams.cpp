#include "PolyParams.h"
//#define NDEBUG
//假想参数单元：每个object的变量在不同的constrain var类里面(下面对应一个agent)
//每个dim的值为x0,x1,dx0,dx1,T
//全部变量组的假想构成是：dim(1),dim(2),dim(3).....
//上面称作一组变量
//每个polyparams对象含有N组变量
//N为三次曲线的维度
#include <xmlcore.h>
#include <Matrix_sparser.h>
PolyParams::PolyParams()
{
    configfiename="./config/Polys/constrainParams.xml";
    constrainIndex=1;
}

void PolyParams::initilization()
{
    xmlCore xml_reader(configfiename.toStdString());
    QString var_name_x="dim_1_x";
    QString var_name_dx="dim_1_dx";
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",point_num);
    xml_reader.xmlRead("step_time",steptime);
    double x0;
    double dx0;
    unit_length=2*dims+1;
    Eigen::MatrixXd init_curve;
    init_curve.resize(dims,2);
    xml_reader.xmlRead("InitCurve",init_curve);
    for(int j=0;j<dims;j++)
    {
        Spline new_dim;
        for(int p=0;p<point_num;p++)
        {
            pos_and_derivative an_epoch;
            new_dim.insert(p,an_epoch);
        }
        new_dim[0].x0=init_curve(j,0);
        new_dim[0].dx0=init_curve(j,1);
        Spline_Set.insert(j,new_dim);
    }
    local_mat_2_params.resize(dims,2*unit_length);

}


void PolyParams::rearrange()
{
    //清空Map
    QMap<double,double> pNullMap;
    QMap<double,int> pNullMap_1;
    time_2_summuptime_map.clear();
    time_2_phase_map.clear();
    time_2_summuptime_map.swap(pNullMap);
    time_2_phase_map.swap(pNullMap_1);
    Spline x_set=Spline_Set.value(0);
    pos_and_derivative first_epoch=x_set.value(0);
    //按照绝对值进行分类
    double current_time=0;
    double phase_time_summup=0;
    int phase=0;
    double phase_time_summup_signed=0;
    for(int i=0;i<point_num;i++)
    {
        time_2_summuptime_map.insert(i,phase_time_summup_signed);
        phase_time_summup_signed+=x_set.value(i).lasting_time;
    }
    for(int i=0;i<dec_num;i++)
    {
        phase=0;
        phase_time_summup=abs(x_set.value(0).lasting_time);
        current_time=steptime*i;
        for(int j=0;j<point_num;j++)
        {
            if(current_time<phase_time_summup)
            {
                time_2_phase_map.insert(current_time,phase);
                break;
            }
            else
            {
                phase+=1;
                phase_time_summup+=abs(x_set.value(phase).lasting_time);
                if(phase==point_num-1)
                {
                    time_2_phase_map.insert(current_time,phase);
                    break;
                }
            }
        }
    }
    //    qDebug()<<"max phase is:"<<phase;
    //    if(phase>2)
    //    {
    //        qDebug()<<"max phase exceeded!";
    //    }
    //当优化中间过程的lasting time为负数的时候，上面的过程会失效，所以，我们必须在优化条件中加入时间必须大于零的约束！
    //
    Init_Curve_Params();

}

void PolyParams::Get_Poly_Value_Mat(Eigen::MatrixXd &Polymat)
{
    double current_time=0;
    for(int i=0;i<dec_num;i++)
    {
        for(int j=0;j<dims;j++)
        {
            Get_Single_Value(current_time,Polymat(j,i), j);
        }
        current_time+=steptime;
    }
}

void PolyParams::Copy_Dense_2_Jac(Eigen::SparseMatrix<double, Eigen::RowMajor> &jac_block, Eigen::MatrixXd &mat, int decN)
{
    int rows=mat.rows();
    int cols=mat.cols();
    int phase=time_2_phase_map.value(decN*steptime);
    int startrow=0;
    int startcol=0;

    if(phase==0)
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=2*dims+1;j<cols;j++)
            {

                jac_block.coeffRef(i+startrow,j-(2*dims+1)) += mat(i,j);
            }
        }
    }
    else
    {
        startrow=(constrainIndex-1)*rows;
        startcol=(phase-1)*unit_length;
        //这个乘法错了，不是乘以cols，而是乘以一般长度
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {

                jac_block.coeffRef(i+startrow,j+startcol) += mat(i,j);

            }
        }
    }
}

void PolyParams::Init_Curve_Params()
{
    for(int dm=0;dm<dims;dm++)
    {
        for(int p=0;p<point_num;p++)
        {
            pos_and_derivative x_set=Spline_Set.value(dm).value(p);
            double T0=x_set.lasting_time;
            x_set.a0=x_set.x0;
            x_set.a1=x_set.dx0;
            x_set.a2=-(3*(x_set.x0-x_set.x1)+T0*(2*x_set.dx0+x_set.dx1))/(T0*T0);
            x_set.a3=(2*(x_set.x0-x_set.x1)+T0*(x_set.dx0+x_set.dx1))/(T0*T0*T0);
            Spline_Set[dm][p]=x_set;
        }
    }
}

void PolyParams::Get_Single_Jacobian_form_2(double currenttime, Eigen::MatrixXd &jacmat, LastintTimeDerivative &timederive)
{
    //此处的矩阵是曲线value按照以下排列方式求导：
    //x0dx0y0dy0Tx1dx1y1dy1
    //按照以上方式排列的变量
    //只求一个时间点的jacob
    //此处考虑对初始状态点的求导
    //jacmat的尺寸：列：2*（2*dim+1）-1
    //行：dims
    jacmat.setZero();
    double a2x0;
    double a2x1;
    double a2dx0;
    double a2dx1;
    double a2T;
    int dim_T1=2*(2*dims+1)-1;
    int dim_T0=(2*dims+1)-1;
    for(int dm=0;dm<dims;dm++)
    {
        Get_Single_derivative(currenttime,dm,
                              a2x0, a2x1,
                              a2dx0,a2dx1,
                              a2T,timederive.derve_value[dm]);
        jacmat(dm,2*dm)=a2x0;
        jacmat(dm,2*dm+1)=a2dx0;
        jacmat(dm,2*dims+1+2*dm)=a2x1;
        jacmat(dm,2*dims+1+2*dm+1)=a2dx1;
        jacmat(dm,dim_T1)=a2T;
    }
    //下面填充额外的时间导数序列
}


void PolyParams::Get_pos_and_derivative_set(int phase, pos_and_derivative &set, int dim)
{
    Spline x_set=Spline_Set.value(dim);
    set=x_set.value(phase);
}

void PolyParams::Get_Single_Value(double currenttime, double &value, int dim)
{
    int phase=time_2_phase_map.value(currenttime);
    pos_and_derivative set;
    Get_pos_and_derivative_set(phase, set,dim);
    double T0;
    T0=currenttime-time_2_summuptime_map.value(phase);
    value=set.a0+T0*(set.a1+T0*(set.a2+set.a3*T0));
}

double PolyParams::Get_Single_value_any(double currenttime, int dim)
{
    int phase=0;
    for(int i=0;i<point_num;i++)
    {
        if(currenttime<time_2_summuptime_map.value(i))//默认时间是大于0的
        {
            phase=i;
            break;
        }
    }
    pos_and_derivative set;
    Get_pos_and_derivative_set(phase, set,dim);
    double T0;
    T0=currenttime-time_2_summuptime_map.value(phase);
    return set.a0+T0*(set.a1+T0*(set.a2+set.a3*T0));

}

double PolyParams::Get_Single_Speed_any(double currenttime, int dim)
{
    int phase=0;
    for(int i=0;i<point_num;i++)
    {
        if(currenttime<time_2_summuptime_map.value(i))//默认时间是大于0的
        {
            phase=i;
            break;
        }
    }
    pos_and_derivative set;
    Get_pos_and_derivative_set(phase, set,dim);
    double T0;
    T0=currenttime-time_2_summuptime_map.value(phase);
    return set.a1+T0*(2*set.a2+3*set.a3*T0);
}

void PolyParams::Get_Single_derivative(double currenttime,
                                       int dim, double &a2x0, double &a2x1, double &a2dx0, double &a2dx1, double &a2T, single_dim &a_dim)
{
    int phase=time_2_phase_map.value(currenttime);
    pos_and_derivative set;
    Get_pos_and_derivative_set(phase, set,dim);
    double T0;
    T0=currenttime-time_2_summuptime_map.value(phase);


    double a0=set.a0;
    double a1=set.a1;
    double a2=set.a2;
    double a3=set.a3;
    double x0=set.x0;
    double x1=set.x1;
    double dx0=set.dx0;
    double dx1=set.dx1;

    double Tl=set.lasting_time;
    //动作求解有问题，使用的时间不是相对0时间，而是总时间
    //下面为对当前phase的所有导数,这个没有问题
    double dAdt_1=T0*T0/(Tl*Tl)*(6*(x0-x1)/Tl+2*dx0+dx1);
    double dAdt_2=-T0*T0*T0/(Tl*Tl*Tl)*(6*(x0-x1)/Tl+2*dx0+2*dx1);
    a2T=dAdt_1+dAdt_2;
    a2x0=1-3*pow((T0/Tl),2)+2*pow((T0/Tl),3);
    a2dx0=T0-2*T0*T0/Tl+T0*T0*T0/(Tl*Tl);
    a2x1=3*pow((T0/Tl),2)-2*pow((T0/Tl),3);
    a2dx1=-T0*T0/Tl+T0*T0*T0/(Tl*Tl);
    //下面为对之前所有phase对应延续时间的导数
    //考虑到解耦，放在其它位置实现
    a_dim.dim_now=dim;
    a_dim.phase_now=phase;
    double dxdTi=0;
    double fi=0;
    for(int i=0;i<phase;i++)
    {
        fi=1;
        a_dim.derivevalue.insert(i,-a1*fi-2*a2*fi*T0-3*a3*fi*T0*T0);
        //实质上就是在目标位置上的导数
    }
}

void PolyParams::FillinJacobian(Eigen::SparseMatrix<double, Eigen::RowMajor> &jacmat_2_go, Jac_Group &First_derive)
{
    int dec=0;

    Eigen::MatrixXd midmat;
    Eigen::MatrixXd midmat_Ti;
    Eigen::MatrixXd T_mat;
    T_mat.resize(dims,1);
    T_mat.setZero();
    LastintTimeDerivative timederive;
    timederive.init(dims);

    Matrix_sparser m_sparse;
    int rows=0;
    for(int i=0;i<First_derive.total_Jac_num;i++)
    {
        dec=First_derive.jac_sets[i].relative_2_dec;
        timederive.phaseNow=time_2_phase_map.value(dec*steptime);
        Get_Single_Jacobian_form_2(dec*steptime, local_mat_2_params,timederive);
        midmat=First_derive.jac_sets[i].jacobian*local_mat_2_params;
        rows=midmat.rows();
        Copy_Dense_2_Jac(jacmat_2_go,midmat,dec);
        //下面填充额外的导数序列
        //导数序列照样需要乘法
        for(int j=0;j<timederive.phaseNow;j++)
        {
            for(int k=0;k<dims;k++)
            {
                T_mat(k,0)=timederive.derve_value[k].derivevalue[j];
            }
            midmat_Ti=First_derive.jac_sets[i].jacobian*T_mat;
            //计算Ti对应所在时间的列为：(phase+1)*unit_length-1
            m_sparse.Copy_Mat_2_Sparse_block(jacmat_2_go,midmat_Ti,(constrainIndex-1)*rows,(j+1)*unit_length-1,rows,1);

        }
        timederive.clear();
    }
    constrainIndex+=1;
}

void PolyParams::packvariable(Eigen::VectorXd &x)
{

    for(int i=0;i<point_num;i++)
    {
        if(i>0)
        {
            for(int dm=0;dm<dims;dm++)
            {
                PointInfo start;
                PointInfo endp;

                Spline_Set[dm][i].x0=x(2*dm+unit_length*(i-1)+0);
                Spline_Set[dm][i].x1=x(2*dm+unit_length*i+0);
                Spline_Set[dm][i].dx0=x(2*dm+unit_length*(i-1)+1);
                Spline_Set[dm][i].dx1=x(2*dm+unit_length*i+1);
                Spline_Set[dm][i].lasting_time=x(unit_length*(i+1)-1);
                Spline_Set[dm][i].total_phase_num=point_num;
                start.point_value=Spline_Set[dm][i].x0;
                start.point_derivative=Spline_Set[dm][i].dx0;
                start.point_value_index=2*dm+unit_length*(i-1)+0;
                start.point_derivative_index=2*dm+unit_length*(i-1)+1;

                endp.point_value=Spline_Set[dm][i].x1;
                endp.point_derivative=Spline_Set[dm][i].dx1;
                endp.point_value_index=2*dm+unit_length*i+0;
                endp.point_derivative_index=2*dm+unit_length*i+1;

                Spline_Set[dm][i].lasting_time_index=unit_length*(i+1)-1;
                Spline_Set[dm][i].start_point=start;
                Spline_Set[dm][i].end_point=endp;

                //                这个是绝对正确的
            }
        }
        else
        {
            //请在外部使用xml文本初始化0处的参数,具体参数排列方式参考参数说明
            //初始化应该在initilization()后面发生
            for(int dm=0;dm<dims;dm++)
            {
                PointInfo start;
                PointInfo endp;
                Spline_Set[dm][i].x1=x(2*dm+0);
                Spline_Set[dm][i].dx1=x(2*dm+1);
                Spline_Set[dm][i].lasting_time=x(unit_length-1);
                Spline_Set[dm][i].total_phase_num=point_num;
                //x0的初始化使用外部文本搞定
                start.point_value=Spline_Set[dm][i].x0;
                start.point_derivative=Spline_Set[dm][i].dx0;
                start.point_value_index=-1;//不存在
                start.point_derivative_index=-1;//不存在

                endp.point_value=Spline_Set[dm][i].x1;
                endp.point_derivative=Spline_Set[dm][i].dx1;
                endp.point_value_index=2*dm+0;
                endp.point_derivative_index=2*dm+1;

                Spline_Set[dm][i].lasting_time_index=(unit_length-1);
                Spline_Set[dm][i].start_point=start;
                Spline_Set[dm][i].end_point=endp;
            }

        }
    }
    rearrange();
}

void PolyParams::clearconstrainindex()
{
    constrainIndex=1;
}

void PolyParams::FillinJacobian_complete(Eigen::SparseMatrix<double, Eigen::RowMajor> &jacmat_2_go)
{
    constrainIndex=1;
    jacmat_2_go.makeCompressed();
}

double PolyParams::dxdti_calc(double phase_now, double i_phase)
{
    if(phase_now>i_phase)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
