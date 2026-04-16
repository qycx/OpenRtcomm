/********************************************************************************
** Form generated from reading UI file 'WinSerConfig.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSERCONFIG_H
#define UI_WINSERCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSerConfig
{
public:
    QWidget *titlewidget;
    QLabel *LabelConfTitle;
    QWidget *bodywidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *serviceName;
    QLabel *label_3;
    QLineEdit *addr1;
    QLabel *label_5;
    QLineEdit *port;
    QTableWidget *tableWidget;
    QPushButton *addBtn;
    QPushButton *saveBtn;
    QPushButton *cancelBtn;
    QLabel *uuid;

    void setupUi(QWidget *WinSerConfig)
    {
        if (WinSerConfig->objectName().isEmpty())
            WinSerConfig->setObjectName("WinSerConfig");
        WinSerConfig->resize(548, 453);
        titlewidget = new QWidget(WinSerConfig);
        titlewidget->setObjectName("titlewidget");
        titlewidget->setGeometry(QRect(-1, -1, 731, 81));
        titlewidget->setProperty("titleskin", QVariant(true));
        LabelConfTitle = new QLabel(titlewidget);
        LabelConfTitle->setObjectName("LabelConfTitle");
        LabelConfTitle->setGeometry(QRect(50, 20, 371, 49));
        bodywidget = new QWidget(WinSerConfig);
        bodywidget->setObjectName("bodywidget");
        bodywidget->setGeometry(QRect(-1, 79, 741, 431));
        bodywidget->setProperty("bottomskin", QVariant(true));
        formLayoutWidget = new QWidget(bodywidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(40, 20, 431, 111));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        serviceName = new QLineEdit(formLayoutWidget);
        serviceName->setObjectName("serviceName");

        formLayout->setWidget(0, QFormLayout::FieldRole, serviceName);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        addr1 = new QLineEdit(formLayoutWidget);
        addr1->setObjectName("addr1");

        formLayout->setWidget(1, QFormLayout::FieldRole, addr1);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName("label_5");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        port = new QLineEdit(formLayoutWidget);
        port->setObjectName("port");

        formLayout->setWidget(2, QFormLayout::FieldRole, port);

        tableWidget = new QTableWidget(bodywidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 180, 501, 171));
        addBtn = new QPushButton(bodywidget);
        addBtn->setObjectName("addBtn");
        addBtn->setGeometry(QRect(90, 140, 93, 29));
        saveBtn = new QPushButton(bodywidget);
        saveBtn->setObjectName("saveBtn");
        saveBtn->setGeometry(QRect(210, 140, 93, 29));
        cancelBtn = new QPushButton(bodywidget);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setEnabled(true);
        cancelBtn->setGeometry(QRect(330, 140, 93, 29));
        uuid = new QLabel(bodywidget);
        uuid->setObjectName("uuid");
        uuid->setEnabled(true);
        uuid->setGeometry(QRect(130, 0, 90, 25));

        retranslateUi(WinSerConfig);

        QMetaObject::connectSlotsByName(WinSerConfig);
    } // setupUi

    void retranslateUi(QWidget *WinSerConfig)
    {
        WinSerConfig->setWindowTitle(QCoreApplication::translate("WinSerConfig", "Form", nullptr));
        LabelConfTitle->setText(QCoreApplication::translate("WinSerConfig", "\347\274\272\347\234\201\346\234\215\345\212\241\345\231\250\351\205\215\347\275\256\357\274\210IP\346\210\226\345\237\237\345\220\215\357\274\211", nullptr));
        label->setText(QCoreApplication::translate("WinSerConfig", "\346\234\215\345\212\241\345\231\250\346\217\217\350\277\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("WinSerConfig", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200(IP)\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("WinSerConfig", "\347\253\257\345\217\243\357\274\232", nullptr));
        port->setText(QCoreApplication::translate("WinSerConfig", "8768", nullptr));
        addBtn->setText(QCoreApplication::translate("WinSerConfig", "\346\226\260 \345\242\236", nullptr));
        saveBtn->setText(QCoreApplication::translate("WinSerConfig", "\347\241\256 \350\256\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("WinSerConfig", "\345\217\226 \346\266\210", nullptr));
        uuid->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WinSerConfig: public Ui_WinSerConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSERCONFIG_H
