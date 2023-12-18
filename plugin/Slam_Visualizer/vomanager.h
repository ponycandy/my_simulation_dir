#ifndef VOMANAGER_H
#define VOMANAGER_H

#include "gpcsnode.h"
#include "gpcsmat.h"
#include "qtimer.h"
#include <QObject>
#include "service/Animateservice3Dservice.h"
#include "slam_drawer.h"
#include "QWidget"
class vomanager: public QObject
{
     Q_OBJECT
public:
     explicit vomanager(QObject *parent = nullptr);
    void KeyframeCallback(const std::string& data);
    void Point3dCallback(const std::string& data);

    gpcs::gpcsnode *nh;
    QTimer *m_timer;
    Animateservice3Dservice *anim;
    Slam_Drawer *SD;
    QWidget *MWidget;
signals:
    void posupdate(Eigen::MatrixXd mat);
private slots:
    void spinonce();

};

#endif // VOMANAGER_H
