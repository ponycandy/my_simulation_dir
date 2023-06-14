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
#include "testpolyparams.h"
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

    TestPolyParams *polys=new TestPolyParams(2);
    std::shared_ptr<ifopt::ConstraintSet> consptr(polys);
    m_service->AddConstraintSet(consptr);

    std::string var_pp="heurioa";
    ControlConstrain *CCs=new ControlConstrain(3+1,var_pp);
    CCs->current_agent_num=0;
    std::shared_ptr<ifopt::ConstraintSet> consptr1(CCs);
    m_service->AddConstraintSet(consptr1);

    m_service->start_crack();

}
