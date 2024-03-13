#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "QPushButton"
#include "QFrame"
#include "service/Mapservice.h"
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr);
    void set_backgroundPannel(QWidget *pannel );
    void startanimate();
    QWidget *m_pannel;
    QPushButton *AddObstacle_plot;
    QPushButton *loadConfigFile;
    QPushButton *AddObstacle_coordinate;
    QPushButton *Add_Target;
    QPushButton *Add_Event;
    QFrame *Background;
    MapService *M_map;

private:
    void initUI();


signals:
};

#endif // CONTROLWIDGET_H
