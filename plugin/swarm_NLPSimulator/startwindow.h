#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>

namespace Ui {
class startwindow;
}

class startwindow : public QWidget
{
    Q_OBJECT

public:
    explicit startwindow(QWidget *parent = nullptr);
    ~startwindow();

private slots:
    void on_pushButton_clicked();
signals:
    void sigstart();
private:
    Ui::startwindow *ui;
};

#endif // STARTWINDOW_H
