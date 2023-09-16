
#ifndef DATALOGSERVICE_H
#define DATALOGSERVICE_H

#include <QObject>
class Datalogservice
{
public:
    virtual ~Datalogservice(){}
    virtual void log(QString word,int level)=0;
    virtual void DeleteFile( QString fileName)=0;
    virtual void createlogfile(QString logfilename,int port)=0;
    virtual void createxlsfile(QString logfilename)=0;
    virtual void log(int rows,int colums,double value)=0;
    virtual Datalogservice* cloneservice()=0;
    virtual void savexlsfile()=0;

};
#define Datalogservice_iid "Datalogservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(Datalogservice,Datalogservice_iid  )
QT_END_NAMESPACE

#endif

