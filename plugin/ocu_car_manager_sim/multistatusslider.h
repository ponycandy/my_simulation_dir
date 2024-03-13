#ifndef MULTISTATUSSLIDER_H
#define MULTISTATUSSLIDER_H

#include <QWidget>
#include <QSlider>
#include <Qlabel>
class multistatusSlider : public QWidget
{
    Q_OBJECT
public:
    explicit multistatusSlider(QWidget *parent = nullptr);
    void init(QVector<QString> list);

    QSlider *innerslider;
    QVector<QString> savedvector;
    QVector<QLabel*> labelvector;
signals:
void StatusChange(QString statusname);
private slots:
void on_Slider_valueChanged(int value) ;
};

#endif // MULTISTATUSSLIDER_H
