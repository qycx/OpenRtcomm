/********************************************************************************
** Form generated from reading UI file 'UserInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFODIALOG_H
#define UI_USERINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInfoDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lab_head;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lab_name;
    QLabel *label_sex;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *dw;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_staticMessengerId;
    QLabel *lab_MessagerId;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_staticLogonTo;
    QLabel *label_server;

    void setupUi(QWidget *UserInfoDialog)
    {
        if (UserInfoDialog->objectName().isEmpty())
            UserInfoDialog->setObjectName("UserInfoDialog");
        UserInfoDialog->resize(287, 253);
        horizontalLayout = new QHBoxLayout(UserInfoDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(UserInfoDialog);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget\n"
"{\n"
"  \n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 86));
        widget_2->setMaximumSize(QSize(16777215, 86));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget#widget_2\n"
"{\n"
" border-bottom:1px solid #e5e5e5;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 16);
        lab_head = new QLabel(widget_2);
        lab_head->setObjectName("lab_head");
        lab_head->setMinimumSize(QSize(70, 70));
        lab_head->setMaximumSize(QSize(70, 70));

        horizontalLayout_2->addWidget(lab_head);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(8);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 12, 0, 0);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 30));
        widget_5->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lab_name = new QLabel(widget_5);
        lab_name->setObjectName("lab_name");
        lab_name->setContextMenuPolicy(Qt::NoContextMenu);
        lab_name->setStyleSheet(QString::fromUtf8("color:#333333;\n"
"font: 22px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-weight:500;"));
        lab_name->setTextInteractionFlags(Qt::TextSelectableByMouse);

        horizontalLayout_3->addWidget(lab_name);

        label_sex = new QLabel(widget_5);
        label_sex->setObjectName("label_sex");
        label_sex->setMinimumSize(QSize(20, 20));
        label_sex->setMaximumSize(QSize(20, 20));
        label_sex->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(label_sex);

        horizontalSpacer = new QSpacerItem(130, 17, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(widget_5);

        verticalSpacer = new QSpacerItem(20, 7, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(widget_4);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 20, 0, 0);
        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_6);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color:#666666;\n"
"font-size:15px;"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        dw = new QLabel(widget_6);
        dw->setObjectName("dw");
        dw->setStyleSheet(QString::fromUtf8("font-size:18px"));

        horizontalLayout_4->addWidget(dw);


        verticalLayout_4->addWidget(widget_6);

        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName("widget_8");
        widget_8->setMinimumSize(QSize(0, 20));
        widget_8->setMaximumSize(QSize(16777215, 20));
        horizontalLayout_5 = new QHBoxLayout(widget_8);
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_staticMessengerId = new QLabel(widget_8);
        label_staticMessengerId->setObjectName("label_staticMessengerId");
        label_staticMessengerId->setMinimumSize(QSize(110, 0));
        label_staticMessengerId->setLayoutDirection(Qt::LeftToRight);
        label_staticMessengerId->setStyleSheet(QString::fromUtf8("color:#666666;"));
        label_staticMessengerId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_staticMessengerId);

        lab_MessagerId = new QLabel(widget_8);
        lab_MessagerId->setObjectName("lab_MessagerId");
        lab_MessagerId->setContextMenuPolicy(Qt::NoContextMenu);
        lab_MessagerId->setStyleSheet(QString::fromUtf8("color:#333333;\n"
"font-size:18px"));
        lab_MessagerId->setTextInteractionFlags(Qt::TextSelectableByMouse);

        horizontalLayout_5->addWidget(lab_MessagerId);


        verticalLayout_4->addWidget(widget_8);

        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName("widget_9");
        widget_9->setMinimumSize(QSize(32, 32));
        widget_9->setMaximumSize(QSize(16777215, 32));
        horizontalLayout_6 = new QHBoxLayout(widget_9);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_staticLogonTo = new QLabel(widget_9);
        label_staticLogonTo->setObjectName("label_staticLogonTo");

        horizontalLayout_6->addWidget(label_staticLogonTo);

        label_server = new QLabel(widget_9);
        label_server->setObjectName("label_server");

        horizontalLayout_6->addWidget(label_server);


        verticalLayout_4->addWidget(widget_9);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(UserInfoDialog);

        QMetaObject::connectSlotsByName(UserInfoDialog);
    } // setupUi

    void retranslateUi(QWidget *UserInfoDialog)
    {
        UserInfoDialog->setWindowTitle(QCoreApplication::translate("UserInfoDialog", "UserInfoDialog", nullptr));
        lab_head->setText(QString());
        lab_name->setText(QString());
        label_sex->setText(QString());
        label->setText(QCoreApplication::translate("UserInfoDialog", "      \351\203\250  \351\227\250\357\274\232", nullptr));
        dw->setText(QString());
        label_staticMessengerId->setText(QCoreApplication::translate("UserInfoDialog", "Messenger ID\357\274\232", nullptr));
        lab_MessagerId->setText(QString());
        label_staticLogonTo->setText(QCoreApplication::translate("UserInfoDialog", "Logon to:", nullptr));
        label_server->setText(QCoreApplication::translate("UserInfoDialog", "127.0.0.1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInfoDialog: public Ui_UserInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFODIALOG_H
