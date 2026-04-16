/********************************************************************************
** Form generated from reading UI file 'CDeviceBinding.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDEVICEBINDING_H
#define UI_CDEVICEBINDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDeviceBindingClass
{
public:
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_title;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_t20;
    QLineEdit *terminal_username;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_t21;
    QLineEdit *terminal_pwd;
    QWidget *widget_yt_wireless;
    QHBoxLayout *horizontalLayout_131;
    QLabel *label_net;
    QPushButton *pushButton_wireless;
    QWidget *widget_yt_share;
    QHBoxLayout *horizontalLayout_1314;
    QLabel *label_share;
    QPushButton *pushButton_share;
    QWidget *widget_yt_selectVideo;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_selectVideo;
    QPushButton *pushButton_selectVideo;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_t2;
    QLineEdit *terminal_ip;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_t4;
    QLineEdit *terminal_mask;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_t3;
    QLineEdit *terminal_gateway;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_t8;
    QLineEdit *terminal_dns;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_t5;
    QLineEdit *terminal_mcu;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_t9;
    QLineEdit *terminal_mcu2;
    QWidget *widget_sm;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_t6;
    QLineEdit *terminal_sqm;
    QWidget *widget_yt;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_t22;
    QPushButton *btn_nvr;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_t7;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton_check;
    QPushButton *btn;
    QPushButton *btnCancel;
    QLabel *lab_err;

    void setupUi(QDialog *CDeviceBindingClass)
    {
        if (CDeviceBindingClass->objectName().isEmpty())
            CDeviceBindingClass->setObjectName("CDeviceBindingClass");
        CDeviceBindingClass->resize(2069, 2359);
        horizontalLayout_4 = new QHBoxLayout(CDeviceBindingClass);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDeviceBindingClass);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(200, -1, 200, -1);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        label_title = new QLabel(widget_2);
        label_title->setObjectName("label_title");
        label_title->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_title);


        verticalLayout_2->addWidget(widget_2);

        widget_11 = new QWidget(widget);
        widget_11->setObjectName("widget_11");
        horizontalLayout_11 = new QHBoxLayout(widget_11);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(-1, -1, 500, -1);
        label_t20 = new QLabel(widget_11);
        label_t20->setObjectName("label_t20");
        label_t20->setMinimumSize(QSize(250, 0));
        label_t20->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_11->addWidget(label_t20);

        terminal_username = new QLineEdit(widget_11);
        terminal_username->setObjectName("terminal_username");
        terminal_username->setMinimumSize(QSize(0, 160));

        horizontalLayout_11->addWidget(terminal_username);


        verticalLayout_2->addWidget(widget_11);

        widget_12 = new QWidget(widget);
        widget_12->setObjectName("widget_12");
        horizontalLayout_12 = new QHBoxLayout(widget_12);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(-1, -1, 500, -1);
        label_t21 = new QLabel(widget_12);
        label_t21->setObjectName("label_t21");
        label_t21->setMinimumSize(QSize(250, 0));
        label_t21->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_12->addWidget(label_t21);

        terminal_pwd = new QLineEdit(widget_12);
        terminal_pwd->setObjectName("terminal_pwd");
        terminal_pwd->setMinimumSize(QSize(0, 160));
        terminal_pwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        horizontalLayout_12->addWidget(terminal_pwd);


        verticalLayout_2->addWidget(widget_12);

        widget_yt_wireless = new QWidget(widget);
        widget_yt_wireless->setObjectName("widget_yt_wireless");
        horizontalLayout_131 = new QHBoxLayout(widget_yt_wireless);
        horizontalLayout_131->setSpacing(6);
        horizontalLayout_131->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_131->setObjectName("horizontalLayout_131");
        horizontalLayout_131->setContentsMargins(-1, -1, 500, -1);
        label_net = new QLabel(widget_yt_wireless);
        label_net->setObjectName("label_net");
        label_net->setMinimumSize(QSize(250, 0));
        label_net->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_131->addWidget(label_net, 0, Qt::AlignLeft);

        pushButton_wireless = new QPushButton(widget_yt_wireless);
        pushButton_wireless->setObjectName("pushButton_wireless");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(pushButton_wireless->sizePolicy().hasHeightForWidth());
        pushButton_wireless->setSizePolicy(sizePolicy);
        pushButton_wireless->setMinimumSize(QSize(200, 80));
        pushButton_wireless->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_131->addWidget(pushButton_wireless);


        verticalLayout_2->addWidget(widget_yt_wireless, 0, Qt::AlignLeft);

        widget_yt_share = new QWidget(widget);
        widget_yt_share->setObjectName("widget_yt_share");
        horizontalLayout_1314 = new QHBoxLayout(widget_yt_share);
        horizontalLayout_1314->setSpacing(6);
        horizontalLayout_1314->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_1314->setObjectName("horizontalLayout_1314");
        horizontalLayout_1314->setContentsMargins(-1, -1, 500, -1);
        label_share = new QLabel(widget_yt_share);
        label_share->setObjectName("label_share");
        label_share->setMinimumSize(QSize(250, 0));
        label_share->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_1314->addWidget(label_share, 0, Qt::AlignLeft);

        pushButton_share = new QPushButton(widget_yt_share);
        pushButton_share->setObjectName("pushButton_share");
        sizePolicy.setHeightForWidth(pushButton_share->sizePolicy().hasHeightForWidth());
        pushButton_share->setSizePolicy(sizePolicy);
        pushButton_share->setMinimumSize(QSize(200, 80));
        pushButton_share->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_1314->addWidget(pushButton_share);


        verticalLayout_2->addWidget(widget_yt_share, 0, Qt::AlignLeft);

        widget_yt_selectVideo = new QWidget(widget);
        widget_yt_selectVideo->setObjectName("widget_yt_selectVideo");
        horizontalLayout_15 = new QHBoxLayout(widget_yt_selectVideo);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(-1, -1, 500, -1);
        label_selectVideo = new QLabel(widget_yt_selectVideo);
        label_selectVideo->setObjectName("label_selectVideo");
        label_selectVideo->setMinimumSize(QSize(250, 0));
        label_selectVideo->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_15->addWidget(label_selectVideo);

        pushButton_selectVideo = new QPushButton(widget_yt_selectVideo);
        pushButton_selectVideo->setObjectName("pushButton_selectVideo");
        sizePolicy.setHeightForWidth(pushButton_selectVideo->sizePolicy().hasHeightForWidth());
        pushButton_selectVideo->setSizePolicy(sizePolicy);
        pushButton_selectVideo->setMinimumSize(QSize(200, 80));
        pushButton_selectVideo->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_15->addWidget(pushButton_selectVideo);


        verticalLayout_2->addWidget(widget_yt_selectVideo, 0, Qt::AlignLeft);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        widget_4->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, -1, 500, -1);
        label_t2 = new QLabel(widget_4);
        label_t2->setObjectName("label_t2");
        label_t2->setMinimumSize(QSize(250, 0));
        label_t2->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_3->addWidget(label_t2);

        terminal_ip = new QLineEdit(widget_4);
        terminal_ip->setObjectName("terminal_ip");
        terminal_ip->setMinimumSize(QSize(0, 160));

        horizontalLayout_3->addWidget(terminal_ip);


        verticalLayout_2->addWidget(widget_4);

        widget_9 = new QWidget(widget);
        widget_9->setObjectName("widget_9");
        horizontalLayout_8 = new QHBoxLayout(widget_9);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(-1, -1, 500, -1);
        label_t4 = new QLabel(widget_9);
        label_t4->setObjectName("label_t4");
        label_t4->setMinimumSize(QSize(250, 0));
        label_t4->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_8->addWidget(label_t4);

        terminal_mask = new QLineEdit(widget_9);
        terminal_mask->setObjectName("terminal_mask");
        terminal_mask->setMinimumSize(QSize(0, 160));

        horizontalLayout_8->addWidget(terminal_mask);


        verticalLayout_2->addWidget(widget_9);

        widget_8 = new QWidget(widget);
        widget_8->setObjectName("widget_8");
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, -1, 500, -1);
        label_t3 = new QLabel(widget_8);
        label_t3->setObjectName("label_t3");
        label_t3->setMinimumSize(QSize(250, 0));
        label_t3->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_7->addWidget(label_t3);

        terminal_gateway = new QLineEdit(widget_8);
        terminal_gateway->setObjectName("terminal_gateway");
        terminal_gateway->setMinimumSize(QSize(0, 160));

        horizontalLayout_7->addWidget(terminal_gateway);


        verticalLayout_2->addWidget(widget_8);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout_9 = new QHBoxLayout(widget_3);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(-1, -1, 500, -1);
        label_t8 = new QLabel(widget_3);
        label_t8->setObjectName("label_t8");
        label_t8->setMinimumSize(QSize(250, 0));
        label_t8->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_9->addWidget(label_t8);

        terminal_dns = new QLineEdit(widget_3);
        terminal_dns->setObjectName("terminal_dns");
        terminal_dns->setMinimumSize(QSize(0, 160));

        horizontalLayout_9->addWidget(terminal_dns);


        verticalLayout_2->addWidget(widget_3);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, -1, 500, -1);
        label_t5 = new QLabel(widget_5);
        label_t5->setObjectName("label_t5");
        label_t5->setMinimumSize(QSize(250, 0));
        label_t5->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_5->addWidget(label_t5);

        terminal_mcu = new QLineEdit(widget_5);
        terminal_mcu->setObjectName("terminal_mcu");
        terminal_mcu->setMinimumSize(QSize(0, 160));

        horizontalLayout_5->addWidget(terminal_mcu);


        verticalLayout_2->addWidget(widget_5);

        widget_10 = new QWidget(widget);
        widget_10->setObjectName("widget_10");
        horizontalLayout_10 = new QHBoxLayout(widget_10);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(-1, -1, 500, -1);
        label_t9 = new QLabel(widget_10);
        label_t9->setObjectName("label_t9");
        label_t9->setMinimumSize(QSize(250, 0));
        label_t9->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_10->addWidget(label_t9);

        terminal_mcu2 = new QLineEdit(widget_10);
        terminal_mcu2->setObjectName("terminal_mcu2");
        terminal_mcu2->setMinimumSize(QSize(0, 160));

        horizontalLayout_10->addWidget(terminal_mcu2);


        verticalLayout_2->addWidget(widget_10);

        widget_sm = new QWidget(widget);
        widget_sm->setObjectName("widget_sm");
        widget_sm->setMinimumSize(QSize(0, 0));
        widget_sm->setMaximumSize(QSize(16777215, 16777215));
        widget_sm->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(widget_sm);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, 500, -1);
        label_t6 = new QLabel(widget_sm);
        label_t6->setObjectName("label_t6");
        label_t6->setMinimumSize(QSize(250, 0));
        label_t6->setMaximumSize(QSize(250, 16777215));
        label_t6->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_t6);

        terminal_sqm = new QLineEdit(widget_sm);
        terminal_sqm->setObjectName("terminal_sqm");
        terminal_sqm->setMinimumSize(QSize(0, 160));
        terminal_sqm->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(terminal_sqm);


        verticalLayout_2->addWidget(widget_sm);

        widget_yt = new QWidget(widget);
        widget_yt->setObjectName("widget_yt");
        horizontalLayout_13 = new QHBoxLayout(widget_yt);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(-1, -1, 500, -1);
        label_t22 = new QLabel(widget_yt);
        label_t22->setObjectName("label_t22");
        label_t22->setMinimumSize(QSize(250, 0));
        label_t22->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_13->addWidget(label_t22, 0, Qt::AlignLeft);

        btn_nvr = new QPushButton(widget_yt);
        btn_nvr->setObjectName("btn_nvr");
        sizePolicy.setHeightForWidth(btn_nvr->sizePolicy().hasHeightForWidth());
        btn_nvr->setSizePolicy(sizePolicy);
        btn_nvr->setMinimumSize(QSize(200, 80));
        btn_nvr->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_13->addWidget(btn_nvr);


        verticalLayout_2->addWidget(widget_yt, 0, Qt::AlignLeft);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName("widget_6");
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(-1, -1, 500, -1);
        label_t7 = new QLabel(widget_6);
        label_t7->setObjectName("label_t7");
        label_t7->setMinimumSize(QSize(250, 0));
        label_t7->setMaximumSize(QSize(250, 16777215));
        label_t7->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(label_t7);

        widget_14 = new QWidget(widget_6);
        widget_14->setObjectName("widget_14");
        horizontalLayout_14 = new QHBoxLayout(widget_14);
        horizontalLayout_14->setSpacing(5);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        pushButton_check = new QPushButton(widget_14);
        pushButton_check->setObjectName("pushButton_check");
        sizePolicy.setHeightForWidth(pushButton_check->sizePolicy().hasHeightForWidth());
        pushButton_check->setSizePolicy(sizePolicy);
        pushButton_check->setMinimumSize(QSize(200, 80));
        pushButton_check->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_14->addWidget(pushButton_check);

        btn = new QPushButton(widget_14);
        btn->setObjectName("btn");
        btn->setMinimumSize(QSize(500, 134));
        btn->setMaximumSize(QSize(500, 134));
        btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_14->addWidget(btn, 0, Qt::AlignLeft);

        btnCancel = new QPushButton(widget_14);
        btnCancel->setObjectName("btnCancel");

        horizontalLayout_14->addWidget(btnCancel, 0, Qt::AlignLeft);


        horizontalLayout_6->addWidget(widget_14, 0, Qt::AlignLeft);

        lab_err = new QLabel(widget_6);
        lab_err->setObjectName("lab_err");

        horizontalLayout_6->addWidget(lab_err, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_6);


        horizontalLayout_4->addWidget(widget);


        retranslateUi(CDeviceBindingClass);

        QMetaObject::connectSlotsByName(CDeviceBindingClass);
    } // setupUi

    void retranslateUi(QDialog *CDeviceBindingClass)
    {
        CDeviceBindingClass->setWindowTitle(QCoreApplication::translate("CDeviceBindingClass", "CDeviceBinding", nullptr));
        label_title->setText(QCoreApplication::translate("CDeviceBindingClass", "\345\210\235\345\247\213\345\214\226\351\205\215\347\275\256", nullptr));
        label_t20->setText(QCoreApplication::translate("CDeviceBindingClass", "\347\231\273\345\275\225\350\264\246\345\217\267", nullptr));
        terminal_username->setText(QString());
        terminal_username->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245\347\231\273\345\275\225\350\264\246\345\217\267", nullptr));
        label_t21->setText(QCoreApplication::translate("CDeviceBindingClass", "\347\231\273\345\275\225\345\257\206\347\240\201", nullptr));
        terminal_pwd->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245\347\231\273\345\275\225\345\257\206\347\240\201", nullptr));
        label_net->setText(QCoreApplication::translate("CDeviceBindingClass", "\346\227\240\347\272\277\347\275\221\350\256\276\347\275\256", nullptr));
        pushButton_wireless->setText(QCoreApplication::translate("CDeviceBindingClass", "\350\256\276\347\275\256", nullptr));
        label_share->setText(QCoreApplication::translate("CDeviceBindingClass", "\345\205\261\344\272\253\350\256\276\347\275\256", nullptr));
        pushButton_share->setText(QCoreApplication::translate("CDeviceBindingClass", "\350\256\276\347\275\256", nullptr));
        label_selectVideo->setText(QCoreApplication::translate("CDeviceBindingClass", "\350\247\206\351\242\221\346\272\220\350\256\276\347\275\256", nullptr));
        pushButton_selectVideo->setText(QCoreApplication::translate("CDeviceBindingClass", "\350\256\276\347\275\256", nullptr));
        label_t2->setText(QCoreApplication::translate("CDeviceBindingClass", "IP\345\234\260\345\235\200", nullptr));
        terminal_ip->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245ip\345\234\260\345\235\200\357\274\214\346\240\274\345\274\217: 192.168.1.12", nullptr));
        label_t4->setText(QCoreApplication::translate("CDeviceBindingClass", "\345\255\220\347\275\221\346\216\251\347\240\201", nullptr));
        terminal_mask->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245\345\255\220\347\275\221\346\216\251\347\240\201\357\274\214\346\240\274\345\274\217\357\274\232255.255.255.0", nullptr));
        label_t3->setText(QCoreApplication::translate("CDeviceBindingClass", "\347\275\221     \345\205\263", nullptr));
        terminal_gateway->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245\347\275\221\345\205\263\357\274\214\346\240\274\345\274\217\357\274\232192.168.1.1", nullptr));
        label_t8->setText(QCoreApplication::translate("CDeviceBindingClass", "DNS\345\234\260\345\235\200", nullptr));
        terminal_dns->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245DNS\345\234\260\345\235\200\357\274\214\346\240\274\345\274\217\357\274\2328.8.8.8", nullptr));
        label_t5->setText(QCoreApplication::translate("CDeviceBindingClass", "MCU\345\234\260\345\235\2001", nullptr));
        terminal_mcu->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245MCU1\345\234\260\345\235\200\357\274\214 \346\240\274\345\274\217\357\274\232192.168.1.124", nullptr));
        label_t9->setText(QCoreApplication::translate("CDeviceBindingClass", "MCU\345\234\260\345\235\2002", nullptr));
        terminal_mcu2->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245MCU2\345\234\260\345\235\200\357\274\214 \346\240\274\345\274\217\357\274\232192.168.1.124", nullptr));
        label_t6->setText(QCoreApplication::translate("CDeviceBindingClass", "\346\263\250\345\206\214\347\240\201", nullptr));
        terminal_sqm->setPlaceholderText(QCoreApplication::translate("CDeviceBindingClass", "\350\276\223\345\205\245\347\273\210\347\253\257\346\216\210\346\235\203\347\240\201", nullptr));
        label_t22->setText(QCoreApplication::translate("CDeviceBindingClass", "\345\205\266\345\256\203\350\256\276\347\275\256", nullptr));
        btn_nvr->setText(QCoreApplication::translate("CDeviceBindingClass", "NVR\351\205\215\347\275\256", nullptr));
        label_t7->setText(QString());
        pushButton_check->setText(QCoreApplication::translate("CDeviceBindingClass", "\346\243\200\346\265\213", nullptr));
        btn->setText(QCoreApplication::translate("CDeviceBindingClass", "\344\277\235 \345\255\230", nullptr));
        btnCancel->setText(QCoreApplication::translate("CDeviceBindingClass", "\345\217\226\346\266\210", nullptr));
        lab_err->setText(QCoreApplication::translate("CDeviceBindingClass", "\350\257\267\350\276\223\345\205\245IP\345\234\260\345\235\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDeviceBindingClass: public Ui_CDeviceBindingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDEVICEBINDING_H
