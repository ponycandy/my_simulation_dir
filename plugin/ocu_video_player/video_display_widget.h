#ifndef VIDEO_DISPLAY_WIDGET_H
#define VIDEO_DISPLAY_WIDGET_H

#include <QWidget>
#include <avplayer/avplayer.h>
namespace Ui {
class video_display_widget;
}

class video_display_widget : public QWidget
{
    Q_OBJECT

public:
    explicit video_display_widget(QWidget *parent = nullptr);
    ~video_display_widget();
    void setConnectFrameImageDisplay(int vehicleType);

    void setReconnectFrameImageDisplay(int vehicleType);


    void setReconnectFrameImageDisplay();


    QString pathname;
    AvPlayer *m_pAvPlayer;
private:

    void init();
    void initModule();
    void initUi();
    void initConnector();
    void release();
    void releaseModule();
    void releaseConnector();
    void createDefaultFrameImageDisplay();
    void createReconnectFrameImageDisplay();


private slots:


    void slotOnStart();
    void slotOnStop();
    void slotOnFrameImageNotify(IMAGE_DATA::_IMAGEDATA spFrameImage);
    void slotOnTryReconnect();
    void slotOnVideoPlayFinished();
    void slotOnRecvFrameImageTimeout();

    void on_horizontalSlider_valueChanged(int value);

private:



    QTimer *m_pRecvFrameImageTimer;
    QString m_rtpSdpPath;
    bool  m_isOverlay;
    int   m_SpinboxValue;
    double m_DoubleSpinBox;

private:
    Ui::video_display_widget *ui;
};

#endif // VIDEO_DISPLAY_WIDGET_H
