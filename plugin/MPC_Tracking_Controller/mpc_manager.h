#ifndef MPC_MANAGER_H
#define MPC_MANAGER_H

#include <QObject>
#include <mpc_constructor.h>
class MPC_manager : public QObject
{
    Q_OBJECT
public:
    explicit MPC_manager(QObject *parent = nullptr);
    MPC_Constructor *m_mpc_construct;
signals:

};

#endif // NMPC_MANAGER_H
