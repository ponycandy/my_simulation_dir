#ifndef CROSSAXLE_H
#define CROSSAXLE_H

#include <QWidget>
#include <qpainter.h>
class crossaxle : public QWidget
{
    Q_OBJECT
public:
    explicit crossaxle(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;

signals:
};

#endif // CROSSAXLE_H
