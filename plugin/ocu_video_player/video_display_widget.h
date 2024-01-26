#ifndef VIDEO_DISPLAY_WIDGET_H
#define VIDEO_DISPLAY_WIDGET_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class video_display_widget;
}

class video_display_widget : public QWidget
{
    Q_OBJECT

public:
    explicit video_display_widget(QWidget *parent = nullptr);
    ~video_display_widget();


    QString pathname;
    int mode;
private:

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.fillRect(rect(), Qt::transparent);
    }


private slots:


    void slotOnStart();
    void slotOnStop();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::video_display_widget *ui;
};

#endif // VIDEO_DISPLAY_WIDGET_H
