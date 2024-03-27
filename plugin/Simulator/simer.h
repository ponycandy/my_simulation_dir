#ifndef SIMER_H
#define SIMER_H

#include <QObject>
#include <QThread>
#include <include/GL_2D/ODE_functor.h>
class Simer : public QThread
{
    Q_OBJECT
public:
    explicit Simer(QObject *parent = nullptr);
    void run() override;
    void stepin();
    Simer(double t);
    double dt;
    bool Ifhault=false;
    ODE_functor *functor;
    Eigen::MatrixXd act_array;
    Eigen::MatrixXd state_array;
    Eigen::MatrixXd sensor_data;

signals:

};

#endif // SIMER_H
