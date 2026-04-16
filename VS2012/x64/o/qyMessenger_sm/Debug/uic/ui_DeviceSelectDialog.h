/********************************************************************************
** Form generated from reading UI file 'DeviceSelectDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICESELECTDIALOG_H
#define UI_DEVICESELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceSelectDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *btnAccept;
    QPushButton *btnClose;

    void setupUi(QDialog *DeviceSelectDialog)
    {
        if (DeviceSelectDialog->objectName().isEmpty())
            DeviceSelectDialog->setObjectName("DeviceSelectDialog");
        DeviceSelectDialog->resize(400, 500);
        DeviceSelectDialog->setMinimumSize(QSize(400, 500));
        DeviceSelectDialog->setMaximumSize(QSize(400, 500));
        verticalLayout_3 = new QVBoxLayout(DeviceSelectDialog);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(DeviceSelectDialog);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("#widget\n"
"{\n"
" \n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:18px;\n"
"font-weight:400;"));

        horizontalLayout_2->addWidget(label);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(30, 30));
        pushButton->setMaximumSize(QSize(30, 30));
        pushButton->setStyleSheet(QString::fromUtf8("image: url(:Resources/Images/WinMain/sysbtn_close_normal.png);\n"
"border:none;"));
        pushButton->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName("widget_4");
        verticalLayout_4 = new QVBoxLayout(widget_4);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setMaximumSize(QSize(16777215, 30));

        verticalLayout_4->addWidget(label_3);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        verticalLayout_5 = new QVBoxLayout(widget_5);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(10, 10, 10, 10);

        verticalLayout_4->addWidget(widget_5);

        label_4 = new QLabel(widget_4);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setMaximumSize(QSize(16777215, 30));

        verticalLayout_4->addWidget(label_4);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName("widget_6");
        verticalLayout_6 = new QVBoxLayout(widget_6);
        verticalLayout_6->setSpacing(10);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(10, 10, 10, 10);

        verticalLayout_4->addWidget(widget_6);


        verticalLayout_2->addWidget(widget_4);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName("widget_7");
        widget_7->setMinimumSize(QSize(0, 50));
        widget_7->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(widget_7);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(widget_7);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setMaximumSize(QSize(16777215, 30));
        label_2->setStyleSheet(QString::fromUtf8("color:#666666;"));

        horizontalLayout->addWidget(label_2);

        btnAccept = new QPushButton(widget_7);
        btnAccept->setObjectName("btnAccept");
        btnAccept->setMinimumSize(QSize(50, 30));
        btnAccept->setMaximumSize(QSize(50, 50));
        btnAccept->setStyleSheet(QString::fromUtf8(" background:rgb(22,154,218);\n"
" color:#fff;\n"
"border:none;\n"
"border-radius:5%;"));

        horizontalLayout->addWidget(btnAccept);

        btnClose = new QPushButton(widget_7);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(50, 30));
        btnClose->setMaximumSize(QSize(50, 16777215));
        btnClose->setSizeIncrement(QSize(0, 0));
        btnClose->setStyleSheet(QString::fromUtf8(" background:gray;\n"
"color:#fff;\n"
"border:none;\n"
"border-radius:5%;"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_2->addWidget(widget_7);


        verticalLayout->addWidget(widget_3);


        verticalLayout_3->addWidget(widget);


        retranslateUi(DeviceSelectDialog);
        QObject::connect(pushButton, &QPushButton::clicked, DeviceSelectDialog, qOverload<>(&QDialog::close));
        QObject::connect(btnClose, &QPushButton::clicked, DeviceSelectDialog, qOverload<>(&QDialog::close));
        QObject::connect(btnAccept, &QPushButton::clicked, DeviceSelectDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(DeviceSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *DeviceSelectDialog)
    {
        DeviceSelectDialog->setWindowTitle(QCoreApplication::translate("DeviceSelectDialog", "\351\237\263\350\247\206\351\242\221\350\256\276\345\244\207\346\216\247\345\210\266", nullptr));
        label->setText(QCoreApplication::translate("DeviceSelectDialog", "\351\237\263\350\247\206\351\242\221\350\256\276\345\244\207\346\216\247\345\210\266", nullptr));
        pushButton->setText(QString());
        label_3->setText(QCoreApplication::translate("DeviceSelectDialog", "\350\247\206\351\242\221\350\256\276\345\244\207:", nullptr));
        label_4->setText(QCoreApplication::translate("DeviceSelectDialog", "\351\237\263\351\242\221\350\256\276\345\244\207:", nullptr));
        label_2->setText(QCoreApplication::translate("DeviceSelectDialog", "\346\263\250\357\274\232\345\217\230\345\212\250\345\220\216\351\234\200\350\246\201\351\207\215\345\220\257\350\247\206\351\242\221\347\252\227\345\217\243", nullptr));
        btnAccept->setText(QCoreApplication::translate("DeviceSelectDialog", "\347\241\256\350\256\244", nullptr));
        btnClose->setText(QCoreApplication::translate("DeviceSelectDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceSelectDialog: public Ui_DeviceSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICESELECTDIALOG_H
