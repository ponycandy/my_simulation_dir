#ifndef PLATFORMSCONTROL_H
#define PLATFORMSCONTROL_H

#include <QWidget>

namespace Ui {
class platformsControl;
}

class platformsControl : public QWidget
{
    Q_OBJECT

public:
    explicit platformsControl(QWidget *parent = nullptr);
    ~platformsControl();

private:
    Ui::platformsControl *ui;
};

#endif // PLATFORMSCONTROL_H
