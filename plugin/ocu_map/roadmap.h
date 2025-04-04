#ifndef ROADMAP_H
#define ROADMAP_H

#include <QObject>
#include <node.h>
#include <QTextStream>
class roadmap : public QObject
{
    Q_OBJECT
public:
    explicit roadmap(QObject *parent = nullptr);
    void read_roadmap(QString filename);
    QHash<int, Node> nodes;
    QHash<int, QList<EdgePoint>> edges;
signals:


};

#endif // ROADMAP_H
