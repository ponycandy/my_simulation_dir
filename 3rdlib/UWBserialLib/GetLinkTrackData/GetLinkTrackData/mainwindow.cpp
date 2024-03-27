#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QBuffer>


#include "nlink_linktrack_nodeframe0.h"
#include "nlink_linktrack_nodeframe1.h"
#include "nlink_tofsense_frame0.h"
#include "nlink_utils.h"
#include "nlink_linktrack_nodeframe2.h"
#include "nlink_linktrack_anchorframe0.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_Init()
{
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort port;
        port.setPort(info);
        if(port.open(QIODevice::ReadWrite))
        {
            ui->comboBox_port->addItem(port.portName());
            port.close();
        }
    }
    //设置波特率下拉菜单默认显示第0项
    ui->comboBox_baud->setCurrentIndex(0);

    //连接信号槽,用于接收信息
    m_port = new QSerialPort();
    connect(m_port, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void MainWindow::on_open_clicked()
{
    if(ui->open->text() == tr("打开串口"))
    {
        //设置串口名
        m_port->setPortName(ui->comboBox_port->currentText());
        //打开串口
        m_port->open(QIODevice::ReadWrite);
//        设置波特率
        m_port->setBaudRate(ui->comboBox_baud->currentText().toInt());
//        设置数据位
        switch(ui->comboBox_bit->currentText().toInt())
        {
            case 8:
                m_port->setDataBits(QSerialPort::Data8);
                break;
            case 7:
                m_port->setDataBits(QSerialPort::Data7);
                break;
            case 6:
                m_port->setDataBits(QSerialPort::Data6);
                break;
            case 5:
                m_port->setDataBits(QSerialPort::Data5);
                break;
            default:
                break;
        }

//        设置控制流
        m_port->setFlowControl(QSerialPort::NoFlowControl);

//        关闭菜单使能
        ui->comboBox_port->setEnabled(false);
        ui->comboBox_baud->setEnabled(false);
        ui->comboBox_bit->setEnabled(false);
        ui->comboBox_parity->setEnabled(false);
        ui->comboBox_stop->setEnabled(false);

        ui->open->setText(tr("关闭串口"));

    }
    else
    {
//        关闭串口
        m_port->clear();
        m_port->close();
//        m_port->deleteLater(); //这句是删除串口

//        恢复菜单使能
        ui->comboBox_port->setEnabled(true);
        ui->comboBox_baud->setEnabled(true);
        ui->comboBox_bit->setEnabled(true);
        ui->comboBox_parity->setEnabled(true);
        ui->comboBox_stop->setEnabled(true);

        ui->open->setText(tr("打开串口"));

    }
}


void MainWindow::on_send_clicked()
{
    m_port->write(ui->lineEdit_send->text().toUtf8());
}

void MainWindow::ReadData()
{
    /******************此处尽量不要放过多的函数处理，否则影响数据接收******************/
    QByteArray arr;
    static QByteArray buffer;

    arr = m_port->readAll();
    static bool flag = false;

    //判断是不是55开头的数据，如果是的话，就存起来，然后设置flag位true，下次就接收另外一组数据
    if(arr.toHex().startsWith("55"))
    {
        buffer.append(arr); //存储第一组数据
        flag = true;
        return;
    }
    //操了，还要校验尾数据
    if(flag && arr.toHex().endsWith("ee")!=0)
    {
        buffer.append(arr);
    }

    if(arr.toHex().endsWith("ee") && flag)
    {

        buffer.append(arr); //存储第二组数据，不一定够，还得补！
        char *string1 = buffer.toHex().data();

        uint8_t data[1024];
        size_t data_length;
        data_length = NLink_StringToHex(string1, data);  //将字符串转换为Hex格式，并将数据存储在data中
        qDebug()<<"data_length: "<<data_length;
        data_length=896;
        if (nlt_anchorframe0_.UnpackData(data, data_length))
        {
          nlt_anchorframe0_result_t *result = &nlt_anchorframe0_.result;
          qDebug()<<"LinkTrack NodeFrame0 data unpack successfully:n";

    //      和上位机对比，数据是正确的
          qDebug()<< "位置：" <<result->nodes[0]->pos_3d[0] <<result->nodes[0]->pos_3d[1]<<result->nodes[0]->pos_3d[2];
          // qDebug()<< "速度：" <<result->nodes[0] <<result->vel_3d[1] <<result->vel_3d[2];
          // qDebug()<< "加速度：" <<result->imu_acc_3d[0] <<result->imu_acc_3d[1] <<result->imu_acc_3d[2];

          ui->textEdit_get->clear();
          QString str1, str2, str3;

          str1 ="位置：" + QString::number(result->nodes[0]->pos_3d[0]) + " " + QString::number(result->nodes[0]->pos_3d[1]) + " " + QString::number(result->nodes[0]->pos_3d[2]);
          // str2 ="速度：" + QString::number(result->vel_3d[0]) + " " + QString::number(result->vel_3d[1]) + " " + QString::number(result->vel_3d[2]);
          // str3 ="加速度：" + QString::number(result->imu_acc_3d[0]) + " " + QString::number(result->imu_acc_3d[1]) + " " + QString::number(result->imu_acc_3d[2]);

          ui->textEdit_get->append(str1);
          ui->textEdit_get->append(str2);
          ui->textEdit_get->append(str3);

         }

        buffer.clear();//因为buffer是静态变量，用完一次后要记得清空，否则会使得内存溢出
        flag=false;
    }

}


void MainWindow::on_check_clicked()
{

    ui->comboBox_port->clear();

    _Init();
}

