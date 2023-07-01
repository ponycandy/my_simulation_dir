#include "visualize.h"
#include "xmlcore.h"
#include "TestPolyPaintingActivator.h"
#include "event/eventype.h"
visualize::visualize(QObject *parent)
    : QObject{parent}
{
    qRegisterMetaType<QVector<PolyParams>>("QVector<PolyParams>");
    TestPolyPaintingActivator::subscribeslot(this,SLOT(update_agent(QVector<PolyParams>,double,double)),UCSEVENT::Display_POlys,Qt::QueuedConnection);
    xmlCore xml_reader("./config/Polys/constrainParams.xml");
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("steps",dec_num);

    xml_reader.xmlRead("pointnum",point_num);
    xml_reader.xmlRead("step_time",steptime);
    initstates_of_animals.resize(4,1);
    xml_reader.xmlRead("Initstate",initstates_of_animals);

    for(int j=0;j<agentnum;j++)
    {
        PolyParams single_poly;
        single_poly.configfiename="./config/Polys/constrainParams"+QString::number(j)+".xml";
        single_poly.initilization();
        m_polys.insert(j,single_poly);
    }
    for(int j=0;j<agentnum;j++)
    {
        Eigen::VectorXd x;
        x.resize(5*point_num);
        x.setRandom();
        for(int i=0;i<point_num;i++)
        {
            x(5*i+4)=dec_num*steptime/point_num;
        }
        m_polys[j].packvariable(x);
    }

    resolution=0.05;
    //    QBrush obs_brush;
    //    obs_brush.setColor(Qt::blue);
    //    obs_brush.setStyle(Qt::SolidPattern);
    agent_brush.setColor(Qt::green);
    agent_brush.setStyle(Qt::SolidPattern);
    x_pos=initstates_of_animals(0,0);
    y_pos=initstates_of_animals(1,0);

}

void visualize::draw()
{
    m_animator->brush_painter->setBrush(agent_brush);
    m_animator->draw_circle(x_pos,y_pos,1);

    QPen pen(Qt::red); // creates a blue pen
    pen.setWidth(5); // sets the pen width to 3 pixels

    m_animator->brush_painter->setPen(pen);

    pos_and_derivative set;
    int iternum=dec_num*steptime/resolution;
    for(int i=0;i<agentnum;i++)
    {
        m_polys[i].Get_pos_and_derivative_set(0,set,0);
        double x=set.x0;
        m_polys[i].Get_pos_and_derivative_set(0,set,1);
        double y=set.x0;
        m_animator->Start_a_path(x,y);
        for(int k=1;k<iternum;k++)
        {
            //计算单个点的坐标
            calc_coordinate(i,0,k*resolution,x,y);
            m_animator->Add_path_point(x,y);
        }
        m_animator->draw_spline();

    }

    //    for(int j=0;j<3;j++)
    //    {
    //        m_animator->Start_a_path(j,j);
    //        for(int i=0;i<10;i++)
    //        {
    //            m_animator->Add_path_point(j+i,j+2*i);
    //        }
    //        m_animator->draw_spline();
    //    }


}

void visualize::calc_coordinate(int agent, int phase, double time, double &x, double &y)
{
    x=m_polys[agent].Get_Single_value_any(time,0);
    y=m_polys[agent].Get_Single_value_any(time,1);
}

void visualize::update_agent(QVector<PolyParams> polys, double finalx, double finaly)
{
    m_polys=polys;
    x_pos=finalx;
    y_pos=finaly;
}

