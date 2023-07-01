#ifndef GRAPHING_H
#define GRAPHING_H

#include <QObject>
#include <service/Animateservice.h>
#include <PolyParams.h>
#include <visualize.h>
#include "QWidget"
class graphing : public QObject
{
    Q_OBJECT
public:
    explicit graphing(QObject *parent = nullptr);
    Animateservice *m_service;
    visualize *m_visual;
    QWidget *m_widget;


signals:

};

#endif // GRAPHING_H
