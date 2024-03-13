#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <QWidget>
#include <QFrame>
#include <multistatusslider.h>
#include <QPushButton>
class Devicecontrol : public QWidget
{
    Q_OBJECT
public:
    explicit Devicecontrol(QWidget *parent = nullptr);
    QFrame *frame;
    multistatusSlider *chasis_powered_slider;
    multistatusSlider *workload_powered_slider;
    multistatusSlider *shift_change_slider;
    multistatusSlider *weapon_change_slider;

    QPushButton *button;

signals:
    void sig_update_chasis_state_mode(int workload_enable,int chasis_enable,int weapon_enable);

private slots:
    void On_Sendcommand();
};

#endif // DEVICECONTROL_H
