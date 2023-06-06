#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include <QWidget>

namespace Ui {
class Control_Widget;
}

class Control_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Control_Widget(QWidget *parent = nullptr);
    ~Control_Widget();
 signals:
    void start_solving();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Control_Widget *ui;
};

#endif // CONTROL_WIDGET_H
