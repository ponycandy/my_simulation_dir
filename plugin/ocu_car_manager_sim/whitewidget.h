#ifndef WHITEWIDGET_H
#define WHITEWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
namespace Ui {
class whitewidget;
}

class whitewidget : public QWidget
{
    Q_OBJECT

public:
    explicit whitewidget(QWidget *parent = nullptr);
    ~whitewidget();
    QFrame *frame;
    QPushButton *button;
private:
    Ui::whitewidget *ui;
};

#endif // WHITEWIDGET_H
