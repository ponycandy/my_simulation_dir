#include "trtui.h"
#include "ui_trtui.h"
#include "include/FILE_manage/f_manager.h"
trtUI::trtUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trtUI)
{
    ui->setupUi(this);
    onnx="  --onnx=";
    file_saved="  --saveEngine=";
    option_num=0;
    init();
}

trtUI::~trtUI()
{
    delete ui;
}

void trtUI::init()
{
    QString str1=f_Read_TXT("./config/config_onnx.txt");
    qDebug()<<str1;
    ui->lineEdit_2->setText(str1);
    onnx="  --onnx="+str1;

    QString str2=f_Read_TXT("./config/config_trexec.txt");
    qDebug()<<str2;
    ui->lineEdit->setText(str2);
    trtexec=str2;

    QString str3=f_Read_TXT("./config/config_generate_path.txt");
    qDebug()<<str3;
    generated_dir=str3;
}


void trtUI::on_pushButton_clicked()
{
    trtexec=f_FileOpen();
    ui->lineEdit->setText(trtexec);
    f_Write_TXT("./config/config_trexec.txt",trtexec);
}

void trtUI::on_pushButton_2_clicked()
{
    QString in_onnx=f_FileOpen();
    onnx="  --onnx="+in_onnx;
    ui->lineEdit_2->setText(in_onnx);
    f_Write_TXT("./config/config_onnx.txt",in_onnx);
}

void trtUI::on_pushButton_3_clicked()
{
    QString in_file_saved=f_Filesavas();
    file_saved="  --saveEngine="+in_file_saved;

    ui->lineEdit_3->setText(in_file_saved);

}

void trtUI::on_pushButton_4_clicked()
{
    QString command;
    command=trtexec+onnx+file_saved;

    QMap<int, QString>::const_iterator iter= options.cbegin();
    while (iter != options.cend())
    {
        command.append(iter.value());
        ++iter;
    }
    qDebug()<<command;
    QString text;
    std::system(command.toLatin1().data());
}

void trtUI::on_checkBox_clicked()
{
    QString workspace;
    workspace="  --workspace=";
    workspace.append(ui->lineEdit_4->text());
    option_num++;
    options.insert(option_num,workspace);
    //以下插其它的选项
}
