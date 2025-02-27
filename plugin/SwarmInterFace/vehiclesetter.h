#ifndef VEHICLESETTER_H
#define VEHICLESETTER_H

#include <QWidget>

namespace Ui {
class vehiclesetter;
}

class vehiclesetter : public QWidget
{
    Q_OBJECT

public:
    explicit vehiclesetter(QWidget *parent = nullptr);
    ~vehiclesetter();

private:
    Ui::vehiclesetter *ui;
};

#endif // VEHICLESETTER_H
