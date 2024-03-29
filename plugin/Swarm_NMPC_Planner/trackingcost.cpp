﻿#include "trackingcost.h"
#include "var_packer.h"
#include "Matrix_sparser.h"
TrackingCost::TrackingCost(): CostTerm("Minimize_distance")
{
    //目标值设置为距离值-1的平方，这样就可以避免压倒目标点上面造成奇点了
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
    coef_S=0.5;
}

double TrackingCost::GetCost() const
{
    QString var_name;
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
    distance=0;
    double mid=0;
    Eigen::MatrixXd sinmat;

    D2statemat.setZero();
    sinmat.resize(dims,decnum);
    single_jacob jacobmat;

    for(int i=0;i<agentnum;i++)
    {
        Eigen::MatrixXd jacmat;
        Jac_Group gpj;
        gpj.init(1);
        jacmat.resize(1,2);
        m_polys[i].Get_Poly_Value_Mat(sinmat);
        mid=pow(sinmat(0,decnum-1)-states(0,decnum-1),2)+pow(sinmat(1,decnum-1)-states(1,decnum-1),2);
        distance+=epson*pow(mid-1,2);
        jacobmat.relative_2_dec=decnum-1;//这个距离需要scale一下，不然会造成梯度过大的问题
        jacmat<<epson*4*(mid-1)*(sinmat(0,decnum-1)-states(0,decnum-1)),epson*4*(mid-1)*(sinmat(1,decnum-1)-states(1,decnum-1));
        jacobmat.jacobian=jacmat;
        gpj.jac_sets[0]=jacobmat;
        Jac_Group_vactor[i]=gpj;
        D2statemat-=jacmat;
    }
    double speed=0;
    speed=pow(states(2,decnum-1),2)+pow(states(3,decnum-1),2);

    return distance+coef_S*speed;

}

void TrackingCost::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    if (var_set == "state_value")
    {
        Matrix_sparser m_sparser;
        double value=GetCost();
        m_sparser.Copy_Mat_2_Sparse_block(jac,D2statemat,0,statenum*(decnum-1),1,2);
        jac.coeffRef(0,statenum*(decnum-1)+2)+=coef_S*2*states(2,decnum-1);
        jac.coeffRef(0,statenum*(decnum-1)+3)+=coef_S*2*states(3,decnum-1);

    }
    for(int j=0;j<agentnum;j++)
    {
        QString var_name;
        var_name="spline_p_set_of_"+QString::number(j);
        if (var_set == var_name.toStdString())
        {
//            double value=GetCost();
            m_polys[j].FillinJacobian(jac,Jac_Group_vactor[j]);
            m_polys[j].clearconstrainindex();
            break;
        }
    }

}

void TrackingCost::init_num(int state_num, int agent_num, int dec_num, int pointnum, double step) const
{
    agentnum=agent_num;
    steptime=step;
    for(int j=0;j<agent_num;j++)
    {
        PolyParams single_poly;
        single_poly.configfiename="./config/Polys/constrainParams"+QString::number(j)+".xml";
        single_poly.initilization();
        m_polys.insert(j,single_poly);

        Jac_Group jrp;
        jrp.init(1);
        Jac_Group_vactor.insert(j,jrp);
    }

}
