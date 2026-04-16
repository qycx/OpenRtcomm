/********************************************************************************
** Form generated from reading UI file 'WinRuleSet.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINRULESET_H
#define UI_WINRULESET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinRuleSet
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *btnClose;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_6;
    QPushButton *btnAccept;
    QPushButton *pushButton_2;

    void setupUi(QWidget *WinRuleSet)
    {
        if (WinRuleSet->objectName().isEmpty())
            WinRuleSet->setObjectName("WinRuleSet");
        WinRuleSet->resize(267, 182);
        WinRuleSet->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(WinRuleSet);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        widget = new QWidget(WinRuleSet);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:16px;"));

        horizontalLayout->addWidget(label);

        btnClose = new QPushButton(widget_2);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        btnClose->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnClose->setStyleSheet(QString::fromUtf8("image: url(:Resources/Images/WinMain/sysbtn_close_normal.png);\n"
"border:none;"));
        btnClose->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName("widget_4");
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        verticalLayout_3->addWidget(widget_5);


        verticalLayout_4->addWidget(widget_4);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(0, 40));
        widget_6->setMaximumSize(QSize(16777215, 40));
        btnAccept = new QPushButton(widget_6);
        btnAccept->setObjectName("btnAccept");
        btnAccept->setGeometry(QRect(130, 10, 50, 30));
        btnAccept->setMinimumSize(QSize(50, 30));
        btnAccept->setMaximumSize(QSize(50, 30));
        btnAccept->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnAccept->setStyleSheet(QString::fromUtf8("background:rgb(22,154,218);\n"
"color:#fff;\n"
"border:none;\n"
"border-radius:5%;"));
        pushButton_2 = new QPushButton(widget_6);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(190, 10, 50, 30));
        pushButton_2->setMinimumSize(QSize(50, 30));
        pushButton_2->setMaximumSize(QSize(50, 30));
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-radius:5%;\n"
"border:1px solid #999;"));

        verticalLayout_4->addWidget(widget_6);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);


        retranslateUi(WinRuleSet);
        QObject::connect(btnClose, &QPushButton::clicked, WinRuleSet, qOverload<>(&QWidget::close));
        QObject::connect(pushButton_2, &QPushButton::clicked, WinRuleSet, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(WinRuleSet);
    } // setupUi

    void retranslateUi(QWidget *WinRuleSet)
    {
        WinRuleSet->setWindowTitle(QCoreApplication::translate("WinRuleSet", "WinRuleSet", nullptr));
        label->setText(QCoreApplication::translate("WinRuleSet", " \350\247\204\345\210\231", nullptr));
        btnClose->setText(QString());
        label_2->setText(QCoreApplication::translate("WinRuleSet", "\350\247\206\351\242\221\346\216\245\346\224\266\350\247\204\345\210\231\357\274\232", nullptr));
        btnAccept->setText(QCoreApplication::translate("WinRuleSet", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WinRuleSet", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinRuleSet: public Ui_WinRuleSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINRULESET_H
