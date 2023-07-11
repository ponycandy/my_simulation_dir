#include "solver_manager.h"
#include "Swarm_NMPC_PlannerActivator.h"
#include "dynamics_of_animals.h"
#include "jac_of_animals.h"
#include "path_point_constrain.h"
#include "problem_wrapup.h"
#include "splinevariable.h"
#include "controlconstrain.h"
#include "QString"
#include "xmlcore.h"
#include "state_variable.h"
#include "dynamics_constrain.h"
#include "trackingcost.h"
#include "event/eventype.h"
#include "service/Animateservice.h"
#include "minimize_speed_cost.h"
#include "mass_center_constrain.h"
#include "terminalwithinrange.h"
solver_manager::solver_manager()
{
    qRegisterMetaType<QVector<PolyParams>>("QVector<PolyParams>");
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",pointnum);

    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("statenum",statenum);
    m_widget=new startdreaw;

    Swarm_NMPC_PlannerActivator::publishsignal(m_widget,SIGNAL(sig_start(QVector<PolyParams>,double,double)),UCSEVENT::Display_POlys,Qt::QueuedConnection);
    m_service=Swarm_NMPC_PlannerActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_service->Use_BuildIn_Dynamics_Cons(false);
    m_service->setuseterminal(false);



    //添加状态变量
    State_Variable *stateVar;
    std::string statevarname="state_value";
    stateVar=new State_Variable(statenum*dec_num,statevarname);
    std::shared_ptr<ifopt::VariableSet> statevarptr(stateVar);
    m_service->AddVariableSet(statevarptr);

    //以下完成三组变量,以及对应的曲线约束,请注意变量的先后插入顺序，将会对雅可比矩阵的计算造成影响

    for(int i=0;i<agentnum;i++)
    {
        SplineVariable *spline_i;
        QString varnameQ="spline_p_set_of_"+QString::number(i);
        std::string varname=varnameQ.toStdString();
        spline_i=new SplineVariable(pointnum*(2*dims+1),varname);
        std::shared_ptr<ifopt::VariableSet> varptr(spline_i);
        m_service->AddVariableSet(varptr);

        QString ControlconsnameQ="ControlCons_of_"+QString::number(i);
        std::string Controlconsname=ControlconsnameQ.toStdString();
        ControlConstrain *control_0=new ControlConstrain(dec_num+2*pointnum,Controlconsname);
        control_0->current_agent_num=i;
        control_0->m_poly->configfiename="./config/Polys/constrainParams"+QString::number(i)+".xml";
        control_0->m_poly->initilization();
        std::shared_ptr<ifopt::ConstraintSet> consptr(control_0);
        m_service->AddConstraintSet(consptr);
    }

    //添加动力学约束
    Dynamics_Constrain *Dcons;
    Dcons=new Dynamics_Constrain(statenum*dec_num);
    std::shared_ptr<ifopt::ConstraintSet> Dconsptr(Dcons);
    m_service->AddConstraintSet(Dconsptr);
    //添加目标函数
    //    TrackingCost *tcost;
    //    tcost=new TrackingCost;
    //    std::shared_ptr<ifopt::ConstraintSet> Dtcostptr(tcost);
    //    m_service->AddCostSet(Dtcostptr);
    //质量中心约束
//    mass_center_constrain *masscons;
//    masscons=new mass_center_constrain(2);
//    std::shared_ptr<ifopt::ConstraintSet> Dconmassconssptr(masscons);
//    m_service->AddConstraintSet(Dconmassconssptr);
    //质量中心散布约束
//    TerminalWithinRange *TerminalWithinRangecons;
//    TerminalWithinRangecons=new TerminalWithinRange(agentnum);
//    std::shared_ptr<ifopt::ConstraintSet> TerminalWithinRangeconsptr(TerminalWithinRangecons);
//    m_service->AddConstraintSet(TerminalWithinRangeconsptr);
    //目标速度损失函数
//    Minimize_Speed_Cost *tcost;
//    tcost=new Minimize_Speed_Cost;
//    std::shared_ptr<ifopt::ConstraintSet> Dtcostptr(tcost);
//    m_service->AddCostSet(Dtcostptr);
//最终约束：masscenter分布在中央一定范围内部，不要使用cost!

    m_service->start_crack();
    //    std::cout<<"optimal value is "<<tcost->GetValues()<<std::endl;
    Dcons->GetValues();
    QVector<PolyParams> polysj;
    m_widget->fx=Dcons->states(0,dec_num-1);
    m_widget->fy=Dcons->states(1,dec_num-1);

    m_widget->m_polys=Dcons->m_polys;
    m_widget->move(20,20);
    m_widget->show();

}
