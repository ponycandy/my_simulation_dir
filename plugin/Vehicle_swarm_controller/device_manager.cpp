#include "device_manager.h"
#include "Vehicle_swarm_controllerActivator.h"
#include "OSGIEVENT.h"
Device_manager::Device_manager(QWidget *parent)
{
    vehiclenum=3;
    setupsensor();
    setupcontroller();
    setupconnection();
}

Device_manager::~Device_manager()
{
    delete this;
}

void Device_manager::setupsensor()
{
    vehiclenum=1;


    serialPort=new QSerialPort;

    serialPort->setPortName("COM4");

    serialPort->setBaudRate(921600);

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()),Qt::DirectConnection);
    connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this, SLOT(handleError(QSerialPort::SerialPortError)));

    if (!serialPort->open(QIODevice::ReadOnly))
    {
    }
    results=new nlt_anchorframe0_t;

}

void Device_manager::setupcontroller()
{

}

void Device_manager::setupconnection()
{

    Vehicle_swarm_controllerActivator::publishsignal(this,SIGNAL(sig_UWB(int, float, float, float, float)),OSGIEVENT::UWB_AGENT_STATE_UPDATE,Qt::QueuedConnection);

}

void Device_manager::UWB_datacallback(const std::string &data)
{
    // jetson::UWBdata uwb=gpcs::struct_load<jetson::UWBdata>(data);
    // qDebug()<<uwb.ID<<" "<<uwb.head_x_pos<<" "<<uwb.tail_x_pos;
    // emit sig_UWB(uwb);
}



void Device_manager::processData()
{
    int FRAME_SIZE=896;
    while (buffer.size() >= FRAME_SIZE)
    {
        QByteArray frame = buffer.left(FRAME_SIZE); // Use 'left' to get the first FRAME_SIZE bytes

        const unsigned  char *data_input= reinterpret_cast<unsigned char *>(frame.data());
        if (UnpackData_nlt_anchorframe0(data_input,FRAME_SIZE,results))
        {
            if(results->result.valid_node_count>0)
            {
                // QElapsedTimer et;
                // et.start();

                for(int i=0;i<results->result.valid_node_count/2;i++)
                {
                    jetson::UWBdata data;
                    data.ID=results->result.nodes[2*i]->id/2;//这里要修改，多车ID不一定对！
                    // results->result.nodes[0]->id
                    data.head_x_pos=results->result.nodes[2*i]->pos_3d[1];//xy反转，注意UWB坐标系是z轴向下的！
                    data.head_y_pos=results->result.nodes[2*i]->pos_3d[0];
                    data.tail_x_pos=results->result.nodes[2*i+1]->pos_3d[1];
                    data.tail_y_pos=results->result.nodes[2*i+1]->pos_3d[0];
                    emit sig_UWB(data.ID,data.head_x_pos,data.head_y_pos,data.tail_x_pos,data.tail_y_pos);
                    // publishers[i]->publish(data);
                    // qDebug()<<"ID:"<<data.ID<< " "<<data.head_x_pos;
                }

            }

            // qDebug()<<"Tag Frame0 data unpack successfully:"<<counter++;
        }
        else
        {
            // qDebug()<<"failed to unpack"<<" datalength :"<<FRAME_SIZE;
        }
        buffer.clear();
    }
}

void Device_manager::handleReadyRead()
{
    int FRAME_SIZE=896;
    QByteArray data = serialPort->readAll();
    bool istrue=serialPort->clear();
    // qDebug()<<istrue;
    if(data.toHex().startsWith("55"))
    {
        buffer.append(data); //存储第一组数据
        is_start_pos_flag = true;
        return;
    }
    if(is_start_pos_flag==true)
    {
        buffer.append(data);
    }
    if(buffer.size() >= FRAME_SIZE && is_start_pos_flag==true)
    {
        processData();
        buffer.clear();
        is_start_pos_flag=false;
    }
}

void Device_manager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ReadError)
    {
        // Handle read error

    }
}

void Device_manager::spinonce()
{
}

void Device_manager::initall()
{

}
