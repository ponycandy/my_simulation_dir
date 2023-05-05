#include "main_stream.h"
#include "service/Animateservice.h"
#include "service/SimDynamicsservice.h"
#include "service/SwarmSimservice.h"
#include "swarm_rl_experimentActivator.h"
#include "defines/CpyDefines.h"
#include "OSGIEVENT.h"
#include "include/FILE_manage/f_manager.h"
main_stream::main_stream(QObject *parent) : QObject(parent)
{
    singleone=new vehicle;
    widgetm=new simulatorWidget;
    m_paint=new MYpainter;

    coef_r1=0.5;
    coef_r2=0.5;
    ref_mat.resize(3,3);
    ref_mat.setZero();
    init_mat.resize(3,3);
    init_mat.setZero();
    init_ref();
    Q_mat.resize(3,3);
    Q_mat.setIdentity();
    R_mat.resize(2,2);
    R_mat.setIdentity();
    tempstate.resize(3,3);
    tempstate.setZero();
    TCPsoc=swarm_rl_experimentActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
    swarm_rl_experimentActivator::subscribeslot(this,SLOT(matrecieved(Eigen::MatrixXd))
                                                ,OSGIEVENT::MAT_GET_NOW,Qt::QueuedConnection);
    //    Animateservice *Anim_service=swarm_rl_experimentActivator::getService<Animateservice>("Animateservice");
    SwarmSimservice *swarmsim=swarm_rl_experimentActivator::getService<SwarmSimservice>("SwarmSimservice");
    TCPsoc->setport("8001","127.0.0.1");
    TCPsoc->connectport();
    decoder=swarm_rl_experimentActivator::getService<CPYcoderservice>("CPYcoderservice");
    swarmsim->init_plant(30,0,singleone);
    agentgroup=swarmsim->getagentgroup();
    Animateservice *anim=swarmsim->getwidgetoperator();
    anim->register_painter(m_paint);
    QWidget *m_widget=anim->getwidget();
    m_widget->resize(1200,800);
    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
    dysim->set_step_in_mode(1);
    swarmsim->startsim();
}

void main_stream::init_ref()
{
    QString agent_mat=f_Read_TXT("./config/agent_mat_ref.txt");
    int agent_num=f_get_mat_height(agent_mat);
    int status_num=f_get_mat_width(agent_mat);
    for(int i=1;i<=agent_num;i++)
    {
        for(int j=0;j<status_num;j++)
        {
            ref_mat(i-1,j)=f_get_mat_at(i-1,j,agent_mat).toDouble();
        }
    }
    agent_mat=f_Read_TXT("./config/agent_mat.txt");

    for(int i=1;i<=agent_num;i++)
    {
        for(int j=0;j<status_num;j++)
        {
            init_mat(i-1,j)=f_get_mat_at(i-1,j,agent_mat).toDouble();
        }
    }
}

void main_stream::healthy_plant_stepin()
{
    Eigen::MatrixXd d_state;
    d_state.resize(3,1);
    d_state.setZero();
    for(int i=0;i<=2;i++)
    {
        SwarmAgent *agent=agentgroup.value(i+1);
        double angle=agent->state_vector(2,0);
        d_state(0,0)=agent->act_vector(0,0)*cos(angle);
        d_state(1,0)=agent->act_vector(0,0)*sin(angle);
        d_state(2,0)=agent->act_vector(1,0);
        d_state=agent->state_vector+d_state*0.03;
        for(int j=0;j<=2;j++)
        {
            tempstate(i,j)=d_state(j,0);
        }
    }


}

