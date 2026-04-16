/********************************************************************************
** Form generated from reading UI file 'CDlgP2p.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGP2P_H
#define UI_CDLGP2P_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgP2pClass
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lab_title;
    QPushButton *btnP2p_up;
    QPushButton *btnP2p_2;
    QPushButton *btnP2p_3;
    QPushButton *btnP2p_4;
    QPushButton *btnP2p_5;
    QPushButton *btnP2p_6;
    QPushButton *btnP2p_7;
    QPushButton *btnP2p_8;
    QPushButton *btnP2p_9;
    QPushButton *btnP2p_down;
    QPushButton *btnP2p_close;

    void setupUi(QDialog *CDlgP2pClass)
    {
        if (CDlgP2pClass->objectName().isEmpty())
            CDlgP2pClass->setObjectName("CDlgP2pClass");
        CDlgP2pClass->resize(134, 345);
        verticalLayout = new QVBoxLayout(CDlgP2pClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgP2pClass);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(11, -1, 11, -1);
        lab_title = new QLabel(widget);
        lab_title->setObjectName("lab_title");
        lab_title->setMaximumSize(QSize(16777215, 30));
        lab_title->setStyleSheet(QString::fromUtf8("font-weight:bold"));

        verticalLayout_2->addWidget(lab_title);

        btnP2p_up = new QPushButton(widget);
        btnP2p_up->setObjectName("btnP2p_up");

        verticalLayout_2->addWidget(btnP2p_up);

        btnP2p_2 = new QPushButton(widget);
        btnP2p_2->setObjectName("btnP2p_2");

        verticalLayout_2->addWidget(btnP2p_2);

        btnP2p_3 = new QPushButton(widget);
        btnP2p_3->setObjectName("btnP2p_3");

        verticalLayout_2->addWidget(btnP2p_3);

        btnP2p_4 = new QPushButton(widget);
        btnP2p_4->setObjectName("btnP2p_4");

        verticalLayout_2->addWidget(btnP2p_4);

        btnP2p_5 = new QPushButton(widget);
        btnP2p_5->setObjectName("btnP2p_5");

        verticalLayout_2->addWidget(btnP2p_5);

        btnP2p_6 = new QPushButton(widget);
        btnP2p_6->setObjectName("btnP2p_6");

        verticalLayout_2->addWidget(btnP2p_6);

        btnP2p_7 = new QPushButton(widget);
        btnP2p_7->setObjectName("btnP2p_7");

        verticalLayout_2->addWidget(btnP2p_7);

        btnP2p_8 = new QPushButton(widget);
        btnP2p_8->setObjectName("btnP2p_8");

        verticalLayout_2->addWidget(btnP2p_8);

        btnP2p_9 = new QPushButton(widget);
        btnP2p_9->setObjectName("btnP2p_9");

        verticalLayout_2->addWidget(btnP2p_9);

        btnP2p_down = new QPushButton(widget);
        btnP2p_down->setObjectName("btnP2p_down");

        verticalLayout_2->addWidget(btnP2p_down);

        btnP2p_close = new QPushButton(widget);
        btnP2p_close->setObjectName("btnP2p_close");

        verticalLayout_2->addWidget(btnP2p_close);


        verticalLayout->addWidget(widget);


        retranslateUi(CDlgP2pClass);

        QMetaObject::connectSlotsByName(CDlgP2pClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgP2pClass)
    {
        CDlgP2pClass->setWindowTitle(QCoreApplication::translate("CDlgP2pClass", "CDlgP2p", nullptr));
        lab_title->setText(QCoreApplication::translate("CDlgP2pClass", "\347\202\271\345\257\271\347\202\271\344\274\232\350\256\256\345\210\227\350\241\250", nullptr));
        btnP2p_up->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton1", nullptr));
        btnP2p_2->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton2", nullptr));
        btnP2p_3->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton3", nullptr));
        btnP2p_4->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton4", nullptr));
        btnP2p_5->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton5", nullptr));
        btnP2p_6->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton6", nullptr));
        btnP2p_7->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton7", nullptr));
        btnP2p_8->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton8", nullptr));
        btnP2p_9->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton9", nullptr));
        btnP2p_down->setText(QCoreApplication::translate("CDlgP2pClass", "PushButton10", nullptr));
        btnP2p_close->setText(QCoreApplication::translate("CDlgP2pClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgP2pClass: public Ui_CDlgP2pClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGP2P_H
