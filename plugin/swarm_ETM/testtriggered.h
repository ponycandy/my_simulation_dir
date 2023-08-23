#ifndef TESTTRIGGERED_H
#define TESTTRIGGERED_H

#include <QWidget>

namespace Ui {
class TestTriggered;
}

class TestTriggered : public QWidget
{
    Q_OBJECT

public:
    explicit TestTriggered(QWidget *parent = nullptr);
    ~TestTriggered();
signals:
    void trigeronce();
private slots:
    void on_pushButton_clicked();

private:
    Ui::TestTriggered *ui;
};

#endif // TESTTRIGGERED_H
