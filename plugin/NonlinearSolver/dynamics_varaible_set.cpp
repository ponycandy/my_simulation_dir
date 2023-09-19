#include "dynamics_varaible_set.h"

Dynamics_varaible_Set::Dynamics_varaible_Set(int num):VariableSet(num, "action_state_set1")
{
}



void Dynamics_varaible_Set::SetVariables(const VectorXd &x)
{
    all_variable=x.eval();
}

void Dynamics_varaible_Set::init_parents()
{
    all_variable.resize(total_varaible_num,1);
    all_variable.setRandom();
}

void Dynamics_varaible_Set::set_cons_num(int statenum, int actnum, int decisionnum)
{
    state_num=statenum;
    act_num=actnum;
    dec_num=decisionnum;
    state_num_plus_act_num=actnum+statenum;
    constrain_num=dec_num*statenum;
    total_varaible_num=state_num_plus_act_num*dec_num;
    init_parents();
}

void Dynamics_varaible_Set::set_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{
    m_lower=lower;
    m_higher=higher;
    control_bound_flag=true;
}

int Dynamics_varaible_Set::get_action_ipopt_number_index(int time_step, int action_index) const
{
    return (state_num_plus_act_num*(time_step-1)+action_index);
}

ifopt::Component::VectorXd Dynamics_varaible_Set::GetValues() const
{
    return all_variable;
}

ifopt::Component::VecBound Dynamics_varaible_Set::GetBounds() const
{
    ifopt::Component::VecBound bounds(GetRows());
    for(int k=0;k<total_varaible_num;k++)
    {
        bounds.at(k)=ifopt::NoBound;
    }

    int coord=0;
    if(control_bound_flag==true)
    {

        for(int i=1;i<=dec_num;i++)
        {
            for(int j=0;j<act_num;j++)
            {
                //                bounds.at(get_action_ipopt_number_index(i,j))
                //                  =ifopt::Bounds(m_lower(j,0), m_higher(j,0));
                coord=get_action_ipopt_number_index(i,j);
                bounds.at(coord)=ifopt::Bounds(m_lower(j,0), m_higher(j,0));

            }

        }
    }
    return bounds;
}
