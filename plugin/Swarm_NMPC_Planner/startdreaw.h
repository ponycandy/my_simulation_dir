#ifndef STARTDREAW_H
#define STARTDREAW_H

#include <QWidget>
#include <PolyParams.h>
namespace Ui {
class startdreaw;
}

class startdreaw : public QWidget
{
    Q_OBJECT

public:
    explicit startdreaw(QWidget *parent = nullptr);
    ~startdreaw();
    QVector<PolyParams> m_polys;
    double fx;
    double fy;

private slots:
    void on_pushButton_clicked();
signals:
    void sig_start(QVector<PolyParams> m_p,double x,double y);

private:
    Ui::startdreaw *ui;
};

#endif // STARTDREAW_H
