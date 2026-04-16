/********************************************************************************
** Form generated from reading UI file 'CDlgP2pMsg.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGP2PMSG_H
#define UI_CDLGP2PMSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgP2pMsgClass
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *lab_txt;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_consent;
    QPushButton *btn_repulse;

    void setupUi(QDialog *CDlgP2pMsgClass)
    {
        if (CDlgP2pMsgClass->objectName().isEmpty())
            CDlgP2pMsgClass->setObjectName("CDlgP2pMsgClass");
        CDlgP2pMsgClass->resize(417, 218);
        verticalLayout = new QVBoxLayout(CDlgP2pMsgClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgP2pMsgClass);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lab_txt = new QLabel(widget_2);
        lab_txt->setObjectName("lab_txt");

        verticalLayout_3->addWidget(lab_txt, 0, Qt::AlignHCenter);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        btn_consent = new QPushButton(widget_3);
        btn_consent->setObjectName("btn_consent");

        horizontalLayout->addWidget(btn_consent);

        btn_repulse = new QPushButton(widget_3);
        btn_repulse->setObjectName("btn_repulse");

        horizontalLayout->addWidget(btn_repulse);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);


        retranslateUi(CDlgP2pMsgClass);

        QMetaObject::connectSlotsByName(CDlgP2pMsgClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgP2pMsgClass)
    {
        CDlgP2pMsgClass->setWindowTitle(QCoreApplication::translate("CDlgP2pMsgClass", "CDlgP2pMsg", nullptr));
        lab_txt->setText(QCoreApplication::translate("CDlgP2pMsgClass", "\345\217\221\350\265\267\345\205\245\344\274\232\351\202\200\350\257\267", nullptr));
        btn_consent->setText(QCoreApplication::translate("CDlgP2pMsgClass", "\346\216\245\345\220\254", nullptr));
        btn_repulse->setText(QCoreApplication::translate("CDlgP2pMsgClass", "\346\213\222\347\273\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgP2pMsgClass: public Ui_CDlgP2pMsgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGP2PMSG_H
