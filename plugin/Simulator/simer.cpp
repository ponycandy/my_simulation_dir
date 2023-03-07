#include "simer.h"
#include "QtDebug"
#include <QElapsedTimer>
#include <QCoreApplication>

Simer::Simer(QObject *parent)
{
    dt=30;
}

void Simer::run()
{
    if(functor==NULL)
    {
        qDebug()<<"ODE function is not asigned!!";
        return;
    }
    else
    {
        do
        {
            QElapsedTimer et;
            et.start();

            functor->ode_function(act_array,state_array);
            functor->sensor(state_array);
            functor->broad_cast(state_array,act_array,sensor_data);
            functor->control(sensor_data,state_array);

            while(et.elapsed()<dt)//ms
            {
                QCoreApplication::processEvents();
            }
        }while (1);
    }
}

void Simer::stepin()
{
    functor->control(sensor_data,state_array);
    functor->ode_function(act_array,state_array);
    functor->sensor(state_array);
    functor->broad_cast(state_array,act_array,sensor_data);
}

Simer::Simer(double t)
{
    dt=t;
}
