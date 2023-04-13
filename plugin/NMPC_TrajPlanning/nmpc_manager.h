#ifndef NMPC_MANAGER_H
#define NMPC_MANAGER_H

#include <QObject>
#include <nmpc_problem.h>
#include <nmpc_constructor.h>
class NMPC_manager : public QObject
{
    Q_OBJECT
public:
    explicit NMPC_manager(QObject *parent = nullptr);
    NMPC_Constructor *m_nmpc_construct;
signals:

};

#endif // NMPC_MANAGER_H
