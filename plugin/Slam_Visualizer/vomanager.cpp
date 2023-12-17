#include "vomanager.h"



vomanager::vomanager(QObject *parent)
{
    nh=new gpcs::gpcsnode;
    nh->init("Qtnode");
    nh->subscribe("Slam_data/3D_points",
                  std::bind(&vomanager::Point3dCallback, this,std::placeholders::_1));
    nh->subscribe("Slam_data/Camerapos",
                  std::bind(&vomanager::KeyframeCallback, this,std::placeholders::_1));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(spinonce()));
    m_timer->start(30);
}

void vomanager::KeyframeCallback(const std::string &data)
{
    std::cout<<"KeyframeCallback "<<std::endl;

    gpcs::mat matrix=gpcs::struct_load<gpcs::mat>(data);
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
            std::cout<<" "<<matrix[i][j]<<" ";
        }
        std::cout<<" "<<std::endl;
    }
    std::cout<<"endl"<<std::endl;

}

void vomanager::Point3dCallback(const std::string &data)
{
    std::cout<<"Point3dCallback "<<std::endl;

    gpcs::mat matrix=gpcs::struct_load<gpcs::mat>(data);
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
            std::cout<<" "<<matrix[i][j]<<" ";
        }
        std::cout<<" "<<std::endl;
    }
    std::cout<<"endl"<<std::endl;
}

void vomanager::spinonce()
{
    nh->spinonce();
}
