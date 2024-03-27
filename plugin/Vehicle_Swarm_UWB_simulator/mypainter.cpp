#include "mypainter.h"
#include "QtDebug"
#include "xmlcore.h"
#include "Vehicle_Swarm_UWB_simulatorActivator.h"
MYpainter::MYpainter(QObject *parent) : QObject(parent)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");
    Eigen::MatrixXd obsmats;
    obsmats.resize(1,3);
    xmlreader.xmlRead("circle_num",obsnum);
    for(int i=1;i<=obsnum;i++)
    {
        QString obs_term_name="OBS_"+QString::number(i)+"_vertexparams";
        xmlreader.xmlRead(obs_term_name.toStdString(),obsmats);
        tripR circle;
        circle.x=obsmats(0,0);
        circle.y=obsmats(0,1);
        circle.r=obsmats(0,2);
        OBSmap.insert(i,circle);
    }
    obs_brush.setColor(Qt::blue);
    obs_brush.setStyle(Qt::SolidPattern);
    traj_brush.setColor(Qt::green);
    traj_brush.setStyle(Qt::SolidPattern);
    coordinate_brush.setColor(QColor(100,100,0));
    coordinate_brush.setStyle(Qt::SolidPattern);

    pointnum=0;
    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    Vehicle_Swarm_UWB_simulatorActivator::subscribeslot(this,SLOT(updateTargetpos(Eigen::MatrixXd))
                                                        ,"Predictbroadcast",
                                                        Qt::QueuedConnection);



}

void MYpainter::draw()
{
    QPen m_pen;
    //绘制橙的固定坐标系
    m_pen.setColor(QColor(100,100,0));
    m_pen.setStyle(Qt::DashLine);
    m_animator->brush_painter->setPen(m_pen);

    m_animator->draw_line(0,0,30,0);
    m_animator->draw_line(0,0,0,30);
}
void MYpainter::updateTargetpos(Eigen::MatrixXd target)
{
    int col=target.cols();
    int row=target.rows();
    pointnum=row;
    targetmat.resize(row,col);
    targetmat=target.eval();
}
