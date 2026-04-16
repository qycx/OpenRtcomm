/********************************************************************************
** Form generated from reading UI file 'CUserLogin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSERLOGIN_H
#define UI_CUSERLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CUserLoginClass
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *winWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *bodywidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *lab_title;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *editUkey;
    QLineEdit *editUserAccount;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *editPassword;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *loginUserBtn;
    QWidget *ukeyStatuswidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *ukeyStatus;
    QWidget *widget_1;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *ukey_img;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *lab_img2;
    QLabel *label_status;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *prodName;

    void setupUi(QWidget *CUserLoginClass)
    {
        if (CUserLoginClass->objectName().isEmpty())
            CUserLoginClass->setObjectName("CUserLoginClass");
        CUserLoginClass->resize(1428, 1302);
        CUserLoginClass->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(CUserLoginClass);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        winWidget = new QWidget(CUserLoginClass);
        winWidget->setObjectName("winWidget");
        winWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(winWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        bodywidget = new QWidget(winWidget);
        bodywidget->setObjectName("bodywidget");
        bodywidget->setProperty("bottomskin", QVariant(true));
        verticalLayout_3 = new QVBoxLayout(bodywidget);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(72, 90, 72, 20);
        widget_2 = new QWidget(bodywidget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(1284, 1040));
        widget_2->setMaximumSize(QSize(1284, 1040));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        lab_title = new QLabel(widget_2);
        lab_title->setObjectName("lab_title");
        lab_title->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(lab_title, 0, Qt::AlignHCenter);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName("widget_3");
        widget_3->setStyleSheet(QString::fromUtf8("background:none"));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 10, 0, 0);
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        editUkey = new QLineEdit(widget_5);
        editUkey->setObjectName("editUkey");
        editUkey->setEnabled(false);
        editUkey->setMinimumSize(QSize(1096, 160));
        editUkey->setMaximumSize(QSize(1096, 160));
        editUkey->setEchoMode(QLineEdit::Normal);
        editUkey->setDragEnabled(false);

        horizontalLayout_4->addWidget(editUkey);


        verticalLayout_2->addWidget(widget_5);

        editUserAccount = new QLineEdit(widget_3);
        editUserAccount->setObjectName("editUserAccount");
        editUserAccount->setMinimumSize(QSize(1096, 160));
        editUserAccount->setMaximumSize(QSize(1096, 160));

        verticalLayout_2->addWidget(editUserAccount);


        verticalLayout->addWidget(widget_3, 0, Qt::AlignHCenter);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        widget_4->setStyleSheet(QString::fromUtf8("background:none"));
        horizontalLayout_6 = new QHBoxLayout(widget_4);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 10, 0, 0);
        editPassword = new QLineEdit(widget_4);
        editPassword->setObjectName("editPassword");
        editPassword->setMinimumSize(QSize(1096, 160));
        editPassword->setMaximumSize(QSize(1096, 160));
        editPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        horizontalLayout_6->addWidget(editPassword);


        verticalLayout->addWidget(widget_4, 0, Qt::AlignHCenter);

        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background:none"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 20, 0, 0);
        loginUserBtn = new QPushButton(widget);
        loginUserBtn->setObjectName("loginUserBtn");
        loginUserBtn->setMinimumSize(QSize(1096, 160));
        loginUserBtn->setMaximumSize(QSize(1096, 160));
        loginUserBtn->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(loginUserBtn);

        ukeyStatuswidget = new QWidget(widget);
        ukeyStatuswidget->setObjectName("ukeyStatuswidget");
        ukeyStatuswidget->setMinimumSize(QSize(0, 100));
        ukeyStatuswidget->setMaximumSize(QSize(1096, 16777215));
        horizontalLayout_5 = new QHBoxLayout(ukeyStatuswidget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        ukeyStatus = new QLabel(ukeyStatuswidget);
        ukeyStatus->setObjectName("ukeyStatus");

        horizontalLayout_5->addWidget(ukeyStatus, 0, Qt::AlignHCenter);


        verticalLayout_4->addWidget(ukeyStatuswidget);


        verticalLayout->addWidget(widget, 0, Qt::AlignHCenter);

        widget_1 = new QWidget(widget_2);
        widget_1->setObjectName("widget_1");
        widget_1->setMinimumSize(QSize(64, 64));
        widget_1->setMaximumSize(QSize(16777215, 16777215));
        widget_1->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_3 = new QHBoxLayout(widget_1);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_7 = new QWidget(widget_1);
        widget_7->setObjectName("widget_7");
        horizontalLayout_8 = new QHBoxLayout(widget_7);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        ukey_img = new QLabel(widget_7);
        ukey_img->setObjectName("ukey_img");
        ukey_img->setMinimumSize(QSize(64, 64));
        ukey_img->setMaximumSize(QSize(64, 64));
        ukey_img->setSizeIncrement(QSize(0, 0));

        horizontalLayout_8->addWidget(ukey_img, 0, Qt::AlignRight);


        horizontalLayout_3->addWidget(widget_7);

        widget_6 = new QWidget(widget_1);
        widget_6->setObjectName("widget_6");
        horizontalLayout_7 = new QHBoxLayout(widget_6);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        lab_img2 = new QPushButton(widget_6);
        lab_img2->setObjectName("lab_img2");
        lab_img2->setEnabled(false);
        lab_img2->setMinimumSize(QSize(46, 46));
        lab_img2->setMaximumSize(QSize(46, 46));

        horizontalLayout_7->addWidget(lab_img2, 0, Qt::AlignVCenter);

        label_status = new QLabel(widget_6);
        label_status->setObjectName("label_status");

        horizontalLayout_7->addWidget(label_status, 0, Qt::AlignVCenter);


        horizontalLayout_3->addWidget(widget_6);


        verticalLayout->addWidget(widget_1);

        widget_8 = new QWidget(widget_2);
        widget_8->setObjectName("widget_8");
        horizontalLayout_9 = new QHBoxLayout(widget_8);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        prodName = new QLabel(widget_8);
        prodName->setObjectName("prodName");
        prodName->setStyleSheet(QString::fromUtf8("color:#fff"));

        horizontalLayout_9->addWidget(prodName);


        verticalLayout->addWidget(widget_8, 0, Qt::AlignHCenter|Qt::AlignBottom);


        verticalLayout_3->addWidget(widget_2, 0, Qt::AlignHCenter);


        horizontalLayout->addWidget(bodywidget);


        horizontalLayout_2->addWidget(winWidget);


        retranslateUi(CUserLoginClass);

        QMetaObject::connectSlotsByName(CUserLoginClass);
    } // setupUi

    void retranslateUi(QWidget *CUserLoginClass)
    {
        CUserLoginClass->setWindowTitle(QCoreApplication::translate("CUserLoginClass", "CUserLogin", nullptr));
        CUserLoginClass->setWindowFilePath(QString());
        lab_title->setText(QCoreApplication::translate("CUserLoginClass", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        editUkey->setText(QCoreApplication::translate("CUserLoginClass", "\350\257\267\346\217\222\345\205\245\347\224\250\346\210\267UKEY", nullptr));
        editUserAccount->setPlaceholderText(QCoreApplication::translate("CUserLoginClass", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        editPassword->setText(QString());
        editPassword->setPlaceholderText(QCoreApplication::translate("CUserLoginClass", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        loginUserBtn->setText(QCoreApplication::translate("CUserLoginClass", "\347\231\273 \345\275\225", nullptr));
        ukeyStatus->setText(QCoreApplication::translate("CUserLoginClass", "\346\234\252\345\220\257\347\224\250UKEY\347\231\273\345\275\225", nullptr));
        ukey_img->setText(QString());
        lab_img2->setText(QString());
        label_status->setText(QCoreApplication::translate("CUserLoginClass", "\350\256\244\350\257\201\346\210\220\345\212\237", nullptr));
        prodName->setText(QCoreApplication::translate("CUserLoginClass", "\346\270\205\346\211\254\344\277\241\345\256\211\347\241\254\344\273\266\350\247\206\351\242\221\344\274\232\350\256\256\347\273\210\347\253\257 MBX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CUserLoginClass: public Ui_CUserLoginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSERLOGIN_H
