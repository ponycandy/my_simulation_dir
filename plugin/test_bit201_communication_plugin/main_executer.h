#ifndef MAIN_EXECUTER_H
#define MAIN_EXECUTER_H

#include <QObject>
#include <startwidget.h>
class main_executer : public QObject
{
    Q_OBJECT
public:
    explicit main_executer(QObject *parent = nullptr);
    startwidget *m_widget;
signals:

};

#endif // MAIN_EXECUTER_H
