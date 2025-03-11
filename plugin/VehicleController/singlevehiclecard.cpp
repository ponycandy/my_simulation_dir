#include "singlevehiclecard.h"
#include <VehicleControllerActivator.h>
//#include <remote.pb.h>
SingleVehicleCard::SingleVehicleCard(QObject *parent)
    : QObject{parent}
{
}

void SingleVehicleCard::setupconnection()
{
    initialization();
     m_timer_1=startTimer(100);
}

void SingleVehicleCard::readJoystickData()
{
    //在这里填写读取摇杆的逻辑
#ifdef linux
    struct input_event ev;

    ssize_t bytes = read(joystick_fd_, &ev, sizeof(ev));
    if (bytes == -1) {
        std::cerr << "Failed to read joystick data" << std::endl;
        return;
    }

    if (ev.type == EV_ABS) {
        if (ev.code == ABS_Y) { // 油门轴
            joystick_data_.throttle = static_cast<double>(ev.value) / 32767.0; // 归一化到 [-1, 1]
        } else if (ev.code == ABS_X) { // 转向轴
            joystick_data_.steering = static_cast<double>(ev.value) / 32767.0; // 归一化到 [-1, 1]
        }
    }
#endif
}

void SingleVehicleCard::WriteControlInfo()
{
#ifdef linux
    // 清空之前的消息
    msg_send_.Clear();

    // 设置消息类型为远程驾驶
    msg_send_.set_msg_type_(remote::v2xclient::proto::RemoteDrv);

    // 填充 CarInfo 信息
    auto* car_info = msg_send_.mutable_carinfo_();
    car_info->set_ip(host_S.toStdstring());
    car_info->set_id(1);
    car_info->set_name("Car1");



    // 填充 AutoDrvCmd 信息
    auto* auto_drv_cmd = msg_send_.mutable_autodrvcmd_();

    // 填充 AutoDrvCmd1 信息
    auto* auto_drv_cmd1 = auto_drv_cmd->mutable_autodrvcmd1_();
    auto_drv_cmd1->set_automodeact(1); // 自动驾驶模式
    auto_drv_cmd1->set_reqaccpdl(joystick_data_.throttle); // 期望油门开度
    auto_drv_cmd1->set_autogearcmd(2); // 档位控制指令
    auto_drv_cmd1->set_autoprkact(0); // 驻车请求
    auto_drv_cmd1->set_autoprkmodecmd(0); // 驻车模式

    // 填充 AutoDrvCmd2 信息
    auto* auto_drv_cmd2 = auto_drv_cmd->mutable_autodrvcmd2_();
    auto_drv_cmd2->set_reqbrkpdl(0.3); // 期望制动踏板开度
    auto_drv_cmd2->set_reqstrangle(joystick_data_.steering * 90.0); // 期望转向角度（映射到 [-90, 90]）
    auto_drv_cmd2->set_reqstranglespd(10.0); // 期望转向角速度

    // 填充 AutoDrvCmd3 信息
    auto* auto_drv_cmd3 = auto_drv_cmd->mutable_autodrvcmd3_();
    auto_drv_cmd3->set_emgstop(0); // 紧急停止
    auto_drv_cmd3->set_beep(1); // 鸣笛
    auto_drv_cmd3->set_evmode(0); // EV 模式
    auto_drv_cmd3->set_combatmode(0); // 战斗模式
    auto_drv_cmd3->set_leftturn(0); // 左转灯
    auto_drv_cmd3->set_rightturn(0); // 右转灯

    // 填充 Target_Pos 信息（可选）
    auto* target_pos = msg_send_.mutable_target_pos_();
    auto* position = target_pos->add_trajectory();
    position->set_latitude(39.9042); // 纬度
    position->set_longitude(116.4074); // 经度
    position->set_altitude(50.0); // 海拔

    // 填充 fm_target_info 信息（可选）
    auto* fm_target_info = msg_send_.mutable_fm_target_info_();
    fm_target_info->set_time_(time(nullptr)); // 时间戳
    fm_target_info->set_target_name("Leader"); // 目标名称
    fm_target_info->set_follow_distance_(10.0); // 跟车距离
    fm_target_info->set_formation_state_(1); // 编队状态
#endif
}

void SingleVehicleCard::sendControlMessage()
{
#ifdef linux
    std::string serialized_msg;
    if (!msg_send_.SerializeToString(&serialized_msg)) {
        std::cerr << "Failed to serialize control message" << std::endl;
        return;
    }
    send(QByteArray::fromStdString(serialized_msg),"none");
#endif
}

void SingleVehicleCard::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==m_timer_1 && connection_status==true)
    {
        // 0. 获取摇杆数据
        readJoystickData();
        // 1. 读取控制信息
        WriteControlInfo();

        // 2. 下发控制指令
        sendControlMessage();


    }
}


void SingleVehicleCard::initialization()
{
    client=VehicleControllerActivator::getService<UDPmessageservice>("UDPmessageservice");
    client=client->cloneservice();
    setNet(client,port_S,host_S);
    client->subscribe_callback(this,SLOT(onReceived(QByteArray)));
}

void SingleVehicleCard::setNet(UDPmessageservice *client, QString port, QString host)
{
    //do nothing
    adr.setAddress(host_S);
}


void SingleVehicleCard::send(QByteArray data, QString topic_name)
{

    client->send(data,adr,port_S.toUInt());
}

void SingleVehicleCard::disconnect()
{
    client->disconnectfromhost();
    connection_status=false;
}

void SingleVehicleCard::connectall()
{
    client->init(port_S.toUInt(),host_S);
    connection_status=true;
}

void SingleVehicleCard::onConnected()
{

}

void SingleVehicleCard::onReceived(const QByteArray &message)
{
#ifdef linux
    // 解析 protobuf 消息
    if (!msg_receive_.ParseFromString(message.toStdString())) {
        std::cerr << "Failed to parse vehicle status" << std::endl;
    }


    // 将解析后的数值赋给车辆状态结构体
    if (msg_receive_.has_chassissts_()) {
        const auto& chassis_sts = msg_receive_.chassissts_();
        // chassis_state_.throttle = chassis_sts.driveraccpdl(); // 油门值
        // chassis_state_.steering = chassis_sts.wheelangle(); // 转向值
        // chassis_state_.veh_spd = chassis_sts.vehspd(); // 车速
        // chassis_state_.battery_soc = chassis_sts.batterysoc(); // 电池电量
        // chassis_state_.wheel_angle = chassis_sts.wheelangle(); // 方向盘角度
    }
#endif
}

