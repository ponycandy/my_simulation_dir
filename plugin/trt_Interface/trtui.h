#ifndef TRTUI_H
#define TRTUI_H

#include <QWidget>
#include <QMap>
namespace Ui {
class trtUI;
}

class trtUI : public QWidget
{
    Q_OBJECT

public:
    explicit trtUI(QWidget *parent = nullptr);
    ~trtUI();
    void init();
    QString trtexec;
        QString onnx;
        QString onnx_path;

        QString file_saved;
        QString file_saved_path;

        QString command;
        QString command_path;

        QString generated_dir;

        int option_num;
        QMap<int,QString> options;
private slots:

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_clicked();

private:
    Ui::trtUI *ui;
};

#endif // TRTUI_H
