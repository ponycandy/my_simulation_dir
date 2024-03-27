#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void _Init();//初始化函数声明

private slots:
    void on_open_clicked();

    void on_send_clicked();

    void ReadData();//数据读取

    void on_check_clicked();

private:
    Ui::MainWindow *ui;

    //声明串口
    QSerialPort *m_port;

};
#endif // MAINWINDOW_H
