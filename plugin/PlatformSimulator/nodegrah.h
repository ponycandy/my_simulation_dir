#ifndef NODEGRAH_H
#define NODEGRAH_H

#include <QObject>

/**
     * @brief 节点表
     *
     * 这个类的目的是判断当前系统中缺失的节点，每个节点是否下线（仿真节点介入）
     * 下线之后，需要取代节点的所有出点和入点
     * 如果重新上线，则需要推出节点
     * 这个东西无法部署在201的计算机上，因为DDS框架不允许动态的话题注册
     * 所以只能是仿真
     */
struct singlenode
{
    QString nodename;
    QString out;
    QString in;
    //分布式话题通讯，每个节点只需要模拟一个输入和一个输出就行
    //不需要模拟边的情况
};
class nodegrah : public QObject
{
    Q_OBJECT
public:
    explicit nodegrah(QObject *parent = nullptr);
    /**
     * @brief 当前节点状态
     */
    QVector<singlenode> current_graph;
    /**
     * @brief 理想节点状态
     */
    QVector<singlenode> Target_graph;
signals:

};

#endif // NODEGRAH_H
