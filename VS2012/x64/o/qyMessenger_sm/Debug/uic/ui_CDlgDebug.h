/********************************************************************************
** Form generated from reading UI file 'CDlgDebug.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGDEBUG_H
#define UI_CDLGDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgDebugClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *meeting_lab;
    QLabel *meetingCompere;
    QLabel *meetingConvener;
    QLabel *meetingType;
    QLabel *localIpStr;
    QLabel *str1stMcu;
    QLabel *str2ndMcu;
    QLabel *confMcu;
    QLabel *meetingId;
    QLabel *diskSize;
    QLabel *io;
    QLabel *packet;
    QLabel *version;
    QLabel *isNv;
    QLabel *meetingStartTime;
    QLabel *meetingDurationInMin;
    QLabel *idInfo;
    QLabel *commEnc;
    QLabel *fps;
    QLabel *meeting_item3;
    QLabel *meeting_lab2;
    QLabel *meeting_item2;
    QLabel *meeting_item1;
    QLabel *audioDeviceIn;
    QLabel *audioDeviceOut;

    void setupUi(QDialog *CDlgDebugClass)
    {
        if (CDlgDebugClass->objectName().isEmpty())
            CDlgDebugClass->setObjectName("CDlgDebugClass");
        CDlgDebugClass->resize(600, 446);
        horizontalLayout = new QHBoxLayout(CDlgDebugClass);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgDebugClass);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        meeting_lab = new QLabel(widget);
        meeting_lab->setObjectName("meeting_lab");

        verticalLayout->addWidget(meeting_lab);

        meetingCompere = new QLabel(widget);
        meetingCompere->setObjectName("meetingCompere");

        verticalLayout->addWidget(meetingCompere);

        meetingConvener = new QLabel(widget);
        meetingConvener->setObjectName("meetingConvener");

        verticalLayout->addWidget(meetingConvener);

        meetingType = new QLabel(widget);
        meetingType->setObjectName("meetingType");

        verticalLayout->addWidget(meetingType);

        localIpStr = new QLabel(widget);
        localIpStr->setObjectName("localIpStr");

        verticalLayout->addWidget(localIpStr);

        str1stMcu = new QLabel(widget);
        str1stMcu->setObjectName("str1stMcu");

        verticalLayout->addWidget(str1stMcu);

        str2ndMcu = new QLabel(widget);
        str2ndMcu->setObjectName("str2ndMcu");

        verticalLayout->addWidget(str2ndMcu);

        confMcu = new QLabel(widget);
        confMcu->setObjectName("confMcu");

        verticalLayout->addWidget(confMcu);

        meetingId = new QLabel(widget);
        meetingId->setObjectName("meetingId");

        verticalLayout->addWidget(meetingId);

        diskSize = new QLabel(widget);
        diskSize->setObjectName("diskSize");

        verticalLayout->addWidget(diskSize);

        io = new QLabel(widget);
        io->setObjectName("io");

        verticalLayout->addWidget(io);

        packet = new QLabel(widget);
        packet->setObjectName("packet");

        verticalLayout->addWidget(packet);

        version = new QLabel(widget);
        version->setObjectName("version");

        verticalLayout->addWidget(version);

        isNv = new QLabel(widget);
        isNv->setObjectName("isNv");

        verticalLayout->addWidget(isNv);

        meetingStartTime = new QLabel(widget);
        meetingStartTime->setObjectName("meetingStartTime");

        verticalLayout->addWidget(meetingStartTime);

        meetingDurationInMin = new QLabel(widget);
        meetingDurationInMin->setObjectName("meetingDurationInMin");

        verticalLayout->addWidget(meetingDurationInMin);

        idInfo = new QLabel(widget);
        idInfo->setObjectName("idInfo");

        verticalLayout->addWidget(idInfo);

        commEnc = new QLabel(widget);
        commEnc->setObjectName("commEnc");

        verticalLayout->addWidget(commEnc);

        fps = new QLabel(widget);
        fps->setObjectName("fps");

        verticalLayout->addWidget(fps);

        meeting_item3 = new QLabel(widget);
        meeting_item3->setObjectName("meeting_item3");

        verticalLayout->addWidget(meeting_item3);

        meeting_lab2 = new QLabel(widget);
        meeting_lab2->setObjectName("meeting_lab2");

        verticalLayout->addWidget(meeting_lab2);

        meeting_item2 = new QLabel(widget);
        meeting_item2->setObjectName("meeting_item2");

        verticalLayout->addWidget(meeting_item2);

        meeting_item1 = new QLabel(widget);
        meeting_item1->setObjectName("meeting_item1");

        verticalLayout->addWidget(meeting_item1);

        audioDeviceIn = new QLabel(widget);
        audioDeviceIn->setObjectName("audioDeviceIn");

        verticalLayout->addWidget(audioDeviceIn);

        audioDeviceOut = new QLabel(widget);
        audioDeviceOut->setObjectName("audioDeviceOut");

        verticalLayout->addWidget(audioDeviceOut);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgDebugClass);

        QMetaObject::connectSlotsByName(CDlgDebugClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgDebugClass)
    {
        CDlgDebugClass->setWindowTitle(QCoreApplication::translate("CDlgDebugClass", "CDlgDebug", nullptr));
        meeting_lab->setText(QCoreApplication::translate("CDlgDebugClass", "11111111111", nullptr));
        meetingCompere->setText(QCoreApplication::translate("CDlgDebugClass", "222222222222222", nullptr));
        meetingConvener->setText(QCoreApplication::translate("CDlgDebugClass", "\344\274\232\350\256\256\345\217\254\351\233\206\344\272\272", nullptr));
        meetingType->setText(QCoreApplication::translate("CDlgDebugClass", "33333333333333", nullptr));
        localIpStr->setText(QCoreApplication::translate("CDlgDebugClass", "444444444", nullptr));
        str1stMcu->setText(QCoreApplication::translate("CDlgDebugClass", "5555555555555555", nullptr));
        str2ndMcu->setText(QCoreApplication::translate("CDlgDebugClass", "777777777777", nullptr));
        confMcu->setText(QCoreApplication::translate("CDlgDebugClass", "999999999999999999", nullptr));
        meetingId->setText(QCoreApplication::translate("CDlgDebugClass", "6666666666666666", nullptr));
        diskSize->setText(QCoreApplication::translate("CDlgDebugClass", "88888888888888888", nullptr));
        io->setText(QCoreApplication::translate("CDlgDebugClass", "io", nullptr));
        packet->setText(QCoreApplication::translate("CDlgDebugClass", "\344\270\242\345\214\205\347\216\207", nullptr));
        version->setText(QCoreApplication::translate("CDlgDebugClass", "\347\211\210\346\234\254", nullptr));
        isNv->setText(QCoreApplication::translate("CDlgDebugClass", "\347\274\226\350\247\243\347\240\201\346\226\271\345\274\217", nullptr));
        meetingStartTime->setText(QCoreApplication::translate("CDlgDebugClass", "1010010101010", nullptr));
        meetingDurationInMin->setText(QCoreApplication::translate("CDlgDebugClass", "12121212121", nullptr));
        idInfo->setText(QCoreApplication::translate("CDlgDebugClass", "1313131313131", nullptr));
        commEnc->setText(QCoreApplication::translate("CDlgDebugClass", "14141414144141", nullptr));
        fps->setText(QCoreApplication::translate("CDlgDebugClass", "1515151515", nullptr));
        meeting_item3->setText(QCoreApplication::translate("CDlgDebugClass", "1616161616", nullptr));
        meeting_lab2->setText(QCoreApplication::translate("CDlgDebugClass", "171717171717", nullptr));
        meeting_item2->setText(QCoreApplication::translate("CDlgDebugClass", "18181818118", nullptr));
        meeting_item1->setText(QCoreApplication::translate("CDlgDebugClass", "1919191919", nullptr));
        audioDeviceIn->setText(QCoreApplication::translate("CDlgDebugClass", "\345\267\262\351\200\211\351\272\246\345\205\213\351\243\216\350\256\276\345\244\207", nullptr));
        audioDeviceOut->setText(QCoreApplication::translate("CDlgDebugClass", "\345\267\262\351\200\211\345\226\207\345\217\255\350\256\276\345\244\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgDebugClass: public Ui_CDlgDebugClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGDEBUG_H
