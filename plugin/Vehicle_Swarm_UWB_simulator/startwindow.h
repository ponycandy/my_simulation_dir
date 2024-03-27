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
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    void sigstart();
    void sigstop();
    void sigspin();
    void sig_choose_bool(bool choosenow);

private:
    Ui::startwindow *ui;
};

#endif // STARTWINDOW_H
