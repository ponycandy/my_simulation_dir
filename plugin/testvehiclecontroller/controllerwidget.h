#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H

#include <QWidget>

namespace Ui {
class controllerwidget;
}

class controllerwidget : public QWidget
{
    Q_OBJECT

public:
    explicit controllerwidget(QWidget *parent = nullptr);
    ~controllerwidget();

signals:
    void send_one();
private slots:
    void on_pushButton_clicked();

private:
    Ui::controllerwidget *ui;
};

#endif // CONTROLLERWIDGET_H
