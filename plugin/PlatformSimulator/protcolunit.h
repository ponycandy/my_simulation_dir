#ifndef PROTCOLUNIT_H
#define PROTCOLUNIT_H

#include <QObject>

class ProtcolUnit : public QObject
{
    Q_OBJECT
public:
    explicit ProtcolUnit(QObject *parent = nullptr);
    char data_char;//0
    uint8_t data_8;//1
    uint16_t data_16;//2
    uint32_t data_32;//3
    QVector<char> data_charlist;//4
    uint8_t sizeofcharlist;//补充说明类型4
    QString varname;
    /**
     * @brief 标识这一条字节的类型
     *
     * 详细描述构造函数的功能，以及它如何初始化类。
     *
     * @param param1 参数1的描述。
     * @param param2 参数2的描述。
     */
    int Characteristicnumber;
signals:

};

#endif // PROTCOLUNIT_H
