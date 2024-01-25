#include "vehicle_manager.h"
#include "Vehicle_simulatorActivator.h"
vehicle_manager::vehicle_manager()
{
    m_anim=Vehicle_simulatorActivator::getService<Animateservice>("Animateservice");

    simer=Vehicle_simulatorActivator::getService<SimDynamicsservice>("SimDynamicsservice");
    m_decoder=Vehicle_simulatorActivator::getService<CPYcoderservice>("CPYcoderservice");
    m_decoder=m_decoder->cloneservice();//注意，这里一定要用clone服务，否则会激发两次
    //每次我都忘记这个
    m_decoder->Client_mode_connect("127.0.0.1",8080);
    m_decoder->Bind_Slot(this,SLOT(get_control(Eigen::MatrixXd)));
    m_sim=new Simulator;
    //先适用road_model计算100米的坐标长度：
//map?

//
    m_painter=new MYpainter;
    qRegisterMetaType<Eigen::MatrixXd>();
    connect(m_sim,SIGNAL(sig_updatepos(Eigen::MatrixXd)),m_painter,SLOT(slot_update_state(Eigen::MatrixXd)));
    m_anim->register_painter(m_painter);
    m_sim->delta_t=0.01;
    m_widget=m_anim->getwidget();

    m_anim->setbackground(Qt::white);
     m_widget->show();
    m_anim->start_animate();
    simer->set_delta_t(0.01);
    simer->set_ODE(m_sim);
    simer->set_step_in_mode(1);
    simer->start_sim();


//    pos_xy po;
//    double s=0;
//    while(s<100)
//    {

//        double curv=m_sim->roadmodel(s);
//        s+=0.5;
//    }

}

void vehicle_manager::get_control(Eigen::MatrixXd mat)
{
    if(mat.rows()==3)
    {
        //stepin 输入1 * 3矩阵
        Eigen::MatrixXd matreturn;
        matreturn.resize(6,1);
        matreturn.setOnes();
        m_sim->controlmat=mat;
        simer->step_in();
        matreturn=m_sim->feedbackstate;
        m_decoder->sendMAT(matreturn);
        return;
    }
    if(mat.rows()==7)
    {
        //setstate  输入 7*1矩阵 x y vx vy
        Eigen::MatrixXd matreturn;
        matreturn.resize(1,1);
        matreturn.setOnes();
        m_sim->Statemat=mat;
        m_sim->posstate.setZero();
        m_decoder->sendMAT(matreturn);
        return;
    }
}
