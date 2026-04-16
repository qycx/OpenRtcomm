/********************************************************************************
** Form generated from reading UI file 'WinSystemRule.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSYSTEMRULE_H
#define UI_WINSYSTEMRULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSystemRule
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *labcp;
    QLabel *labver;

    void setupUi(QWidget *WinSystemRule)
    {
        if (WinSystemRule->objectName().isEmpty())
            WinSystemRule->setObjectName("WinSystemRule");
        WinSystemRule->resize(350, 120);
        WinSystemRule->setMinimumSize(QSize(0, 120));
        WinSystemRule->setMaximumSize(QSize(16777215, 120));
        horizontalLayout = new QHBoxLayout(WinSystemRule);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(WinSystemRule);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        widget_6 = new QWidget(widget);
        widget_6->setObjectName("widget_6");
        verticalLayout_2 = new QVBoxLayout(widget_6);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labcp = new QLabel(widget_6);
        labcp->setObjectName("labcp");
        labcp->setMaximumSize(QSize(16777215, 50));
        labcp->setStyleSheet(QString::fromUtf8("font-size:20px;"));

        verticalLayout_2->addWidget(labcp);

        labver = new QLabel(widget_6);
        labver->setObjectName("labver");
        labver->setMaximumSize(QSize(16777215, 50));
        labver->setStyleSheet(QString::fromUtf8("font-size:20px"));

        verticalLayout_2->addWidget(labver);


        verticalLayout->addWidget(widget_6);


        horizontalLayout->addWidget(widget);


        retranslateUi(WinSystemRule);

        QMetaObject::connectSlotsByName(WinSystemRule);
    } // setupUi

    void retranslateUi(QWidget *WinSystemRule)
    {
        WinSystemRule->setWindowTitle(QCoreApplication::translate("WinSystemRule", "WinSystemRule", nullptr));
        labcp->setText(QCoreApplication::translate("WinSystemRule", "aaaa", nullptr));
        labver->setText(QCoreApplication::translate("WinSystemRule", "aaaa", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinSystemRule: public Ui_WinSystemRule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSYSTEMRULE_H
