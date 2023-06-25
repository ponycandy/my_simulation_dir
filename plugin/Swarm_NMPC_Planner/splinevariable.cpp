#include "splinevariable.h"
#include <QString>
#include <xmlcore.h>

SplineVariable::SplineVariable(int num, std::string &varname):VariableSet(num,varname)
{
    var_num=num;
    variable.resize(var_num,1);
    variable.setRandom();
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);


    //将lastingtime设为非0平均化
    for(int i=0;i<pointnum;i++)
    {
        variable((2*dims+1)*(i+1)-1)=dec_num*steptime/pointnum;
    }
    //将剩余参数设为0，这样可能会好一些？
//    variable.setZero();
}

void SplineVariable::SetVariables(const VectorXd &x)
{
    variable=x;
}


ifopt::Component::VectorXd SplineVariable::GetValues() const
{

    Eigen::VectorXd x=variable;
    return x;
}

ifopt::Component::VecBound SplineVariable::GetBounds() const
{
    //no bound,bound is constrained by constrains
    ifopt::Component::VecBound bounds(GetRows());
    for(int i=0;i<var_num;i++)
    {
        bounds.at(i)=ifopt::NoBound;
    }
    return bounds;
}
