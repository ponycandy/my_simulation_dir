#include "problem_wrapup.h"
#include <xmlcore.h>
problem_wrapup::problem_wrapup()
{
    QString configfiename="./config/Polys/ProblemParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",decnum);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
}

void problem_wrapup::construct()
{
    //构建三次曲线变量
    int var_num=pointnum*(2*dims+1);
    for(int i=0;i<agentnum;i++)
    {
        QString var_name="spline_p_set_of_"+QString::number(i);
        std::string varnamespline=var_name.toStdString();
        SplineVariable *spline_1;
        spline_1=new SplineVariable(var_num,varnamespline);
        m_spline_sets.insert(i,spline_1);
    }
    //构建动力学约束
    m_constrain=new Dynamics_Constrain(statenum*decnum);


    //构建状态变量
}
