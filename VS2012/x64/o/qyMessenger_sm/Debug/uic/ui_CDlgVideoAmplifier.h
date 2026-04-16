/********************************************************************************
** Form generated from reading UI file 'CDlgVideoAmplifier.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGVIDEOAMPLIFIER_H
#define UI_CDLGVIDEOAMPLIFIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgVideoAmplifierClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lab_title;
    QPushButton *btnAmp_up;
    QPushButton *btnAmp_2;
    QPushButton *btnAmp_3;
    QPushButton *btnAmp_4;
    QPushButton *btnAmp_5;
    QPushButton *btnAmp_6;
    QPushButton *btnAmp_7;
    QPushButton *btnAmp_8;
    QPushButton *btnAmp_9;
    QPushButton *btnAmp_down;
    QPushButton *btnAmp_close;

    void setupUi(QDialog *CDlgVideoAmplifierClass)
    {
        if (CDlgVideoAmplifierClass->objectName().isEmpty())
            CDlgVideoAmplifierClass->setObjectName("CDlgVideoAmplifierClass");
        CDlgVideoAmplifierClass->resize(116, 340);
        horizontalLayout = new QHBoxLayout(CDlgVideoAmplifierClass);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgVideoAmplifierClass);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        lab_title = new QLabel(widget);
        lab_title->setObjectName("lab_title");
        lab_title->setStyleSheet(QString::fromUtf8("font-weight:bold"));

        verticalLayout->addWidget(lab_title);

        btnAmp_up = new QPushButton(widget);
        btnAmp_up->setObjectName("btnAmp_up");

        verticalLayout->addWidget(btnAmp_up);

        btnAmp_2 = new QPushButton(widget);
        btnAmp_2->setObjectName("btnAmp_2");

        verticalLayout->addWidget(btnAmp_2);

        btnAmp_3 = new QPushButton(widget);
        btnAmp_3->setObjectName("btnAmp_3");

        verticalLayout->addWidget(btnAmp_3);

        btnAmp_4 = new QPushButton(widget);
        btnAmp_4->setObjectName("btnAmp_4");

        verticalLayout->addWidget(btnAmp_4);

        btnAmp_5 = new QPushButton(widget);
        btnAmp_5->setObjectName("btnAmp_5");

        verticalLayout->addWidget(btnAmp_5);

        btnAmp_6 = new QPushButton(widget);
        btnAmp_6->setObjectName("btnAmp_6");

        verticalLayout->addWidget(btnAmp_6);

        btnAmp_7 = new QPushButton(widget);
        btnAmp_7->setObjectName("btnAmp_7");

        verticalLayout->addWidget(btnAmp_7);

        btnAmp_8 = new QPushButton(widget);
        btnAmp_8->setObjectName("btnAmp_8");

        verticalLayout->addWidget(btnAmp_8);

        btnAmp_9 = new QPushButton(widget);
        btnAmp_9->setObjectName("btnAmp_9");

        verticalLayout->addWidget(btnAmp_9);

        btnAmp_down = new QPushButton(widget);
        btnAmp_down->setObjectName("btnAmp_down");

        verticalLayout->addWidget(btnAmp_down);

        btnAmp_close = new QPushButton(widget);
        btnAmp_close->setObjectName("btnAmp_close");

        verticalLayout->addWidget(btnAmp_close);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgVideoAmplifierClass);

        QMetaObject::connectSlotsByName(CDlgVideoAmplifierClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgVideoAmplifierClass)
    {
        CDlgVideoAmplifierClass->setWindowTitle(QCoreApplication::translate("CDlgVideoAmplifierClass", "CDlgVideoAmplifier", nullptr));
        lab_title->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "\346\255\243\345\234\250\345\217\221\350\250\200\345\210\227\350\241\250", nullptr));
        btnAmp_up->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "\344\270\212\344\270\200\351\241\265", nullptr));
        btnAmp_2->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_3->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_4->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_5->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_6->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_7->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_8->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_9->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "PushButton", nullptr));
        btnAmp_down->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "\344\270\213\344\270\200\351\241\265", nullptr));
        btnAmp_close->setText(QCoreApplication::translate("CDlgVideoAmplifierClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgVideoAmplifierClass: public Ui_CDlgVideoAmplifierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGVIDEOAMPLIFIER_H
