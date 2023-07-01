#include "minimize_speed_cost.h"
#include "xmlcore.h"
#include "var_packer.h"
Minimize_Speed_Cost::Minimize_Speed_Cost(): CostTerm("Minimize_speed")
{
   //最小化末端速度，这是唯一合理的解答
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",decnum);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("statenum",statenum);
    xml_reader.xmlRead("actnum",actnum);
    init_num(statenum,agentnum,decnum,pointnum,steptime);
    actMat.resize(actnum,decnum);
    actMat.setZero();
    states.resize(statenum,decnum);
    states.setZero();
    D2statemat.resize(1,2);
    epson=0.0001;
}

double Minimize_Speed_Cost::GetCost() const
{
    Eigen::VectorXd x;
    x.resize(statenum*decnum);
    x=GetVariables()->GetComponent("state_value")->GetValues();
    packvariable_states_set(x,states,decnum);
    double speed=0;
    speed=pow(states(2,decnum-1),2)+pow(states(3,decnum-1),2);
    return speed;
}

void Minimize_Speed_Cost::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    if (var_set == "state_value")
    {
        Eigen::VectorXd x;
        x.resize(statenum*decnum);
        x=GetVariables()->GetComponent("state_value")->GetValues();
        packvariable_states_set(x,states,decnum);
        jac.coeffRef(0,statenum*(decnum-1)+2)=2*states(2,decnum-1);
        jac.coeffRef(0,statenum*(decnum-1)+3)=2*states(3,decnum-1);

    }
}

void Minimize_Speed_Cost::init_num(int state_num, int agent_num, int dec_num, int pointnum, double step) const
{

}
