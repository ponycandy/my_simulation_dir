/********************************************************************************
** Form generated from reading UI file 'testtriggered.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTTRIGGERED_H
#define UI_TESTTRIGGERED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestTriggered
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *TestTriggered)
    {
        if (TestTriggered->objectName().isEmpty())
            TestTriggered->setObjectName(QString::fromUtf8("TestTriggered"));
        TestTriggered->resize(400, 300);
        pushButton = new QPushButton(TestTriggered);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 170, 80, 18));

        retranslateUi(TestTriggered);

        QMetaObject::connectSlotsByName(TestTriggered);
    } // setupUi

    void retranslateUi(QWidget *TestTriggered)
    {
        TestTriggered->setWindowTitle(QCoreApplication::translate("TestTriggered", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("TestTriggered", "ETM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestTriggered: public Ui_TestTriggered {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTTRIGGERED_H
