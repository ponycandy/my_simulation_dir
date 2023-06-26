#include "trackingcost.h"
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
    return distance;

}

void TrackingCost::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    if (var_set == "state_value")
    {
        Matrix_sparser m_sparser;
        double value=GetCost();
        m_sparser.Copy_Mat_2_Sparse_block(jac,D2statemat,0,statenum*(decnum-1),1,2);

    }
    for(int j=0;j<agentnum;j++)
    {
        QString var_name;
        var_name="spline_p_set_of_"+QString::number(j);
        if (var_set == var_name.toStdString())
        {
            double value=GetCost();
            m_polys[j].FillinJacobian(jac,Jac_Group_vactor[j]);


            int maxnum=15;
            Eigen::MatrixXd mat_num_jacob;
            mat_num_jacob.resize(1,maxnum);
            mat_num_jacob.setZero();
            double step=0.00001;
            Eigen::VectorXd x=GetVariables()->GetComponent(var_set)->GetValues();
            Eigen::MatrixXd sinmat;
            sinmat.resize(dims,decnum);
            for(int i=0;i<maxnum;i++)
            {
                Eigen::VectorXd y_var=x;
                y_var(i)+=step;
                m_polys[j].packvariable(y_var);
                distance=0;
                for(int k=0;k<agentnum;k++)
                {
                    Eigen::MatrixXd jacmat;
                    jacmat.resize(1,2);
                    m_polys[k].Get_Poly_Value_Mat(sinmat);
                    double mid=pow(sinmat(0,decnum-1)-states(0,decnum-1),2)+pow(sinmat(1,decnum-1)-states(1,decnum-1),2);
                    distance+=epson*pow(mid-1,2);
                }

                mat_num_jacob(0,i)=(distance-value)/step;
            }
            std::cout<<"-----------------numerical -   results   -  down --here   ----------------------"<<std::endl;
            std::cout<<mat_num_jacob<<std::endl;
            std::cout<<"-----------------numerical -   results   -  up  --here    ----------------------"<<std::endl;
            std::cout<<"-----------------Analytical -   results   -  down  --here    ----------------------"<<std::endl;
            std::cout<<jac<<std::endl;
            std::cout<<"-----------------Analytical -   results   -  up  --here    ----------------------"<<std::endl;
            std::cout<<"-----------------relative bias is below    ----------------------"<<std::endl;
            Eigen::MatrixXd matyup;
            matyup=jac-mat_num_jacob;
            std::cout<<matyup<<std::endl;
            std::cout<<" "<<std::endl;


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
        single_poly.initilization();
        m_polys.insert(j,single_poly);

        Jac_Group jrp;
        jrp.init(1);
        Jac_Group_vactor.insert(j,jrp);
    }

}
