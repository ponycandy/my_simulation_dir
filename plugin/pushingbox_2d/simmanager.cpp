﻿#include "simmanager.h"
#include "service/Animateservice.h"
#include "service/SimDynamicsservice.h"
#include "pushingbox_2dActivator.h"
#include "QWidget"
#include "OSGIEVENT.h"
simmanager::simmanager(QObject *parent) : QObject(parent)
{
    paint=new MYpainter;
    m_sim=new Simulator;


    m_sim->init();
    m_TCP=pushingbox_2dActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
    m_TCP->setport("8001","127.0.0.1");
    m_TCP->connectport();
    Animateservice *Anim_service=pushingbox_2dActivator::getService<Animateservice>("Animateservice");
    ODE_service=pushingbox_2dActivator::getService<SimDynamicsservice>("SimDynamicsservice");
    decoder=pushingbox_2dActivator::getService<CPYcoderservice>("CPYcoderservice");
    pushingbox_2dActivator::subscribeslot(this,SLOT(matrecieved(Eigen::MatrixXd))
                                            ,OSGIEVENT::MAT_GET_NOW,Qt::QueuedConnection);

    setupEvent();

    Anim_service->register_painter(paint);
    Anim_service->resizeWindow(1200,800);
    ODE_service->set_step_in_mode(1);
    ODE_service->set_ODE(m_sim);
    //这里开始主流程
    QWidget *awidget=Anim_service->getwidget();
    awidget->show();
    Anim_service->start_animate();
    ODE_service->start_sim();

}
void simmanager::setupEvent()
{
    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(m_sim,SIGNAL(sig_agent_state_update(QVector<double>)),paint,SLOT(slot_update_state(QVector<double>)),Qt::QueuedConnection);

}

void simmanager::matrecieved(Eigen::MatrixXd mat)
{
    if(mat.rows()==2)
    {
//stepin 输入1 * 2矩阵
        Eigen::MatrixXd matreturn;
        matreturn.resize(4,1);
        matreturn.setOnes();
        m_sim->control_0(0,0)=mat(0,0);
         m_sim->control_0(1,0)=mat(1,0);
        ODE_service->step_in();
        matreturn=m_sim->state;
        decoder->sendMAT(matreturn,m_TCP);
        return;
    }
    if(mat.rows()==4)
    {
//setstate  输入 4*1矩阵 x y vx vy
        Eigen::MatrixXd matreturn;
        matreturn.resize(1,1);
        matreturn.setOnes();
        m_sim->state(0,0)=mat(0,0);
        m_sim->state(1,0)=mat(1,0);
        m_sim->state(2,0)=mat(2,0);
        m_sim->state(3,0)=mat(3,0);
        decoder->sendMAT(matreturn,m_TCP);
        return;
    }

}

