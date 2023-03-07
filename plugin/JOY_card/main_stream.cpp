#include "main_stream.h"
#include "service/Animateservice.h"
#include "service/SimDynamicsservice.h"
#include "JOY_cardActivator.h"
#include "QtDebug"
#include "QWidget"
#include "service/SwarmSimservice.h"
#include "FILE_manage/f_manager.h"
main_stream::main_stream(QObject *parent) : QObject(parent),paint(NULL)
{
      SwarmSimservice *a_service0=JOY_cardActivator::getService<SwarmSimservice>("SwarmSimservice");
      a_service=a_service0->cloneservice();
      QString mat= f_Read_TXT("./config/mat1.txt");
      qDebug()<<mat;
      qDebug()<<f_get_mat_height(mat);
      qDebug()<<f_get_mat_width(mat);
      qDebug()<<f_get_mat_at(0,1,mat);
//      classA_test atest;
//      atest.setID(1);
//      qDebug()<<atest.getID();

//    paint=new MYpainter;
//    m_sim=new Simulator;
//    m_sim->init();
//    Animateservice *Anim_service=JOY_cardActivator::getService<Animateservice>("Animateservice");
//    SimDynamicsservice *ODE_service=JOY_cardActivator::getService<SimDynamicsservice>("SimDynamicsservice");
//    a_serive=ODE_service;


//    a_test_timer = new QTimer(this);
//    connect(a_test_timer, SIGNAL(timeout()), this, SLOT(step_once()));


//    setupEvent();
//    m_sim->update_obs();

//    Anim_service->register_painter(paint);
//    Anim_service->resizeWindow(1200,800);
//    a_serive->set_ODE(m_sim);
//    //这里开始主流程
//    QWidget *awidget=Anim_service->getwidget();
//    awidget->show();
//    Anim_service->start_animate();
//    a_serive->set_step_in_mode(1);
//    a_serive->start_sim();

//    a_test_timer->start(30);
}

void main_stream::setupEvent()
{
    qRegisterMetaType<QMap<int,Single_agent*>>("QMap<int,Single_agent*>");
    connect(m_sim,SIGNAL(sig_agent_state_update(QMap<int,Single_agent*>)),paint,SLOT(slot_update_state(QMap<int,Single_agent*>)),Qt::QueuedConnection);


    qRegisterMetaType<QMap<int,single_obstacle*> >("QMap<int,single_obstacle*>");
    connect(m_sim,SIGNAL(sig_obs_state_update(QMap<int,single_obstacle*>)),paint,SLOT(slot_obs_state_update(QMap<int,single_obstacle*>)),Qt::QueuedConnection);

}

void main_stream::step_once()
{
//    a_serive->step_in();
}
