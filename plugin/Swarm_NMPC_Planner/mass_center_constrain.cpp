
3


#include "mass_center_constrain.h"
#include "QString"
#include "var_packer.h"
mass_center_constrain::mass_center_constrain(int num):ConstraintSet(num,"mass_center_constrain")
{
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",decnum);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("statenum",statenum);
    xml_reader.xmlRead("actnum",actnum);
    init_num(statenum,agentnum,decnum,pointnum,0);
    Eigen::MatrixXd actmats_i;
    actmats_i.resize(2,decnum);
    for(int i=0;i<agentnum;i++)
    {
        ActMats.insert(i,actmats_i);
    }
    states.resize(statenum,decnum);
    states.setZero();
    minimalD=3;

}

ifopt::Component::VectorXd mass_center_constrain::GetValues() const
{
    //计算末端坐标质心
    QString var_name;
    VectorXd g(GetRows());
    for(int i=0;i<agentnum;i++)
    {
        var_name="spline_p_set_of_"+QString::number(i);
        Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
        m_polys[i].packvariable(x);
    }
    Eigen::VectorXd x;
    x.resize(statenum*decnum);
    x=GetVariables()->GetComponent("state_value")->GetValues();
    packvariable_states_set(x,states,decnum);


    formactmat();

    FillinG(g);
    return g;
}

void mass_center_constrain::init_num(int state_num, int agent_num, int dec_num, int pointnum, double step) const
{
    agentnum=agent_num;
    for(int j=0;j<agent_num;j++)
    {
        PolyParams single_poly;
        single_poly.configfiename="./config/Polys/constrainParams"+QString::number(j)+".xml";
        single_poly.initilization();
        m_polys.insert(j,single_poly);
    }
}

ifopt::Component::VecBound mass_center_constrain::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=2;i++)
    {
        b.at(i-1)=ifopt::Bounds(0.0, 0.0);
    }

    return b;
}

void mass_center_constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    if (var_set == "state_value")
    {
        jac_block.coeffRef(0,statenum*(decnum-1))=-1;
        jac_block.coeffRef(1,statenum*(decnum-1)+1)=-1;
        QString var_name;
        for(int i=0;i<agentnum;i++)
        {
            var_name="spline_p_set_of_"+QString::number(i);
            Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
            m_polys[i].packvariable(x);
        }

    }
    for(int j=0;j<agentnum;j++)
    {
        QString var_name;
        var_name="spline_p_set_of_"+QString::number(j);
        if (var_set == var_name.toStdString())
        {
            Jac_Group group;
            single_jacob jac0;
            group.init(1);
            Eigen::MatrixXd dgda;
            dgda.resize(2,2);
            dgda<<1,0,0,1;
            jac0.relative_2_dec=decnum-1;
            jac0.jacobian=dgda/agentnum;
            group.jac_sets[0]=jac0;
            m_polys[j].FillinJacobian(jac_block,group);
            // 我想我们需要三级，乃至多级的雅可比矩阵计算！雅可比的级数
            //也需要可变

            m_polys[j].clearconstrainindex();
            break;
        }
    }
}

void mass_center_constrain::FillinG(Eigen::VectorXd &g) const
{
    double x_average=0;
    double y_average=0;
    double x_current_agent=0;
    double y_current_agent=0;
    double distance=0;
    for(int i=0;i<agentnum;i++)
    {
        x_current_agent=ActMats[i](0,decnum-1);
        y_current_agent=ActMats[i](1,decnum-1);

        x_average+=x_current_agent;
        y_average+=y_current_agent;
        distance=pow(states(0,decnum-1)-x_current_agent,2)+
                   pow(states(1,decnum-1)-y_current_agent,2);
        g(2+i)=distance-minimalD*minimalD;


    }
    x_average/=agentnum;
    y_average/=agentnum;
    g(0)=x_average-states(0,decnum-1);
    g(1)=y_average-states(1,decnum-1);
    //下面需要添加约束：1.每段的最大速度小于一个值，2.最终的所有点都在一个圆圈里面
}


void mass_center_constrain::formactmat() const
{
    for(int i=0;i<agentnum;i++)
    {
        m_polys.value(i).Get_Poly_Value_Mat(ActMats[i]);
    }
}
