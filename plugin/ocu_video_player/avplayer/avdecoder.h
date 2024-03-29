﻿#ifndef AVDECODER_H
#define AVDECODER_H

#include <QThread>
#include <QImage>
#include <QSharedPointer>
#include <defines/VehicleData.h>


class AvDecoder : public QThread
{
    Q_OBJECT
public:
    AvDecoder(QObject *parent = 0);
    ~AvDecoder();
    int play_flag;

public:
    /*解码*/
    void startDecode(const QString &url);
    void stopDecode();

signals:
    void signalDecodeFinished();
    void signalFrameImage(IMAGE_DATA::_IMAGEDATA frameImage);


protected:
    virtual void run() Q_DECL_OVERRIDE;

signals:
    /*已解码的一帧图像（连接信号槽需要跨线程连接Qt::QueuedConnection）*/
    void signalFrameImage(QSharedPointer<QImage> frameImage);

private:
    enum AVDEBUG_TYPE {
        AVDEBUG_INFO = 0,
        AVDEBUG_WARINIG,
        AVDEBUG_ERROR,
    };

private:
    void init();
    void release();

    void decode();

    void debugInfo(const QString &text, AVDEBUG_TYPE type = AVDEBUG_INFO);

private:
    QString m_videoPath;

    bool m_isThreadRunningState;
};

#endif // AVDECODER_H
