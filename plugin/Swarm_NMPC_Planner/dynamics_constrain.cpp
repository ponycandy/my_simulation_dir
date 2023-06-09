#include "dynamics_constrain.h"
#include "var_packer.h"
#include "QString"
#define top_side_x(dec) (4*dec+0)
#define top_side_y(dec) (4*dec+1)
#define top_side_vx(dec) (4*dec+2)
#define top_side_vy(dec) (4*dec+3)
#define left_side_x(dec) (4*dec+0)
#define left_side_y(dec) (4*dec+1)
#define left_side_vx(dec) (4*dec+2)
#define left_side_vy(dec) (4*dec+3)

#define index_x1(dec) (5*dec+0)
#define index_dx1(dec) (5*dec+1)
#define index_y1(dec) (5*dec+2)
#define index_dy1(dec) (5*dec+3)
#define index_T(dec) (5*dec+4)

Dynamics_Constrain::Dynamics_Constrain(int num):ConstraintSet(num,"Dynamics_Constrain")
{

}

ifopt::Component::VectorXd Dynamics_Constrain::GetValues() const
{
    QString var_name;
    VectorXd g(GetRows());
    PolyParams posset;
    for(int i=0;i<agentnum;i++)
    {
        posset=m_polys(i);
        var_name="spline_p_set_of_"+QString::number(i);
        packvariable_pos_set(
            GetVariables()->GetComponent(var_name)->GetValues(),
            posset ,pointnum);
        m_polys.value(i)=posset;
    }
    packvariable_states_set(
        GetVariables()->GetComponent("state_vars")->GetValues(),
        states,decnum );
    formactmat();
    FillinG(g);
    return g;
}

void Dynamics_Constrain::init_num(int state_num, int agent_num, int dec_num, int pointnum,double step) const
{
    agentnum=agent_num;
    steptime=step;
    for(int j=0;j<agent_num;j++)
    {
        PolyParams single_poly;
        single_poly.initilization(2,dec_num,pointnum,steptime);
        m_polys.insert(j,single_poly);
    }
}


ifopt::Component::VecBound Dynamics_Constrain::GetBounds() const
{
    VecBound b(GetRows());
    for(int i=1;i<=constrainnum;i++)
    {
        b.at(i-1)=ifopt::Bounds(0.0, 0.0);
    }

    return b;
}

void Dynamics_Constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    //下面的矩阵实际上无需反复求算，可以在初始化的时候搞定然后
    //赋值给jac_block
    if (var_set == "state_vars")
    {
        packvariable_states_set(
            GetVariables()->GetComponent("state_vars")->GetValues(),
            states,decnum );
        for(int i=0;i<decnum;i++)
        {

            //这里用非通用算法
            if(i==0)
            {
                jac_block.coeffRef(left_side_x(i), top_side_x(i)) = 1.0;
                jac_block.coeffRef(left_side_y(i), top_side_y(i)) = 1.0;
                jac_block.coeffRef(left_side_vx(i), top_side_vx(i)) = 1.0;
                jac_block.coeffRef(left_side_vy(i), top_side_vy(i)) = 1.0;

            }
            else
            {
                jac_block.coeffRef(left_side_x(i), top_side_x(i)) = 1.0;
                jac_block.coeffRef(left_side_y(i), top_side_y(i)) = 1.0;
                jac_block.coeffRef(left_side_vx(i), top_side_vx(i)) = 1.0;
                jac_block.coeffRef(left_side_vy(i), top_side_vy(i)) = 1.0;

                jac_block.coeffRef(left_side_x(i), top_side_x(i-1)) = -1.0;
                jac_block.coeffRef(left_side_x(i), top_side_vx(i-1)) =-steptime;
                jac_block.coeffRef(left_side_y(i), top_side_y(i-1)) = -1;
                jac_block.coeffRef(left_side_y(i), top_side_vy(i-1)) =-steptime;

                jac_block.coeffRef(left_side_vx(i), top_side_x(i-1)) =-agentnum*consta*steptime;
                jac_block.coeffRef(left_side_vx(i), top_side_vx(i-1)) =-1;
                jac_block.coeffRef(left_side_vy(i), top_side_y(i-1)) = -agentnum*consta*steptime;
                jac_block.coeffRef(left_side_vy(i), top_side_vy(i-1)) =-1-steptime*consta*agentnum;

            }
        }
    }
    for(int j=0;j<agentnum;j++)
    {
        QString var_name;
        var_name="spline_p_set_of_"+QString::number(j);
        Eigen::MatrixXd dfdstate;
        dfdstate<<0,0,
            0,0,
            1,0,
            0,1;
        Eigen::MatrixXd jacob;
        if (var_set == var_name)
        {
            PolyParams set=m_polys.value(j);
            double currenttime=0;
            Eigen::MatrixXd jac_mat_block;
            for(int i=0;i<decnum;i++)
            {
                if(i==0)
                {
                    set.Get_Single_Jacobian_form_2(currenttime,jac_mat_block);
                    jacob=steptime*consta*jac_mat_block;
                    Copy_Dense_2_Sparse(jac_block,jacob.block(0,5,4,5),0,0);
                    currenttime+=steptime;

                }
                else
                {
                    set.Get_Single_Jacobian_form_2(currenttime,jac_mat_block);
                    jacob=steptime*consta*jac_mat_block;
                    Copy_Dense_2_Sparse(jac_block,jacob,4*i,5*(i-1));
                    currenttime+=steptime;
                }
            }
            break;
        }

    }
}

void Dynamics_Constrain::FillinG(Eigen::VectorXd &g)
{
    for(int i=0;i<decnum;i++)
    {
        if(i==0)
        {
            Combined_cons.block(0,0,statenum,1)=states.block(0,0,statenum,1)-
                                                     initstates_of_animals-steptime*
                                                                                 self_ode->ode_function(actMat.block(0,0,actnum,1),initstates_of_animals);
        }
        else
        {
            Combined_cons.block(statenum*i,0,statenum,1)=states.block(0,i,statenum,1)-
                                                                states.block(0,i-1,statenum,1)-steptime*
                                                                                                          self_ode->ode_function(actMat.block(0,i,actnum,1),states.block(0,i-1,statenum,1));

        }
    }
    for(int i=0;i<constrainnum;i++)
    {
        g(i)=Combined_cons(i);
    }
}

void Dynamics_Constrain::Copy_Dense_2_Sparse(Jacobian &jac_block, Eigen::MatrixXd mat, int startrow, int startcol)
{
    int rows=mat.rows();
    int cols=mat.cols();
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if( mat(i,j)!=0)
            {
                jac_block.coeffRef(rows+startrow,cols+startcol) = mat(i,j);
            }
        }
    }
}

void Dynamics_Constrain::formactmat()
{


    for(int i=0;i<agentnum;i++)
    {
        Eigen::MatrixXd single_mat;
        m_polys.value(i).Get_Poly_Value_Mat(single_mat);//2*dec_num尺寸的矩阵
        ActMats.value(i)=single_mat;

    }
    actMat.setZero();
    Eigen::MatrixXd single_mat;

    for(int j=0;j<agentnum;j++)
    {
        single_mat=ActMats.value(j);
        for(int i=0;i<decnum;i++)
        {
            actMat.block(0,i,2,1)+=consta*(states.block(0,i,2,1)-single_mat.block(0,i,2,1));
        }
    }



    actMat=consta*actMat;
}
