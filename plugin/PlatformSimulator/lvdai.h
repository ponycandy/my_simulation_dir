#ifndef LVDAI_H
#define LVDAI_H

#include <QObject>
#include "generalplatform.h"
class Lvdai : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit Lvdai(QObject *parent = nullptr);
    /**
     * @brief 反应函数
     *
     * 详细描述构造函数的功能，以及它如何初始化类。
     *
     * @param control 第一控制分量（对应动力控制）。
     * @param statechange 第二控制分量（对应状态的直接转变）。
     * @param reserve 第三控制分量（预留项）。
     * @param time 第四控制分量（环境或者随机变量）。
     */
    FeedBackState StateTransition(const ControlCommand& control,
                                                     const ManipulateState& statechange,
                                                     const EnviromentChange& Env) override;
signals:

};

#endif // LVDAI_H
