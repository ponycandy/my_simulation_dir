#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QWidget>
#include <QVector>
#include <include/FILE_manage/f_manager.h>
#include <QTimer>


namespace Ui {
class Cameracontroller;
}

class Cameracontroller : public QWidget
{
    Q_OBJECT

public:
    explicit Cameracontroller(QWidget *parent = nullptr);
    ~Cameracontroller();
    QVector<int> cameraIDlists;
    QString directory_name;
    int framerate;
    int width;
    int height;
    int cameranum;
    QTimer *timer;

private slots:
    void on_pushButton_clicked();
    void CameraCapture();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::Cameracontroller *ui;
};

#endif // CAMERACONTROLLER_H
