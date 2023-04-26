
#ifndef MAINEXEC_H
#define MAINEXEC_H


#include <QObject>
#include <service/MPC_Trackerservice.h>
#include <dynamic_function.h>
#include <form.h>
class mainexec : public QObject
{
    Q_OBJECT
public:
    explicit mainexec(QObject *parent = nullptr);
    dynamic_function *funtor;
    MPC_Trackerservice *m_service;
    Form *m_wi;
signals:

public  slots:
    void start_solve();


};

#endif // MAINEXEC_H
