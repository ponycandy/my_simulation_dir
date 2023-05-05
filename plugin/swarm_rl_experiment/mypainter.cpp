#include "mypainter.h"
#include "QtDebug"
#include "FILE_manage/f_manager.h"
MYpainter::MYpainter(QObject *parent) : QObject(parent)
{
    agent_brush.setColor(Qt::green);
    agent_brush.setStyle(Qt::SolidPattern);
    QString agent_mat=f_Read_TXT("./config/agent_mat_ref.txt");
    int agent_num=f_get_mat_height(agent_mat);
    int status_num=f_get_mat_width(agent_mat);
    ref_mat.resize(agent_num,status_num);
    for(int i=1;i<=agent_num;i++)
    {
        for(int j=0;j<status_num;j++)
        {
            ref_mat(i-1,j)=f_get_mat_at(i-1,j,agent_mat).toDouble();
        }
    }
}

void MYpainter::draw()
{

    m_animator->brush_painter->setBrush(agent_brush);
    double x,y,phi;

    for (int i=1;i<=3;i++)
    {
        x=ref_mat(i-1,0);y=ref_mat(i-1,1);phi=ref_mat(i-1,2);

        m_animator->draw_beacon(x,y,phi);
    }


}