void main_stream::calc_reward()
{
    rp=0;
    rf=0;
    rpf=0;
    for(int i=0;i<=2;i++)
    {
        Eigen::MatrixXd mid_state=tempstate.block(i,0,1,3)-ref_mat.block(i,0,1,3);
        SwarmAgent *agent=agentgroup.value(i+1);
        Eigen::MatrixXd state_vector_trans=agent->state_vector.transpose();
        Eigen::MatrixXd mid_state_f=state_vector_trans-ref_mat.block(i,0,1,3);
        Eigen::MatrixXd act_mid=agent->act_vector;
        rp+=(mid_state*Q_mat*mid_state.transpose()+act_mid.transpose()*R_mat*act_mid)(0,0);
        rf+=(mid_state_f*Q_mat*mid_state_f.transpose()+act_mid.transpose()*R_mat*act_mid)(0,0);
    }
    rpf=abs(rp-rf);
    rp=-rp;
    rpf=-rpf;
    rf=-rf;
    //    tempstate.transpose()*Q_mat*tempstate+;
}

void main_stream::step_once()
{
    //    dysim_1->step_in();
    //    dysim->step_in();

}

void main_stream::matrecieved(Eigen::MatrixXd mat)
{
    //输入数据所有机器人的一次性控制量，维度重新计算
    if(mat.rows()==3 && mat.cols()==2)//控制指令
    {
        Eigen::MatrixXd matreturn;
        int i=0;
        QMap<int, SwarmAgent *>::const_iterator iter = agentgroup.cbegin();
        while (iter != agentgroup.cend())
        {
            iter.value()->act_vector(0,0)=mat(i,0);
            iter.value()->act_vector(1,0)=mat(i,1);
            ++iter;
            i++;
        }
        healthy_plant_stepin();
        dysim->step_in();
        matreturn.resize(3,9);
        matreturn.setZero();

        iter = agentgroup.cbegin();
        for (int i=0;i<=2;i++)
        {
            matreturn(0,3*i)=iter.value()->state_vector(0,0)-ref_mat(i,0);
            matreturn(0,3*i+1)=iter.value()->state_vector(1,0)-ref_mat(i,1);
            matreturn(0,3*i+2)=iter.value()->state_vector(2,0)-ref_mat(i,2);
            iter++;
        }
        //assign healthy lines
        i=0;
        iter = agentgroup.cbegin();
        while (iter != agentgroup.cend())
        {
            matreturn(1,3*i)=iter.value()->state_vector(0,0)-ref_mat(i,0);
            matreturn(1,3*i+1)=iter.value()->state_vector(1,0)-ref_mat(i,1);
            matreturn(1,3*i+2)=iter.value()->state_vector(2,0)-ref_mat(i,2);
            matreturn(2,3*i)=iter.value()->act_vector(0,0);
            matreturn(2,3*i+1)=iter.value()->act_vector(1,0);
            ++iter;
            i+=1;
        }
        //assign false lines
        calc_reward();
        matreturn(2,2)=rp;
        matreturn(2,5)=rf;//这里放终止条件,当误差过大的时候使用
        matreturn(2,8)=rpf;
        //奖励混合比例由python决定
        //calc reward
        decoder->sendMAT(matreturn,TCPsoc);//返回3*9矩阵
        //then send mat
    }
    //输出数据，一次步进完成后的所有状态变量，以及
    //此处计算的奖励值

    if(mat.rows()==1 && mat.cols()==1)//重置指令
    {
        //change agentgroup state and control!!
        Eigen::MatrixXd matreturn;
        matreturn.resize(3,9);
        matreturn.setZero();
        QMap<int, SwarmAgent *>::const_iterator iter = agentgroup.cbegin();
        int i=0;
        while (iter != agentgroup.cend())
        {
            iter.value()->state_vector=init_mat.block(i,0,1,3).transpose();
            ++iter;
            i++;
        }
        for(int i=0;i<=2;i++)
        {
            for(int j=0;j<=2;j++)
            {

                tempstate(i,j)=agentgroup.value(i+1)->state_vector(j,0);
                matreturn(1,3*i+j)=tempstate(i,j);

            }
        }
        decoder->sendMAT(matreturn,TCPsoc);//返回3*9矩阵
    }

}
