#include "close_point_constrain.h"
#include "QString"
#include "var_packer.h"
#include "xmlcore.h"
#define set_x_0_x0(pointnum) (5*pointnum)
#define set_x_1_x0(pointnum) (5*pointnum)
#define set_y_0_x0(pointnum) (5*pointnum)
#define set_y_1_x0(pointnum) (5*pointnum)

close_point_constrain::close_point_constrain(int thisagentorder,int consNum,std::string name):ConstraintSet(consNum,name)
{
    self_agent_order=thisagentorder;
}

ifopt::Component::VectorXd close_point_constrain::GetValues() const
{
    QString var_name;
    VectorXd g(GetRows());
    PolyParams posset;
    int i=self_agent_order;
    posset=m_polys(i);
    var_name="spline_p_set_of_"+QString::number(i);
    packvariable_pos_set(
        GetVariables()->GetComponent(var_name)->GetValues(),
        posset ,pointnum);
    m_polys.value(i)=posset;
    formactmat();
    FillinG(g);
    return g;
}

void close_point_constrain::FillinG(Eigen::VectorXd &g)
{
    PolyParams mid=m_polys(0);
    pos_and_derivative set_x_0;pos_and_derivative set_x_1;
    pos_and_derivative set_y_0;pos_and_derivative set_y_1;
    for(int i=0;i<pointnum-1;i++)
    {
        mid.Get_pos_and_derivative_set(i,set_x_0,0);
        mid.Get_pos_and_derivative_set(i+1,set_x_1,0);
        mid.Get_pos_and_derivative_set(i,set_y_0,1);
        mid.Get_pos_and_derivative_set(i+1,set_y_1,1);
        g(i)=pow(set_x_0.x0-set_x_1.x0,2)+pow(set_y_0.x0-set_y_1.x0,2)-radius*radius;
    }

}

void close_point_constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    QString var_name="spline_p_set_of_"+QString::number(self_agent_order);
    if (var_set == var_name)
    {
        packvariable_pos_set(
            GetVariables()->GetComponent(var_name)->GetValues(),
            posset ,pointnum);
        PolyParams mid=m_polys(0);
        pos_and_derivative set_x_0;pos_and_derivative set_x_1;
        pos_and_derivative set_y_0;pos_and_derivative set_y_1;
        for(int i=0;i<pointnum-1;i++)
        {
            mid.Get_pos_and_derivative_set(i,set_x_0,0);
            mid.Get_pos_and_derivative_set(i+1,set_x_1,0);
            mid.Get_pos_and_derivative_set(i,set_y_0,1);
            mid.Get_pos_and_derivative_set(i+1,set_y_1,1);

            jac_block(i,set_x_0_x0(i))=2*(set_x_0.x0-set_x_1.x0);
            jac_block(i,set_x_1_x0(i))=2*(set_x_1.x0-set_x_0.x0);
            jac_block(i,set_y_0_x0(i))=2*(set_y_0.x0-set_y_1.x0);
            jac_block(i,set_y_1_x0(i))=2*(set_y_1.x0-set_y_0.x0);

        }
        //当时我的三次曲线基本上用的是直接差分法求解得到导数
        //目前这个算法的复杂度真的爆炸s


    }
}
void close_point_constrain::formactmat()
{
    int i=self_agent_order;
    m_polys.value(i).Get_Poly_Value_Mat(actMat);//2*dec_num尺寸的矩阵
}
