#ifndef NODE_H
#define NODE_H



#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QSet>
#include <QStringList>
#include <QDebug>
struct EdgePoint {
    int real_id;
    double jd;
    double wd;
    int Id;
    QString type;
};

// 定义节点类
class Node {

public:
    Node();
    Node(int realId);

    void addPoint(double jd, double wd, int Id, const QString& type, int origFid);

    double avgJd() const;
    double avgWd() const;

    // 获取器
    int realId() const;
    QSet<int> ids() const;
    QSet<QString> types() const;
    QSet<int> origFids() const;

private:
    int m_realId;
    double m_jdSum;
    double m_wdSum;
    int m_count;
    QSet<int> m_ids;
    QSet<QString> m_types;
    QSet<int> m_origFids;
};


#endif // NODE_H
