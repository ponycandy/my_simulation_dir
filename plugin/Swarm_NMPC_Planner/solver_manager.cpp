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
solver_manager::solver_manager()
{

    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);

    m_service=Swarm_NMPC_PlannerActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_service->Use_BuildIn_Dynamics_Cons(false);
    m_service->setuseterminal(false);

//    problem_wrapup *m_problem=new problem_wrapup;
    //第一次测试，尝试单纯引入曲线自身约束的单曲线
    SplineVariable *spline_0;
    std::string varname="spline_p_set_of_0";
    spline_0=new SplineVariable(pointnum*(2*dims+1),varname);
    std::shared_ptr<ifopt::VariableSet> varptr(spline_0);
    m_service->AddVariableSet(varptr);
    std::string Controlconsname="ControlCons";
    ControlConstrain *control_0=new ControlConstrain(1+3,Controlconsname);
    control_0->current_agent_num=0;
    std::shared_ptr<ifopt::ConstraintSet> consptr(control_0);
    m_service->AddConstraintSet(consptr);
    m_service->start_crack();
    Eigen::VectorXd x=m_service->solve_problem("spline_p_set_of_0");
    control_0->m_poly->packvariable(x);
    Eigen::MatrixXd mat;
    mat.resize(2,10);
    control_0->m_poly->Get_Poly_Value_Mat(mat);
    //不对，约束已经被满足了，但是不是以mat的形式，而是以
    //关键点的形式
    std::cout<<mat<<std::endl;
    //下一步，动力学模式！

}
