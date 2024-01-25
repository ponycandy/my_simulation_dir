#include "video_display_widget.h"
#include "ui_video_display_widget.h"
#include <QTimer>
#include <QDebug>
#define RECV_FRAME_IMAGE_TIMEOUT 2000
#define VIDEO_CONTROL_DISPLAY
video_display_widget::video_display_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video_display_widget)
{
    ui->setupUi(this);
    init();
}

video_display_widget::~video_display_widget()
{
    delete ui;
}

void video_display_widget::init()
{
    initModule();
    initUi();
    initConnector();
}

void video_display_widget::initModule()
{
    m_pAvPlayer = new AvPlayer(this);
    m_pRecvFrameImageTimer = new QTimer(this);
    m_pRecvFrameImageTimer->setInterval(RECV_FRAME_IMAGE_TIMEOUT);
}

void video_display_widget::initUi()
{
}

void video_display_widget::initConnector()
{
    qRegisterMetaType<QSharedPointer<QImage>>("QSharedPointer<QImage>");
    qRegisterMetaType<IMAGE_DATA::_IMAGEDATA>("IMAGE_DATA::_IMAGEDATA");

    connect(m_pAvPlayer, SIGNAL(signalFrameImage(IMAGE_DATA::_IMAGEDATA)), this, SLOT(slotOnFrameImageNotify(IMAGE_DATA::_IMAGEDATA)), Qt::QueuedConnection);
    connect(m_pAvPlayer, SIGNAL(signalTryReconnect()), this, SLOT(slotOnTryReconnect()));
    connect(m_pAvPlayer, SIGNAL(signalVideoPlayFinished()), this, SLOT(slotOnVideoPlayFinished()));
    connect(m_pRecvFrameImageTimer, SIGNAL(timeout()), this, SLOT(slotOnRecvFrameImageTimeout()));
}
void video_display_widget::createReconnectFrameImageDisplay()
{
    QSharedPointer<QImage> spImage = QSharedPointer<QImage>(new QImage(":/img/titan.PNG"));
    ui->widget_video->setImage(spImage.data());
    //set the background image of the display window
}


void video_display_widget::slotOnStart()
{
    Q_ASSERT(m_pAvPlayer);
    QString rtmp_path=pathname;
    m_pAvPlayer->play(rtmp_path);
    m_pRecvFrameImageTimer->start();
}

void video_display_widget::slotOnStop()
{
    m_pAvPlayer->stop();
    m_pRecvFrameImageTimer->stop();
    createReconnectFrameImageDisplay();
}

void video_display_widget::slotOnFrameImageNotify(IMAGE_DATA::_IMAGEDATA spFrameImage)
{
    ui->widget_video->setImage(spFrameImage.sp_t_image.data());
}

void video_display_widget::slotOnTryReconnect()
{
    createReconnectFrameImageDisplay();

}

void video_display_widget::slotOnVideoPlayFinished()
{
    createReconnectFrameImageDisplay();
    m_pRecvFrameImageTimer->stop();
}

void video_display_widget::slotOnRecvFrameImageTimeout()
{
    createReconnectFrameImageDisplay();
}

void video_display_widget::on_horizontalSlider_valueChanged(int value)
{
    if(value==1)
    {
        slotOnStart();
    }
    else
    {
        slotOnStop();
    }
}

