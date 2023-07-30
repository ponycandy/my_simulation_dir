#include "constraintest.h"



constraintest::constraintest(int num, std::string name):ifopt::ConstraintSet(num,name)
{

}

ifopt::Component::VectorXd constraintest::GetValues() const
{
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    std::string var_name="x_value_all";

    Eigen::VectorXd x=GetVariables()->GetComponent(var_name)->GetValues();

    g(0)=x(0)*x(1)-1;
    g(1)=x(1)*x(2)-1;
    return g;
}

ifopt::Component::VecBound constraintest::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=2;i++)
    {
        b.at(i-1)=ifopt::BoundGreaterZero;
    }

    return b;
}

void constraintest::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    std::string var_name="x_value_all";

    Eigen::VectorXd x=GetVariables()->GetComponent(var_name)->GetValues();


    jac_block.coeffRef(0,0)=x(1);
    jac_block.coeffRef(0,1)=x(0);
    jac_block.coeffRef(1,1)=x(2);
    jac_block.coeffRef(1,2)=x(1);
}

void constraintest::FillHessionBlock(std::string var_set, Jacobian &jac, int irow) const
{
    if(irow==0)
    {
        jac.coeffRef(1,0)=1;//只填左下角
//        jac.coeffRef(0,1)=1;//只填左下角
    }
    if(irow==1)
    {
        jac.coeffRef(2,1)=1;//只填左下角
//         jac.coeffRef(1,2)=1;//只填左下角
    }
}
