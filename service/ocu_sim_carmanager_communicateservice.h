//ocu_sim_carmanager_communicateservice.h
#ifndef OCU_SIM_CARMANAGER_COMMUNICATESERVICE_H
#define OCU_SIM_CARMANAGER_COMMUNICATESERVICE_H
#include <QObject>
class ocu_sim_carmanager_communicateservice
{
public:
    virtual ~ocu_sim_carmanager_communicateservice(){}
    virtual void send_motion_command(double linear,double omega)=0;
    virtual void send_Chasis_command(double linear,double omega)=0;
    virtual void sim_init() =0;

};
#define ocu_sim_carmanager_communicateservice_iid "ocu_sim_carmanager_communicateservice"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(ocu_sim_carmanager_communicateservice,ocu_sim_carmanager_communicateservice_iid  )
QT_END_NAMESPACE
#endif
