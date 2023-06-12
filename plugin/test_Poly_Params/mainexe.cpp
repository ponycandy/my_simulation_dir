#include "mainexe.h"
#include "PolyParams.h"
#include "xmlcore.h"
mainexe::mainexe()
{
    PolyParams *m_polys=new PolyParams;
    m_polys->initilization();

    Eigen::VectorXd x(15);
    x<<0,1,0,1,1.667,
        0,1,0,1,1.667,
        0,1,0,1,1.667;
    m_polys->packvariable(x);
    double value;
    m_polys->Get_Single_Value(0.833,value,0);
    qDebug()<<value;
    double a2x0;double a2x1; double a2dx0;
    double a2dx1;double a2T;
    m_polys->Get_Single_derivative(0,0,a2x0,a2x1,a2dx0,a2dx1,a2T);
    qDebug()<<a2x0<<a2x1<<a2dx0<<a2dx1<<a2T;
    m_polys->Get_Single_derivative(1.5,0,a2x0,a2x1,a2dx0,a2dx1,a2T);
    qDebug()<<a2x0<<a2x1<<a2dx0<<a2dx1<<a2T;
    //current time不能够为任意值，只能是给定的currenttime的double值
    Eigen::MatrixXd valuemat;
    valuemat.resize(2,10);
    m_polys->Get_Poly_Value_Mat(valuemat);
    std::cout<<valuemat<<std::endl;
    std::cout<<"-----------------"<<std::endl;
    Eigen::MatrixXd singlejac;
    singlejac.resize(2,9);
    m_polys->Get_Single_Jacobian_form_2(0,singlejac);
    std::cout<<singlejac<<std::endl;
    std::cout<<"-----------------"<<std::endl;
    Eigen::SparseMatrix<double, Eigen::RowMajor> jacmat_2_go;
    jacmat_2_go.resize(2,15);

    Jac_Group group;
    group.total_Jac_num=2;
    single_jacob a_jac;
    a_jac.relative_2_dec=0;
    a_jac.jacobian.resize(2,2);
    a_jac.jacobian<<-1,0,
        0,-1;
    group.jac_sets.insert(0,a_jac);


    single_jacob a_jac_1;
    a_jac_1.relative_2_dec=1;
    a_jac_1.jacobian.resize(2,2);
    a_jac_1.jacobian<<1,0,
        0,1;
    group.jac_sets.insert(1,a_jac_1);


    m_polys->FillinJacobian(jacmat_2_go,group);
    std::cout<<jacmat_2_go<<std::endl;
    std::cout<<"-----------------"<<std::endl;
    jacmat_2_go.setZero();
    Jac_Group group_1;
    group_1.total_Jac_num=2;
    a_jac.relative_2_dec=3;
    a_jac.jacobian.resize(2,2);
    a_jac.jacobian<<-1,0,
        0,-1;
    group_1.jac_sets.insert(0,a_jac);


    a_jac_1.relative_2_dec=4;
    a_jac_1.jacobian.resize(2,2);
    a_jac_1.jacobian<<1,0,
        0,1;
    group_1.jac_sets.insert(1,a_jac_1);

    m_polys->clearconstrainindex();
    m_polys->FillinJacobian(jacmat_2_go,group_1);
    m_polys->FillinJacobian_complete(jacmat_2_go);
    std::cout<<jacmat_2_go<<std::endl;

}
