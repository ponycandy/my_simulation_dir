#ifndef CARDATAVIEWER_H
#define CARDATAVIEWER_H

#include <QWidget>
#include "videoplayer.h"
#include "service/VideoCoreservice.h"
namespace Ui {
class CardataViewer;
}

class CardataViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CardataViewer(QWidget *parent = nullptr);
    ~CardataViewer();
    void clearcombox();
    void Addwidget(QWidget *windows,QString vehicle,QString windowname);
    void changeTowidget(QString vehicle,QString windowname);
    void switchview();
    QMap<int,QString> order_2_namemap;
    QMap<QString,int> combox_map_view_genre;

    QMap<QString,QMap<QString,QWidget*>> two_2_1map;//第一输入为车辆名称，第二输入为窗口类型.
    VideoCoreservice *vid;
    QWidget *nullwidget;
    videoplayer *m_video;

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::CardataViewer *ui;
};

#endif // CARDATAVIEWER_H
