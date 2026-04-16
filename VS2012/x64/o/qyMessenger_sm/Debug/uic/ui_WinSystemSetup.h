/********************************************************************************
** Form generated from reading UI file 'WinSystemSetup.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSYSTEMSETUP_H
#define UI_WINSYSTEMSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSystemSetup
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QPushButton *BtnClose;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *BtnRule;
    QPushButton *BtnPwd;
    QPushButton *BtnDebug;
    QPushButton *BtnGuide;
    QSpacerItem *verticalSpacer;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QStackedWidget *SystemstackedWidget;

    void setupUi(QWidget *WinSystemSetup)
    {
        if (WinSystemSetup->objectName().isEmpty())
            WinSystemSetup->setObjectName("WinSystemSetup");
        WinSystemSetup->resize(754, 784);
        horizontalLayout = new QHBoxLayout(WinSystemSetup);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(WinSystemSetup);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background:#fff;"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:18px;\n"
""));

        horizontalLayout_3->addWidget(label);

        BtnClose = new QPushButton(widget_2);
        BtnClose->setObjectName("BtnClose");
        BtnClose->setMinimumSize(QSize(30, 30));
        BtnClose->setMaximumSize(QSize(30, 30));
        BtnClose->setStyleSheet(QString::fromUtf8("border:none;"));
        BtnClose->setIconSize(QSize(30, 30));

        horizontalLayout_3->addWidget(BtnClose);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(30, 43, -1, -1);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(100, 0));
        widget_4->setMaximumSize(QSize(100, 16777215));
        widget_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font-size:18px;\n"
"border:none;\n"
"cursor:pointer;\n"
"}\n"
"QWidget#widget_4{\n"
"  border-right:1px solid #999;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        BtnRule = new QPushButton(widget_4);
        BtnRule->setObjectName("BtnRule");
        BtnRule->setMinimumSize(QSize(0, 40));

        verticalLayout_2->addWidget(BtnRule);

        BtnPwd = new QPushButton(widget_4);
        BtnPwd->setObjectName("BtnPwd");
        BtnPwd->setMinimumSize(QSize(0, 40));

        verticalLayout_2->addWidget(BtnPwd);

        BtnDebug = new QPushButton(widget_4);
        BtnDebug->setObjectName("BtnDebug");
        BtnDebug->setMinimumSize(QSize(0, 40));

        verticalLayout_2->addWidget(BtnDebug);

        BtnGuide = new QPushButton(widget_4);
        BtnGuide->setObjectName("BtnGuide");
        BtnGuide->setMinimumSize(QSize(0, 40));

        verticalLayout_2->addWidget(BtnGuide);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        SystemstackedWidget = new QStackedWidget(widget_5);
        SystemstackedWidget->setObjectName("SystemstackedWidget");
        SystemstackedWidget->setMinimumSize(QSize(0, 0));
        SystemstackedWidget->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(SystemstackedWidget);


        horizontalLayout_2->addWidget(widget_5);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(WinSystemSetup);

        SystemstackedWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(WinSystemSetup);
    } // setupUi

    void retranslateUi(QWidget *WinSystemSetup)
    {
        WinSystemSetup->setWindowTitle(QCoreApplication::translate("WinSystemSetup", "WinSystemSetup", nullptr));
        label->setText(QCoreApplication::translate("WinSystemSetup", "  \347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        BtnClose->setText(QString());
        BtnRule->setText(QString());
        BtnPwd->setText(QString());
        BtnDebug->setText(QString());
        BtnGuide->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WinSystemSetup: public Ui_WinSystemSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSYSTEMSETUP_H
