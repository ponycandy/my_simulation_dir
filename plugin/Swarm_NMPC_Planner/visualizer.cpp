#include "visualizer.h"

visualizer::visualizer(QObject *parent)
    : QObject{parent}
{

}

void visualizer::draw()
{
//    m_animator->brush_painter->setBrush(obs_brush);
//    QPolygonF poly;
//    poly<<QPointF(x_pos+cartwidth/2,-cartheight/2)
//         <<QPointF(x_pos-cartwidth/2,-cartheight/2)
//         <<QPointF(x_pos-cartwidth/2,cartheight/2)
//         <<QPointF(x_pos+cartwidth/2,cartheight/2);
//    m_animator->draw_polygon(poly);
//    m_animator->brush_painter->setBrush(agent_brush);
//    m_animator->draw_square_oneside(x_pos,0,pendwidth,penlength,-phi+3.1415926535);
}

void visualizer::draw_spline(Eigen::MatrixXd var)
{
//    double x0=var(0,0);double dx0=var(0,1);double x1=var(0,2);double dx1=var(0,3);double lastime=var(0,4);
//    double y0=var(1,0);double dy0=var(1,1);double y1=var(1,2);double dy1=var(1,3);
//    double T0=lastime;
//    double a0=x0;
//    double a1=dx0;
//    double a2=-(3*(x0-x1)+T0*(2*dx0+dx1))/(T0*T0);
//    double a3=(2*(x0-x1)+T0*(dx0+dx1))/(T0*T0*T0);
//    T0=0;
//    int itertimes=lastime/resolution;//除法强制取整
//    for(int i=1;i<itertimes;i++)
//    {
//        T0=i*resolution;
//        double x_value=a0+T0*(a1+T0*(a2+a3*T0));
//        double y_value=a0+T0*(a1+T0*(a2+a3*T0));
//    }

}

void visualizer::slot_update_state(Eigen::MatrixXd state_array)
{
//根据四元数组绘制三次曲线
//    m_animator->draw_Spline();
}
