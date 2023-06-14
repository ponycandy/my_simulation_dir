#include "PolyParams.h"

//假想参数单元：每个object的变量在不同的constrain var类里面(下面对应一个agent)
//每个dim的值为x0,x1,dx0,dx1,T
//全部变量组的假想构成是：dim(1),dim(2),dim(3).....
//上面称作一组变量
//每个polyparams对象含有N组变量
//N为三次曲线的维度
#include <xmlcore.h>
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

    for(int j=0;j<dims;j++)
    {
        Spline new_dim;
        for(int p=0;p<point_num;p++)
        {
            pos_and_derivative an_epoch;
            new_dim.insert(p,an_epoch);
        }

        xml_reader.xmlRead(var_name_x.toStdString(),new_dim[0].x0);
        xml_reader.xmlRead(var_name_dx.toStdString(),new_dim[0].dx0);
        Spline_Set.insert(j,new_dim);
        var_name_x="dim_"+QString::number(j+2)+"_x";
        var_name_dx="dim_"+QString::number(j+2)+"_dx";
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
    double current_time=0;
    double phase_time_summup=first_epoch.lasting_time;
    time_2_summuptime_map.insert(0,0);
    int phase=0;
    for(int i=0;i<dec_num;i++)
    {
        if(current_time<phase_time_summup)
        {
            time_2_phase_map.insert(current_time,phase);
            current_time+=steptime;
        }
        else
        {
            phase+=1;
            time_2_summuptime_map.insert(phase,phase_time_summup);
            first_epoch=x_set.value(phase);
            phase_time_summup+=first_epoch.lasting_time;
            time_2_phase_map.insert(current_time,phase);
            current_time+=steptime;
        }
    }
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
                if( mat(i,j)!=0)
                {
                    jac_block.coeffRef(i+startrow,j-(2*dims+1)) += mat(i,j);
                }
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
                if( mat(i,j)!=0)
                {
                    jac_block.coeffRef(i+startrow,j+startcol) += mat(i,j);
                }
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

void PolyParams::Get_Single_Jacobian_form_2(double currenttime, Eigen::MatrixXd &jacmat)
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
                              a2T);
        jacmat(dm,2*dm)=a2x0;
        jacmat(dm,2*dm+1)=a2dx0;
        jacmat(dm,2*dims+1+2*dm)=a2x1;
        jacmat(dm,2*dims+1+2*dm+1)=a2dx1;
        jacmat(dm,dim_T1)=a2T;
    }
    //最后一个T似乎并用不上
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

void PolyParams::Get_Single_derivative(double currenttime,
                                       int dim, double &a2x0, double &a2x1, double &a2dx0, double &a2dx1, double &a2T)
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
    double dAdt_1=T0*T0/(Tl*Tl)*(6*(x0-x1)/Tl+2*dx0+dx1);
    double dAdt_2=-T0*T0*T0/(Tl*Tl*Tl)*(6*(x0-x1)/Tl+2*dx0+2*dx1);
    a2T=dAdt_1+dAdt_2;
    a2x0=1-3*pow((T0/Tl),2)+2*pow((T0/Tl),3);
    a2dx0=T0-2*T0*T0/Tl+T0*T0*T0/(Tl*Tl);
    a2x1=3*pow((T0/Tl),2)-2*pow((T0/Tl),3);
    a2dx1=-T0*T0/Tl+T0*T0*T0/(Tl*Tl);

}

void PolyParams::FillinJacobian(Eigen::SparseMatrix<double, Eigen::RowMajor> &jacmat_2_go, Jac_Group &First_derive)
{
    int dec=0;

    Eigen::MatrixXd midmat;
    for(int i=0;i<First_derive.total_Jac_num;i++)
    {
        dec=First_derive.jac_sets[i].relative_2_dec;
        Get_Single_Jacobian_form_2(dec*steptime, local_mat_2_params);
        midmat=First_derive.jac_sets[i].jacobian*local_mat_2_params;
        Copy_Dense_2_Jac(jacmat_2_go,midmat,dec);
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
