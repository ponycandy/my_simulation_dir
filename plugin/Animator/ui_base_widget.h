/********************************************************************************
** Form generated from reading UI file 'base_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASE_WIDGET_H
#define UI_BASE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_base_widget
{
public:

    void setupUi(QWidget *base_widget)
    {
        if (base_widget->objectName().isEmpty())
            base_widget->setObjectName(QStringLiteral("base_widget"));
        base_widget->resize(400, 300);

        retranslateUi(base_widget);

        QMetaObject::connectSlotsByName(base_widget);
    } // setupUi

    void retranslateUi(QWidget *base_widget)
    {
        base_widget->setWindowTitle(QApplication::translate("base_widget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class base_widget: public Ui_base_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASE_WIDGET_H
