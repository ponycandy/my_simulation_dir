#ifndef MAINEXECUTION_H
#define MAINEXECUTION_H

#include <QObject>
#include "qtimer.h"
#include "gpcsmat.h"
#include "gpcsnode.h"
struct MyData {
    int id;
    double value;
    char name[20];

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& id;
        ar& value;
        ar& name;
    }
};

class mainExecution : public QObject
{
    Q_OBJECT
public:
    explicit mainExecution(QObject *parent = nullptr);
    void gpcscallback(const std::string& data);
    void gpcscallback_2(const std::string& data);

    QTimer *m_timer;
    QTimer *m_timer1;
     gpcs::gpcsnode *nh;//创建句柄
    gpcs::Publisher* somepuber;
signals:

private slots:
    void send_messages();
    void spinonce();

};

#endif // MAINEXECUTION_H
