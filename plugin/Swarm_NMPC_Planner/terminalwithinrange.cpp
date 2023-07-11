#include "terminalwithinrange.h"
#include "xmlcore.h"
#include "var_packer.h"
TerminalWithinRange::TerminalWithinRange(int num):ifopt::ConstraintSet(num,"TerminalWithinRange")
{
    consnum=num;
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

ifopt::Component::VectorXd TerminalWithinRange::GetValues() const
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

void TerminalWithinRange::init_num(int state_num, int agent_num, int dec_num, int pointnum, double step) const
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

ifopt::Component::VecBound TerminalWithinRange::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=consnum;i++)
    {
        b.at(i-1)=ifopt::BoundSmallerZero;
    }

    return b;
}

void TerminalWithinRange::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    if (var_set == "state_value")
    {
        QString vars_name;
        VectorXd g(GetRows());
        for(int i=0;i<agentnum;i++)
        {
            vars_name="spline_p_set_of_"+QString::number(i);
            Eigen::VectorXd x=GetVariables()->GetComponent(vars_name.toStdString())->GetValues();
            m_polys[i].packvariable(x);
        }
        Eigen::VectorXd x;
        x.resize(statenum*decnum);
        x=GetVariables()->GetComponent("state_value")->GetValues();
        packvariable_states_set(x,states,decnum);


        formactmat();

        QString var_name;
        for(int i=0;i<agentnum;i++)
        {
            double x_current_agent=ActMats[i](0,decnum-1);
            double y_current_agent=ActMats[i](1,decnum-1);
            jac_block.coeffRef(i,statenum*(decnum-1)+0)=2*states(0,decnum-1)-2*x_current_agent;
            jac_block.coeffRef(i,statenum*(decnum-1)+1)=2*states(1,decnum-1)-2*y_current_agent;

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
            dgda.resize(1,2);
            double x_current_agent=ActMats[j](0,decnum-1);
            double y_current_agent=ActMats[j](1,decnum-1);

            dgda<<-2*states(0,decnum-1)+2*x_current_agent,-2*states(1,decnum-1)+2*y_current_agent;
            jac0.relative_2_dec=decnum-1;
            jac0.jacobian=dgda;
            group.jac_sets[0]=jac0;
            m_polys[j].FillinJacobian(jac_block,group);
            m_polys[j].clearconstrainindex();
            break;
        }
    }
}

void TerminalWithinRange::FillinG(Eigen::VectorXd &g) const
{
    double x_current_agent=0;
    double y_current_agent=0;
    double distance=0;
    for(int i=0;i<agentnum;i++)
    {
        x_current_agent=ActMats[i](0,decnum-1);
        y_current_agent=ActMats[i](1,decnum-1);
        distance=pow(states(0,decnum-1)-x_current_agent,2)+
                   pow(states(1,decnum-1)-y_current_agent,2);
        g(i)=distance-minimalD*minimalD;
    }
    //下面需要添加约束：最终的所有点都在一个圆圈里面
}


void TerminalWithinRange::formactmat() const
{
    for(int i=0;i<agentnum;i++)
    {
        m_polys.value(i).Get_Poly_Value_Mat(ActMats[i]);
    }
}
