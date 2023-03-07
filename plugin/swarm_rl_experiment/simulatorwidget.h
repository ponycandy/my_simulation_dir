#ifndef SIMULATORWIDGET_H
#define SIMULATORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
namespace Ui {
class simulatorWidget;
}

class simulatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit simulatorWidget(QWidget *parent = nullptr);
    ~simulatorWidget();
    QVBoxLayout *Vbox;

private:
    Ui::simulatorWidget *ui;

};

#endif // SIMULATORWIDGET_H
