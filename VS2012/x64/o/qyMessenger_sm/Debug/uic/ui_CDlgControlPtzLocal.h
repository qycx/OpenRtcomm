/********************************************************************************
** Form generated from reading UI file 'CDlgControlPtzLocal.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGCONTROLPTZLOCAL_H
#define UI_CDLGCONTROLPTZLOCAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgControlPtzLocalClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lab_title;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnPtz_up;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnPtz_left;
    QPushButton *btnPtz_right;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btnPtz_down;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnPtz_zoomUp;
    QPushButton *btnPtz_zoomDown;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnPtz_focusUp;
    QPushButton *btnPtz_focusDown;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnPtz_haloUp;
    QPushButton *btnPtz_haloDown;
    QWidget *widget_8;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btnPtz_close;

    void setupUi(QDialog *CDlgControlPtzLocalClass)
    {
        if (CDlgControlPtzLocalClass->objectName().isEmpty())
            CDlgControlPtzLocalClass->setObjectName("CDlgControlPtzLocalClass");
        CDlgControlPtzLocalClass->resize(208, 314);
        horizontalLayout = new QHBoxLayout(CDlgControlPtzLocalClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(CDlgControlPtzLocalClass);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lab_title = new QLabel(widget);
        lab_title->setObjectName("lab_title");
        lab_title->setStyleSheet(QString::fromUtf8("font-weight:bold"));

        verticalLayout->addWidget(lab_title);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        verticalLayout_5 = new QVBoxLayout(widget_2);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        btnPtz_up = new QPushButton(widget_2);
        btnPtz_up->setObjectName("btnPtz_up");

        verticalLayout_5->addWidget(btnPtz_up);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnPtz_left = new QPushButton(widget_3);
        btnPtz_left->setObjectName("btnPtz_left");

        horizontalLayout_2->addWidget(btnPtz_left);

        btnPtz_right = new QPushButton(widget_3);
        btnPtz_right->setObjectName("btnPtz_right");

        horizontalLayout_2->addWidget(btnPtz_right);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        verticalLayout_6 = new QVBoxLayout(widget_4);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        btnPtz_down = new QPushButton(widget_4);
        btnPtz_down->setObjectName("btnPtz_down");

        verticalLayout_6->addWidget(btnPtz_down);


        verticalLayout->addWidget(widget_4);

        widget_7 = new QWidget(widget);
        widget_7->setObjectName("widget_7");
        verticalLayout_2 = new QVBoxLayout(widget_7);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnPtz_zoomUp = new QPushButton(widget_7);
        btnPtz_zoomUp->setObjectName("btnPtz_zoomUp");

        verticalLayout_2->addWidget(btnPtz_zoomUp);

        btnPtz_zoomDown = new QPushButton(widget_7);
        btnPtz_zoomDown->setObjectName("btnPtz_zoomDown");

        verticalLayout_2->addWidget(btnPtz_zoomDown);


        verticalLayout->addWidget(widget_7);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName("widget_6");
        verticalLayout_3 = new QVBoxLayout(widget_6);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnPtz_focusUp = new QPushButton(widget_6);
        btnPtz_focusUp->setObjectName("btnPtz_focusUp");

        verticalLayout_3->addWidget(btnPtz_focusUp);

        btnPtz_focusDown = new QPushButton(widget_6);
        btnPtz_focusDown->setObjectName("btnPtz_focusDown");

        verticalLayout_3->addWidget(btnPtz_focusDown);


        verticalLayout->addWidget(widget_6);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        btnPtz_haloUp = new QPushButton(widget_5);
        btnPtz_haloUp->setObjectName("btnPtz_haloUp");

        verticalLayout_4->addWidget(btnPtz_haloUp);

        btnPtz_haloDown = new QPushButton(widget_5);
        btnPtz_haloDown->setObjectName("btnPtz_haloDown");

        verticalLayout_4->addWidget(btnPtz_haloDown);


        verticalLayout->addWidget(widget_5);

        widget_8 = new QWidget(widget);
        widget_8->setObjectName("widget_8");
        verticalLayout_7 = new QVBoxLayout(widget_8);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        btnPtz_close = new QPushButton(widget_8);
        btnPtz_close->setObjectName("btnPtz_close");

        verticalLayout_7->addWidget(btnPtz_close);


        verticalLayout->addWidget(widget_8);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgControlPtzLocalClass);

        QMetaObject::connectSlotsByName(CDlgControlPtzLocalClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgControlPtzLocalClass)
    {
        CDlgControlPtzLocalClass->setWindowTitle(QCoreApplication::translate("CDlgControlPtzLocalClass", "CDlgControlPtzLocal", nullptr));
        lab_title->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\346\234\254\345\234\260\344\272\221\345\217\260\346\216\247\345\210\266", nullptr));
        btnPtz_up->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\344\270\212", nullptr));
        btnPtz_left->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\267\246", nullptr));
        btnPtz_right->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\217\263", nullptr));
        btnPtz_down->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\344\270\213", nullptr));
        btnPtz_zoomUp->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\217\230\345\200\215+", nullptr));
        btnPtz_zoomDown->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\217\230\345\200\215-", nullptr));
        btnPtz_focusUp->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\350\201\232\347\204\246+", nullptr));
        btnPtz_focusDown->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\350\201\232\347\204\246-", nullptr));
        btnPtz_haloUp->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\205\211\345\234\210+", nullptr));
        btnPtz_haloDown->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\205\211\345\234\210-", nullptr));
        btnPtz_close->setText(QCoreApplication::translate("CDlgControlPtzLocalClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgControlPtzLocalClass: public Ui_CDlgControlPtzLocalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGCONTROLPTZLOCAL_H
