#ifndef BATTERYSTATUS_H
#define BATTERYSTATUS_H

#include <QWidget>
#include <qpainter.h>
class BatteryStatus : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryStatus(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;

signals:
private:
    double valueNow;
public slots:
    void updateSliderValue(double value);
};

#endif // BATTERYSTATUS_H
