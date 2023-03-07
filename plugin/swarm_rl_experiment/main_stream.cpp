#include "main_stream.h"
#include "service/Animateservice.h"
#include "service/SimDynamicsservice.h"
#include "service/SwarmSimservice.h"
#include "swarm_rl_experimentActivator.h"
#include "defines/CpyDefines.h"
#include "OSGIEVENT.h"
main_stream::main_stream(QObject *parent) : QObject(parent)
{
    singleone=new vehicle;
    widgetm=new simulatorWidget;
    TCPsoc=swarm_rl_experimentActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
    swarm_rl_experimentActivator::subscribeslot(this,SLOT(matrecieved(Eigen::MatrixXd))
                                            ,OSGIEVENT::MAT_GET_NOW,Qt::QueuedConnection);
    //    Animateservice *Anim_service=swarm_rl_experimentActivator::getService<Animateservice>("Animateservice");
    SwarmSimservice *swarmsim=swarm_rl_experimentActivator::getService<SwarmSimservice>("SwarmSimservice");

    swarmsim->init_plant(30,0,singleone);
    Animateservice *anim=swarmsim->getwidgetoperator();
    QWidget *m_widget=anim->getwidget();
    m_widget->resize(1200,800);
    m_widget->show();
//    widgetm->Vbox->addWidget(m_widget);
//    widgetm->show();

    //    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
//    dysim->set_step_in_mode(1);
    swarmsim->startsim();
//    swarmsim1->startsim();

//    a_test_timer = new QTimer(this);
//    connect(a_test_timer, SIGNAL(timeout()), this, SLOT(step_once()));
//    a_test_timer->start(30);
    //    setupEvent();
    //    m_sim->update_obs();

    //    Anim_service->register_painter(paint);
    //    Anim_service->resizeWindow(1200,800);
    //    ODE_service->set_ODE(m_sim);
    //    //这里开始主流程
    //    Anim_service->start_animate();
    //    ODE_service->start_sim();


}

void main_stream::step_once()
{
//    dysim_1->step_in();
//    dysim->step_in();

}

void main_stream::matrecieved(Eigen::MatrixXd mat)
{
    if(mat.rows()==1 && mat.cols()==1)
    {

        dysim->step_in();
    }
    if(mat.cols()==5)
    {
        //change agentgroup state and control!!
        dysim->step_in();
    }

}
