#ifndef EVENTEDITER_H
#define EVENTEDITER_H

#include <QWidget>
#include <QPushButton>
#include <QtWidgets/QTableWidget>
#include <QComboBox>
#include <QLineEdit>
class EventEditer : public QWidget
{
    Q_OBJECT
public:
    explicit EventEditer(QWidget *parent = nullptr);
    /**
     * @brief 添加可以选择的信号槽，在这里拓展其它的事件
     * @param
     * @return
     */
    void init_signal_and_slot();
    QPushButton *addevent;
    QLineEdit *extraparameter_input;
    QPushButton *saveevent;
    QPushButton *deleteevent;
    QPushButton *input_label;

    QTableWidget *tableWidget;
    QComboBox *select_signal;
    QComboBox *select_slot;

signals:
public slots:
    /**
     * @brief 添加事件项目
     * @param
     * @return
     */
    void OnAddItem();
};

#endif // EVENTEDITER_H
