#ifndef TRTMANAGER_H
#define TRTMANAGER_H

#include <QObject>
#include <trtui.h>
class trtmanager : public QObject
{
    Q_OBJECT
public:
    explicit trtmanager(QObject *parent = nullptr);
    trtUI *m_ui;

signals:

};

#endif // TRTMANAGER_H
