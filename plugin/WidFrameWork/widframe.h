#ifndef WIDFRAME_H
#define WIDFRAME_H

#include <QMainWindow>
#include "service/Widframeopservice.h"
#include "QVBoxLayout"
#include <QMap>
namespace Ui {
class WidFrame;
}

class WidFrame : public QMainWindow,Widframeopservice
{
    Q_OBJECT

public:
    explicit WidFrame(QWidget *parent = nullptr);
    ~WidFrame();
    void Add_Menu(QMenuBar* menu,QString menuname) override;
    void remove_Menu(QString Menuname) override;
private:
    Ui::WidFrame *ui;
    QVBoxLayout *Menu_layout ;
    QVBoxLayout *over_all_layout;
    QMap<QString,QMenuBar*> menuist;
public slots:
    void closeAll();
};

#endif // WIDFRAME_H
