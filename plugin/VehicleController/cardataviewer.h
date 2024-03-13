#ifndef CARDATAVIEWER_H
#define CARDATAVIEWER_H

#include <QWidget>
#include "videoplayer.h"
#include "service/VideoCoreservice.h"
#include <QMap>
#include "qcombobox.h"
#include "QGridLayout"

struct widgetinfos
{
    int x;
    int y;
    QFrame* wid;
};

class CardataViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CardataViewer(QWidget *parent = nullptr);
    ~CardataViewer();
    void clearcombox();
    void display_combox();
    void Addwidget(QWidget *windows,QString vehicle,QString windowname);
    void changeTowidget(QString vehicle,QString windowname);
    void switchview();
    QMap<int,QString> order_2_namemap;
    QMap<QString,int> combox_map_view_genre;
    QVector<widgetinfos> all_overlays;
    QMap<QString,QWidget*> two_2_1map;//第一输入为车辆名称，第二输入为窗口类型.
    QMap<QString,int > temp_1;//第一输入为车辆名称，第二输入为窗口类型.
    QMap<QString,int > temp_2;//第一输入为车辆名称，第二输入为窗口类型.
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    VideoCoreservice *vid;
    QWidget *nullwidget;
    QGridLayout *gridLayout;
    videoplayer *m_video;
    QFrame *comboxframe;
    bool combox_state=false;

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);
};

#endif // CARDATAVIEWER_H
