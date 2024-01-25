#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "service/VideoCoreservice.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    VideoCoreservice *m_service;

private:
    Ui::Form *ui;
};

#endif // FORM_H
