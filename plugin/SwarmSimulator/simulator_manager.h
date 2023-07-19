#ifndef SIMULATOR_MANAGER_H
#define SIMULATOR_MANAGER_H

#include <QObject>
#include <service/Animateservice.h>
#include <service/SimDynamicsservice.h>
#include <service/CollisionDetectservice.h>
#include <service/SwarmSimservice.h>
#include <mypainter.h>
#include <simulator.h>
#include <FILE_manage/f_manager.h>
class simulator_manager : public QObject,public SwarmSimservice
{
    Q_OBJECT
public:
    explicit simulator_manager(QObject *parent = nullptr);
    Animateservice * getwidgetoperator() override;
    SwarmSimservice* cloneservice() override;
    SimDynamicsservice * get_simer() override;
    QMap<int, SwarmAgent *> getagentgroup() override;
    void startsim() override;
    void init_plant(int steptime, QString configfile, SwarmAgent *singleagents) override;
    void set_neib_sequnce(int flag) override;
    Animateservice *Anim_service;
    SimDynamicsservice* SimDy_service;
    CollisionDetectservice* Colli_service;
    MYpainter *paint;
    Simulator *m_sim;
    int thread_ID;
    int neibseq;


signals:
    void startsimnow();
public slots:
    void slotstartsim();

};

#endif // SIMULATOR_MANAGER_H
