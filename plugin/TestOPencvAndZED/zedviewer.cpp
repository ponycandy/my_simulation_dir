#include "zedviewer.h"
#include "TestOPencvAndZEDActivator.h"
#include "opencv2/opencv.hpp""
ZEDviewer::ZEDviewer()
{
//             m_painter=new cubedrawer;
    //    cloudpainter=new PointClouddrawer;
    m_cuda=new TestCuda;
    m_anim=TestOPencvAndZEDActivator::getService<Animateservice3Dservice>("Animateservice3Dservice");
//              m_anim->register_painter(m_painter);
    //    m_anim->register_painter(cloudpainter);
    m_anim->register_painter(m_cuda);
    Mwidget=m_anim->getwidget();
    Mwidget->show();
    m_anim->start_animate();
    //试一试简单的照片显示
    //    sl::Camera zed;

    //    // Open the camera
    //    sl::ERROR_CODE returned_state = zed.open();
    //    if (returned_state != sl::ERROR_CODE::SUCCESS)
    //    {
    //        std::cout << "Error " << returned_state << ", exit program.\n";
    //        return ;
    //    }
    //    sl::Mat image_zed(1280,720, sl::MAT_TYPE::U8_C4);
     //   cv::Mat image_ocv = slMat2cvMat(image_zed);


    //    if (zed.grab() == sl::ERROR_CODE::SUCCESS)
    //    {
    //        // Retrieve the left image in sl::Mat
    //        // The cv::Mat is automatically updated
    //        zed.retrieveImage(image_zed, sl::VIEW::LEFT);
    //        // Create an OpenCV Mat that shares sl::Mat data

    //        // Display the left image from the cv::Mat object

    //        cv::imshow("Image", image_ocv);
    //    }
    //图像能够显示出来，说明数据获取没有问题
}
