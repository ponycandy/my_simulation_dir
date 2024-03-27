#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "gpcsnode.h"
#include "include/jetsonnanoDATA/jetsonnanoDATA.h"
namespace Ui {
class controlwidget;
}

class controlwidget : public QWidget
{
    Q_OBJECT

public:
    explicit controlwidget(QWidget *parent = nullptr);
    ~controlwidget();
    gpcs::gpcsnode *node;
    jetson::motioncommand cmd;
    gpcs::Publisher* somepuber;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::controlwidget *ui;
};

#endif // CONTROLWIDGET_H
