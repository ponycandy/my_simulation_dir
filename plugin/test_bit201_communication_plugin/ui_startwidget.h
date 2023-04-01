/********************************************************************************
** Form generated from reading UI file 'startwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWIDGET_H
#define UI_STARTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startwidget
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *startwidget)
    {
        if (startwidget->objectName().isEmpty())
            startwidget->setObjectName(QStringLiteral("startwidget"));
        startwidget->resize(400, 300);
        pushButton = new QPushButton(startwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 130, 93, 28));

        retranslateUi(startwidget);

        QMetaObject::connectSlotsByName(startwidget);
    } // setupUi

    void retranslateUi(QWidget *startwidget)
    {
        startwidget->setWindowTitle(QApplication::translate("startwidget", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("startwidget", "send_start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class startwidget: public Ui_startwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWIDGET_H
