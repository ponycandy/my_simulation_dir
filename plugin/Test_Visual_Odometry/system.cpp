#include "system.h"


namespace myslam
{
	System::System(const string& strSettingPath)
	{
		//��ʼ��������ʾ�߳�
		mpViewer = new Viewer(strSettingPath);
		mptViewer = new thread(&Viewer::Run, mpViewer);

		//��ʼ���Ӿ���̼�ָ��
		m_pVO = new myslam::VisualOdometry(strSettingPath, mpViewer);
	}

	cv::Mat System::TrackingRGBD(cv::Mat im, cv::Mat imD, double tframe)
	{
		//��ʼ����
		return m_pVO->Tracking(im, imD, tframe);
	}
}
