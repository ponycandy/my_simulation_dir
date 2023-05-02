
#ifndef MAINEXE_H
#define MAINEXE_H


#include <QObject>
#include "form.h"
#include "service/TCPserverservice.h"
#include "service/MPC_Trackerservice.h"
#include "dynamic_function.h"
class mainexe : public QObject
{
    Q_OBJECT
public:
    explicit mainexe(QObject *parent = nullptr);
    TCPserverservice *m_service1;
    MPC_Trackerservice *m_service2;
    Eigen::MatrixXd statenow;
    Form *widgetm;
    dynamic_function *functor;
signals:
    void mget_state_now();
    void outer_stepin(Eigen::MatrixXd act);
public slots:
    void state_return(Eigen::MatrixXd state);
    void solve();
};

#endif // MAINEXE_H
