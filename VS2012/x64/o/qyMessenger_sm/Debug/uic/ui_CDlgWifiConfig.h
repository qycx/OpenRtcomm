/********************************************************************************
** Form generated from reading UI file 'CDlgWifiConfig.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGWIFICONFIG_H
#define UI_CDLGWIFICONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgWifiConfigClass
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_21;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget_wifi;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_8;
    QLabel *label_title;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_ssid;
    QLineEdit *lineEdit_ssid;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_pw;
    QLineEdit *lineEdit_pw;
    QWidget *widget_6;
    QPushButton *pushButton_detect;
    QPushButton *pushButton_conn;
    QWidget *widget_5;
    QTextEdit *textEdit_msg;
    QWidget *widget_7;
    QPushButton *btnOk;

    void setupUi(QDialog *CDlgWifiConfigClass)
    {
        if (CDlgWifiConfigClass->objectName().isEmpty())
            CDlgWifiConfigClass->setObjectName("CDlgWifiConfigClass");
        CDlgWifiConfigClass->resize(1041, 532);
        verticalLayout = new QVBoxLayout(CDlgWifiConfigClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgWifiConfigClass);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(100, -1, 100, -1);
        widget_21 = new QWidget(widget);
        widget_21->setObjectName("widget_21");
        widget_21->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_3 = new QHBoxLayout(widget_21);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(widget_21);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        treeWidget_wifi = new QTreeWidget(widget_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_wifi->setHeaderItem(__qtreewidgetitem);
        treeWidget_wifi->setObjectName("treeWidget_wifi");

        horizontalLayout->addWidget(treeWidget_wifi);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget_8 = new QWidget(widget_2);
        widget_8->setObjectName("widget_8");
        label_title = new QLabel(widget_8);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(150, 20, 141, 31));

        verticalLayout_3->addWidget(widget_8);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_ssid = new QLabel(widget_4);
        label_ssid->setObjectName("label_ssid");

        horizontalLayout_4->addWidget(label_ssid);

        lineEdit_ssid = new QLineEdit(widget_4);
        lineEdit_ssid->setObjectName("lineEdit_ssid");

        horizontalLayout_4->addWidget(lineEdit_ssid);


        verticalLayout_3->addWidget(widget_4);

        widget_9 = new QWidget(widget_2);
        widget_9->setObjectName("widget_9");
        horizontalLayout_5 = new QHBoxLayout(widget_9);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_pw = new QLabel(widget_9);
        label_pw->setObjectName("label_pw");

        horizontalLayout_5->addWidget(label_pw);

        lineEdit_pw = new QLineEdit(widget_9);
        lineEdit_pw->setObjectName("lineEdit_pw");

        horizontalLayout_5->addWidget(lineEdit_pw);


        verticalLayout_3->addWidget(widget_9);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName("widget_6");
        pushButton_detect = new QPushButton(widget_6);
        pushButton_detect->setObjectName("pushButton_detect");
        pushButton_detect->setGeometry(QRect(40, 20, 93, 41));
        pushButton_conn = new QPushButton(widget_6);
        pushButton_conn->setObjectName("pushButton_conn");
        pushButton_conn->setGeometry(QRect(220, 20, 93, 41));

        verticalLayout_3->addWidget(widget_6);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName("widget_5");
        textEdit_msg = new QTextEdit(widget_5);
        textEdit_msg->setObjectName("textEdit_msg");
        textEdit_msg->setGeometry(QRect(0, 0, 361, 71));

        verticalLayout_3->addWidget(widget_5);

        widget_7 = new QWidget(widget_2);
        widget_7->setObjectName("widget_7");
        btnOk = new QPushButton(widget_7);
        btnOk->setObjectName("btnOk");
        btnOk->setGeometry(QRect(200, 30, 93, 41));

        verticalLayout_3->addWidget(widget_7);


        horizontalLayout->addWidget(widget_2);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);


        retranslateUi(CDlgWifiConfigClass);

        QMetaObject::connectSlotsByName(CDlgWifiConfigClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgWifiConfigClass)
    {
        CDlgWifiConfigClass->setWindowTitle(QCoreApplication::translate("CDlgWifiConfigClass", "CDlgWifiConfig", nullptr));
        label_title->setText(QCoreApplication::translate("CDlgWifiConfigClass", "Wifi\351\200\211\346\213\251", nullptr));
        label_ssid->setText(QCoreApplication::translate("CDlgWifiConfigClass", "ssid", nullptr));
        label_pw->setText(QCoreApplication::translate("CDlgWifiConfigClass", "\345\257\206\347\240\201", nullptr));
        pushButton_detect->setText(QCoreApplication::translate("CDlgWifiConfigClass", "\346\216\242\346\265\213", nullptr));
        pushButton_conn->setText(QCoreApplication::translate("CDlgWifiConfigClass", "\350\277\236\346\216\245", nullptr));
        btnOk->setText(QCoreApplication::translate("CDlgWifiConfigClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgWifiConfigClass: public Ui_CDlgWifiConfigClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGWIFICONFIG_H
