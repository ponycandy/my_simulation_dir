#ifndef LVDAIFEEDBACK_H
#define LVDAIFEEDBACK_H

#include <QWidget>

namespace Ui {
class LvdaiFeedBack;
}

class LvdaiFeedBack : public QWidget
{
    Q_OBJECT

public:
    explicit LvdaiFeedBack(QWidget *parent = nullptr);
    ~LvdaiFeedBack();

private:
    Ui::LvdaiFeedBack *ui;
};

#endif // LVDAIFEEDBACK_H
