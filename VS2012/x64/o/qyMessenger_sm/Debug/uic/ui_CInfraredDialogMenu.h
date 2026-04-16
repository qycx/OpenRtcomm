/********************************************************************************
** Form generated from reading UI file 'CInfraredDialogMenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CINFRAREDDIALOGMENU_H
#define UI_CINFRAREDDIALOGMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CInfraredDialogMenuClass
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *menuBtn1;
    QPushButton *btnVideo;
    QPushButton *btnAudio;
    QPushButton *menuBtn2;
    QPushButton *menuChairman;
    QPushButton *menuBtnAmplifier;
    QPushButton *menuBtnAmplifierClose;
    QPushButton *menuBtn3;
    QPushButton *menuBtn5;
    QPushButton *menuSetting;
    QPushButton *menuP2p;
    QPushButton *PortSetting;
    QPushButton *menuShare;
    QPushButton *menuBtn4;
    QPushButton *menuBtn6;
    QPushButton *menuPoint;
    QPushButton *menuResolution;
    QPushButton *btnLogOut;
    QPushButton *menuOther;
    QPushButton *menuDebug;
    QPushButton *menuRestart;
    QPushButton *menuShutdown;

    void setupUi(QDialog *CInfraredDialogMenuClass)
    {
        if (CInfraredDialogMenuClass->objectName().isEmpty())
            CInfraredDialogMenuClass->setObjectName("CInfraredDialogMenuClass");
        CInfraredDialogMenuClass->resize(119, 608);
        verticalLayout = new QVBoxLayout(CInfraredDialogMenuClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CInfraredDialogMenuClass);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        widget->setSizeIncrement(QSize(0, 0));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        menuBtn1 = new QPushButton(widget);
        menuBtn1->setObjectName("menuBtn1");

        verticalLayout_2->addWidget(menuBtn1, 0, Qt::AlignHCenter);

        btnVideo = new QPushButton(widget);
        btnVideo->setObjectName("btnVideo");

        verticalLayout_2->addWidget(btnVideo);

        btnAudio = new QPushButton(widget);
        btnAudio->setObjectName("btnAudio");

        verticalLayout_2->addWidget(btnAudio);

        menuBtn2 = new QPushButton(widget);
        menuBtn2->setObjectName("menuBtn2");

        verticalLayout_2->addWidget(menuBtn2, 0, Qt::AlignHCenter);

        menuChairman = new QPushButton(widget);
        menuChairman->setObjectName("menuChairman");

        verticalLayout_2->addWidget(menuChairman);

        menuBtnAmplifier = new QPushButton(widget);
        menuBtnAmplifier->setObjectName("menuBtnAmplifier");

        verticalLayout_2->addWidget(menuBtnAmplifier);

        menuBtnAmplifierClose = new QPushButton(widget);
        menuBtnAmplifierClose->setObjectName("menuBtnAmplifierClose");

        verticalLayout_2->addWidget(menuBtnAmplifierClose);

        menuBtn3 = new QPushButton(widget);
        menuBtn3->setObjectName("menuBtn3");

        verticalLayout_2->addWidget(menuBtn3, 0, Qt::AlignHCenter);

        menuBtn5 = new QPushButton(widget);
        menuBtn5->setObjectName("menuBtn5");

        verticalLayout_2->addWidget(menuBtn5);

        menuSetting = new QPushButton(widget);
        menuSetting->setObjectName("menuSetting");

        verticalLayout_2->addWidget(menuSetting);

        menuP2p = new QPushButton(widget);
        menuP2p->setObjectName("menuP2p");

        verticalLayout_2->addWidget(menuP2p);

        PortSetting = new QPushButton(widget);
        PortSetting->setObjectName("PortSetting");

        verticalLayout_2->addWidget(PortSetting);

        menuShare = new QPushButton(widget);
        menuShare->setObjectName("menuShare");

        verticalLayout_2->addWidget(menuShare);

        menuBtn4 = new QPushButton(widget);
        menuBtn4->setObjectName("menuBtn4");

        verticalLayout_2->addWidget(menuBtn4, 0, Qt::AlignHCenter);

        menuBtn6 = new QPushButton(widget);
        menuBtn6->setObjectName("menuBtn6");

        verticalLayout_2->addWidget(menuBtn6);

        menuPoint = new QPushButton(widget);
        menuPoint->setObjectName("menuPoint");

        verticalLayout_2->addWidget(menuPoint);

        menuResolution = new QPushButton(widget);
        menuResolution->setObjectName("menuResolution");

        verticalLayout_2->addWidget(menuResolution);

        btnLogOut = new QPushButton(widget);
        btnLogOut->setObjectName("btnLogOut");

        verticalLayout_2->addWidget(btnLogOut);

        menuOther = new QPushButton(widget);
        menuOther->setObjectName("menuOther");

        verticalLayout_2->addWidget(menuOther);

        menuDebug = new QPushButton(widget);
        menuDebug->setObjectName("menuDebug");

        verticalLayout_2->addWidget(menuDebug);

        menuRestart = new QPushButton(widget);
        menuRestart->setObjectName("menuRestart");

        verticalLayout_2->addWidget(menuRestart);

        menuShutdown = new QPushButton(widget);
        menuShutdown->setObjectName("menuShutdown");

        verticalLayout_2->addWidget(menuShutdown);


        verticalLayout->addWidget(widget);


        retranslateUi(CInfraredDialogMenuClass);

        QMetaObject::connectSlotsByName(CInfraredDialogMenuClass);
    } // setupUi

    void retranslateUi(QDialog *CInfraredDialogMenuClass)
    {
        CInfraredDialogMenuClass->setWindowTitle(QCoreApplication::translate("CInfraredDialogMenuClass", "CInfraredQialogMenu", nullptr));
        menuBtn1->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\350\217\234\345\215\225\344\270\200", nullptr));
        btnVideo->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\274\200\345\220\257\346\221\204\345\203\217\345\244\264", nullptr));
        btnAudio->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\274\200\345\220\257\351\272\246\345\205\213\351\243\216", nullptr));
        menuBtn2->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\350\217\234\345\215\225\344\272\214", nullptr));
        menuChairman->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\344\270\273\345\270\255\345\270\203\345\261\200", nullptr));
        menuBtnAmplifier->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\347\224\273\351\235\242\346\224\276\345\244\247", nullptr));
        menuBtnAmplifierClose->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\217\226\346\266\210\347\224\273\351\235\242\346\224\276\345\244\247", nullptr));
        menuBtn3->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\350\217\234\345\215\225\344\270\211", nullptr));
        menuBtn5->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\350\217\234\345\215\225\344\272\224", nullptr));
        menuSetting->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\210\235\345\247\213\345\214\226\350\256\276\347\275\256", nullptr));
        menuP2p->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\347\202\271\345\257\271\347\202\271\344\274\232\350\256\256", nullptr));
        PortSetting->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\347\253\257\345\217\243\350\256\276\347\275\256", nullptr));
        menuShare->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\346\211\223\345\274\200\345\205\261\344\272\253", nullptr));
        menuBtn4->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\350\217\234\345\215\225\345\233\233", nullptr));
        menuBtn6->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\350\217\234\345\215\225\345\205\255", nullptr));
        menuPoint->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\347\202\271\345\257\271\347\202\271\344\274\232\350\256\256", nullptr));
        menuResolution->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\210\206\350\276\250\347\216\207\351\200\202\345\272\224", nullptr));
        btnLogOut->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        menuOther->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\205\266\345\256\203\350\256\276\347\275\256", nullptr));
        menuDebug->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\346\211\223\345\274\200\350\260\203\350\257\225\347\252\227\345\217\243", nullptr));
        menuRestart->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\351\207\215\345\220\257", nullptr));
        menuShutdown->setText(QCoreApplication::translate("CInfraredDialogMenuClass", "\345\205\263\346\234\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CInfraredDialogMenuClass: public Ui_CInfraredDialogMenuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CINFRAREDDIALOGMENU_H
