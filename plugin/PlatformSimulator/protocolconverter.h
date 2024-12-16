#ifndef PROTOCOLCONVERTER_H
#define PROTOCOLCONVERTER_H

#include <QObject>
/**
     * @brief 协议转接模块
     *
     * 展开多个UDP接口接受DDS转UDP数据
     */
class protocolconverter : public QObject
{
    Q_OBJECT
public:
    explicit protocolconverter(QObject *parent = nullptr);

signals:

};

#endif // PROTOCOLCONVERTER_H
