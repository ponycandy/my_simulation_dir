#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();
signals:
    void addone();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
