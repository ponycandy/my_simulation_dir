#ifndef DIRECTIONHRON_H
#define DIRECTIONHRON_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
class DirectionHron : public QWidget
{
    Q_OBJECT
public:
    explicit DirectionHron(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;
    double normalizeAngle(double angle) ;
    double valueNow;
    double unit;
    double unitlength_pic;
    QVector<QString> directions;
signals:


public slots:
    void updateSliderValue(double value);
    void setunit(double unit_value,int unitleng);
};

#endif // DIRECTIONHRON_H
