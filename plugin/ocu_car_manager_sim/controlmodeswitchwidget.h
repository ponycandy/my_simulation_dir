#ifndef CONTROLMODESWITCHWIDGET_H
#define CONTROLMODESWITCHWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QSlider>
#include <multistatusslider.h>
#include <qlineedit.h>
#include <QPushButton>
class ControlModeSwitchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlModeSwitchWidget(QWidget *parent = nullptr);
    QFrame *frame;
    QLabel *SpeedLimit;
    QPushButton *butt;
    QLineEdit *speedinput;
    QString controlmode;
    multistatusSlider *chasisslider;
signals:
    void sig_updateControlmode(short controlmode,double speed);
private slots:
    void On_Sendcommand();
    void On_updatecontrolmode(QString name);

};

#endif // CONTROLMODESWITCHWIDGET_H
