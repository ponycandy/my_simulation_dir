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
solver_manager::solver_manager()
{

    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("statenum",statenum);


    m_service=Swarm_NMPC_PlannerActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_service->Use_BuildIn_Dynamics_Cons(false);
    m_service->setuseterminal(false);

    //以下完成三组变量,以及对应的曲线约束

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
        ControlConstrain *control_0=new ControlConstrain(1+pointnum,Controlconsname);
        control_0->current_agent_num=i;
        std::shared_ptr<ifopt::ConstraintSet> consptr(control_0);
        m_service->AddConstraintSet(consptr);
    }

    //添加状态变量
    State_Variable *stateVar;
    std::string statevarname="state_value";
    stateVar=new State_Variable(statenum*dec_num,statevarname);
    std::shared_ptr<ifopt::VariableSet> statevarptr(stateVar);
    m_service->AddVariableSet(statevarptr);
    //添加动力学约束
    Dynamics_Constrain *Dcons;
    Dcons=new Dynamics_Constrain(statenum*dec_num);
    std::shared_ptr<ifopt::ConstraintSet> Dconsptr(Dcons);
    m_service->AddConstraintSet(Dconsptr);


    m_service->start_crack();
    Eigen::VectorXd x=m_service->solve_problem("spline_p_set_of_0");
}
