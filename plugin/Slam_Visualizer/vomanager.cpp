#include "vomanager.h"


#include "Slam_VisualizerActivator.h"
vomanager::vomanager(QObject *parent)
{
    anim=Slam_VisualizerActivator::getService<Animateservice3Dservice>("Animateservice3Dservice");

    SD=new Slam_Drawer;
    anim->register_painter(SD);
    MWidget=anim->getwidget();
    MWidget->show();



    nh=new gpcs::gpcsnode;
    nh->init("Qtnode");
////    nh->subscribe("Slam_data/3D_points",
////                  std::bind(&vomanager::Point3dCallback, this,std::placeholders::_1));
    nh->subscribe("Slam_data/Camerapos",
                  std::bind(&vomanager::KeyframeCallback, this,std::placeholders::_1));
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(spinonce()));
    qRegisterMetaType<Eigen::MatrixXd>();
    connect(this, SIGNAL(posupdate(Eigen::MatrixXd)), SD, SLOT(add_pos(Eigen::MatrixXd)));
    m_timer->start(30);


    anim->start_animate();
}

void vomanager::KeyframeCallback(const std::string &data)
{


    gpcs::mat matrix=gpcs::struct_load<gpcs::mat>(data);
    Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>
        Trans(matrix.data.data(), 4, 4);
    //相机坐标系是右x下y前z
    //世界坐标是右x前y上z
    //首先要将旋转矩阵修正，也就是绕x轴旋转90度
    //其次，得到的位移和旋转坐标是相较于初始摄像机位置的旋转坐标，
    Eigen::MatrixXd toworld,towordl2;
    toworld.resize(4,4);
    toworld.setIdentity();towordl2=toworld;
    toworld<<-1,0,0,0
            ,0,0,-1,0
            ,0,1,0,0
            ,0,0,0,1;
    toworld=toworld*Trans;
    Trans(0,3)=toworld(0,3);Trans(1,3)=toworld(1,3);Trans(2,3)=toworld(2,3);

std::cout<<"comehere "<<std::endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            std::cout<<" "<<matrix[i][j]<<" ";
        }
        std::cout<<" "<<std::endl;
    }

    //得到的矩阵是相对于相机初始位置的，所以还要转化一下到世界坐标系下
    toworld<<1,0,0,0,
        0,0,1,0,
        0,-1,0,0,
        0,0,0,1;
        towordl2<<-1,0,0,0,
            0,-1,0,0,
            0,0,1,0,
            0,0,0,1;
    //
      //  Trans.block(0,0,3,3)=toworld.block(0,0,3,3)*Trans.block(0,0,3,3);
//左右手坐标系的转化（idiot）
        Trans.block(0,0,3,3)=toworld.block(0,0,3,3)*towordl2.block(0,0,3,3)*Trans.block(0,0,3,3);


    emit posupdate(Trans);

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
