#include "vomanager.h"


#include "Slam_VisualizerActivator.h"
vomanager::vomanager(QObject *parent)
{
    anim=Slam_VisualizerActivator::getService<Animateservice3Dservice>("Animateservice3Dservice");

    SD=new Slam_Drawer;
    anim->register_painter(SD);
    MWidget=anim->getwidget();
    MWidget->show();



//    nh=new gpcs::gpcsnode;
//    nh->init("Qtnode");
//    nh->subscribe("Slam_data/3D_points",
//                  std::bind(&vomanager::Point3dCallback, this,std::placeholders::_1));
//    nh->subscribe("Slam_data/Camerapos",
//                  std::bind(&vomanager::KeyframeCallback, this,std::placeholders::_1));
//    m_timer = new QTimer(this);
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(spinonce()));
//    m_timer->start(30);


    anim->start_animate();
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
