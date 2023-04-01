#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <service/Tcpcommunicateservice.h>
#include <service/TCPserverservice.h>
namespace Ui {
class startwidget;
}

class startwidget : public QWidget
{
    Q_OBJECT

public:
    explicit startwidget(QWidget *parent = nullptr);
    ~startwidget();
    Tcpcommunicateservice *m_service;
    TCPserverservice *m_service_1;

private slots:
    void on_pushButton_clicked();
    void datarecieved(QByteArray data);

private:
    Ui::startwidget *ui;
};

#endif // STARTWIDGET_H
