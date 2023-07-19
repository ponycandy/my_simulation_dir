#include "costfunc.h"
#include "iostream"



costfunc::costfunc():ifopt::CostTerm("cost")
{

    m_variable.resize(5,1);//假设变量为x1~x5
    eigendata.resize(5,5);
    Jac.resize(1,5);
    //    eigendata<<2 , 1 , 0 , 0.7 , 9,
    //        1 , 1 , 3 , 0.8 ,0,
    //        0 , 3 , 3 , 0.8 ,0,
    //        0.7,0.8,0.8, 0   ,0,
    //        9 ,0 ,0 , 0   , 0;
    eigendata.setIdentity();
}

double costfunc::GetCost() const
{
    QString var_name;
    var_name="x_value_all";
    Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
    for(int i=0;i<x.rows();i++)
    {
        m_variable[i][0]=autograd::variable(x(i));
    }

    outcome=m_variable.Transpose() * eigendata * m_variable;
//    auto my_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt", true);


//    my_logger->info(QString::number(outcome[0][0]->value_).toStdString());
//    my_logger->flush();
    //因为程序没有退出，所以务必在这里手动刷新，否则文本是没有写入的！
    //logger不能够放在ipopt的优化程序内

    return outcome[0][0]->value_;
}

void costfunc::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{

    if (var_set == "x_value_all")
    {
        double value=GetCost();
        autograd::GetJacobian(outcome,m_variable,Jac);
        ATtensor gradienttechnique= 2 * m_variable.Transpose() * eigendata;


        //        printTensor(gradienttechnique);
        //log不起作用....
        jac=Jac.sparseView();
        //        std::cout<<Jac<<std::endl;
    }
}
