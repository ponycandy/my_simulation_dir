/********************************************************************************
** Form generated from reading UI file 'simulatorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATORWIDGET_H
#define UI_SIMULATORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simulatorWidget
{
public:

    void setupUi(QWidget *simulatorWidget)
    {
        if (simulatorWidget->objectName().isEmpty())
            simulatorWidget->setObjectName(QStringLiteral("simulatorWidget"));
        simulatorWidget->resize(692, 496);

        retranslateUi(simulatorWidget);

        QMetaObject::connectSlotsByName(simulatorWidget);
    } // setupUi

    void retranslateUi(QWidget *simulatorWidget)
    {
        simulatorWidget->setWindowTitle(QApplication::translate("simulatorWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class simulatorWidget: public Ui_simulatorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATORWIDGET_H
