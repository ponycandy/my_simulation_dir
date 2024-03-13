#ifndef HRONSLIDER_H
#define HRONSLIDER_H

#include <QWidget>
#include <QPainter>
class HronSlider : public QWidget
{
    Q_OBJECT
public:
    explicit HronSlider(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;
private:
    double valueNow;
    double unit;
    int unitlength_pic;
public slots:
    void updateSliderValue(double value);
    void setunit(double unit_value,int unitleng);

signals:
};

#endif // HRONSLIDER_H
