//Widframeopservice.h
#ifndef WIDFRAMEOPSERVICE_H
#define WIDFRAMEOPSERVICE_H
#include <QObject>
#include <QMenuBar>
class Widframeopservice
{
public:
    virtual ~Widframeopservice(){}
    virtual void Add_Menu(QMenuBar* menu,QString Menuname)=0;
    virtual void remove_Menu(QString Menuname)=0;
};
#define Widframeopservice_iid "Widframeopservice"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(Widframeopservice,Widframeopservice_iid  )
QT_END_NAMESPACE
#endif
