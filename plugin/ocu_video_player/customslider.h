#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>
#include <QPainter>
class CustomSlider : public QWidget
{
    Q_OBJECT
public:
    explicit CustomSlider(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;
signals:
private:
    double valueNow;
    double unit;
    int unitlength_pic;

public slots:
    void updateSliderValue(double value);
    void setunit(double unit_value,int unitleng);
};

#endif // CUSTOMSLIDER_H
