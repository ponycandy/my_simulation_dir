#include "roadmap.h"

roadmap::roadmap(QObject *parent) : QObject(parent)
{

}

void roadmap::read_roadmap(QString filename)
{
    QHash<int, int> realIdCount;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "can't open "<<file.fileName();
        return ;
    }

    QTextStream in(&file);
    //        in.setEncoding(QStringConverter::Utf8);
    in.readLine();

    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(',');
        if (fields.size() < 7) continue;

        bool ok;
        int realId = fields[6].toInt(&ok);
        if (ok) realIdCount[realId]++;
    }
    file.close();


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "can't open "<<file.fileName();
        return ;
    }
    QTextStream in_2(&file);
    in_2.readLine();
    while (!in_2.atEnd()) {
        QStringList fields = in_2.readLine().split(',');
        if (fields.size() < 7) continue;

        int realId = fields[6].toInt();
        int Id = fields[1].toInt();
        QString type = fields[2];
        int origFid = fields[3].toInt();
        double jd = fields[4].toDouble();
        double wd = fields[5].toDouble();

        // 处理节点（real_id出现2次及以上）
        if (realIdCount.value(realId, 0) >= 2) {
            if (!nodes.contains(realId)) {
                nodes.insert(realId, Node(realId));
            }
            nodes[realId].addPoint(jd, wd, Id, type, origFid);
        }

        // 处理边（无论real_id出现次数）
        EdgePoint point{realId, jd, wd, Id, type};
        edges[origFid].append(point);
    }
    file.close();

}







