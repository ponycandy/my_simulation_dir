#ifndef GENERALPLATFORM_H
#define GENERALPLATFORM_H

#include <QVector>
#include <protcolunit.h>
#include <controlcommand.h>
#include <feedbackstate.h>
#include <manipulatestate.h>
#include <enviromentchange.h>
/**
     * @brief 节点通用构造函数
     * 对于每一个节点来说feedback=f(t,control)
     *  改变节点状态有两种，一种是control，一种是t(随机或者环境因素)
     * 还有一种情况，直接更改feedback
     * 将直接对feedback的修改视作为control即可以了，将车辆设定为一个按照固定时间反馈的对象
     */
class GeneralPlatform
{
public:
    /**
     * @brief 构造函数。
     *
     */
    GeneralPlatform();
    /**
     * @brief 实物和仿真模块检测接口。
     *
     * 当检测到外部接口切换时，主动开启或者关闭本模块的输出
     *其实现应该是公有的
     * @param param1 接口当前状态。
     * @param param2 接口名称。
     */
    void PhysicalSimulationInterfaces();
    /**
     * @brief 反应函数
     *
     * 详细描述构造函数的功能，以及它如何初始化类。
     *
     * @param control 第一控制分量（对应动力控制）。
     * @param statechange 第二控制分量（对应状态的直接转变）。
     * @param time 第三控制分量（环境或者随机变量）。
     */
    virtual FeedBackState StateTransition(const ControlCommand& control,
                                                 const ManipulateState& statechange,
                                                 const EnviromentChange& Env);
    /**
     * @brief 广播反馈状态。
     * 这个函数同时完成内部广播（从平台到显示界面,到态势图）
     * 和外部传播（从平台到UDP给到外面）
     */
    virtual void broadcast(const FeedBackState& state);
    /**
     * @brief 反馈接口
     */
    QVector<ProtcolUnit> FeedBack;
    /**
     * @brief 控制接口
     */
    QVector<ProtcolUnit> controlport;
    /**
     * @brief 类型标识
     *
     * 0=车辆类 1=无人机类 2=上装类
     */
    int genID;
};

#endif // GENERALPLATFORM_H
