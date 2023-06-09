#include "path_point_constrain.h"
#include "var_packer.h"
Path_Point_Constrain::Path_Point_Constrain(int cons_num): ConstraintSet(cons_num, "Acc_constrain")
{
    xmlCore files("./config/constrainParams.xml");
    files.xmlRead("constant",consta);
}

ifopt::Component::VectorXd Path_Point_Constrain::GetValues() const
{
    VectorXd g(GetRows());
    Eigen::VectorXd x = GetVariables()->GetComponent("spline_p_set")->GetValues();
    Eigen::VectorXd x_acc = GetVariables()->GetComponent("action_state_set1")->GetValues();
    packvariable_pos_set(x_acc,posset);
    for(int i=0;i<decnum;i++)
    {
        double ax=0;
        double ay=0;
        double target_x=0;
        double target_y=0;
        target_x=x(6*i+2);
        target_y=x(6*i+3);
        for(int j=0;j<agentnum;j++)
        {
            ax+=(target_x-posset(2*j+0,i));
            ay+=(target_y-posset(2*j+1,i));
        }
        g(2*i+0)=x(6*i+0)-consta*ax;
        g(2*i+1)=x(6*i+1)-consta*ay;
    }
    return g;
    //加速度约束
}

void Path_Point_Constrain::init_num(int state_num, int agent_num, int dec_num) const
{
    statenum=state_num;
    agentnum=agent_num;
    decnum=dec_num;
    posset.resize(2*agentnum,statenum);//x y位置
    posset.setZero();
}

ifopt::Component::VecBound Path_Point_Constrain::GetBounds() const
{
    VecBound b(GetRows());
    for(int i=1;i<=2*decnum;i++)
    {
        b.at(i-1)=ifopt::Bounds(0.0, 0.0);
    }

    return b;
}

void Path_Point_Constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    if (var_set == "action_state_set1")
    {
        for(int i=0;i<decnum;i++)
        {
            jac_block.coeffRef(2*i+0, 6*i+0) = 1.0;
            jac_block.coeffRef(2*i+1, 6*i+1) = 1.0;

            jac_block.coeffRef(2*i+0, 6*i+2) = -consta*agentnum;
            jac_block.coeffRef(2*i+1, 6*i+3) = -consta*agentnum;

        }
    }
    if (var_set == "spline_p_set")
    {
        for(int i=0;i<decnum;i++)
        {
            for(int j=0;j<agentnum;j++)
            {
                jac_block.coeffRef(2*i+0, 2*agentnum*i+2*j+0) = consta;
                jac_block.coeffRef(2*i+0, 2*agentnum*i+2*j+1) = consta;
            }
        }
    }
}

