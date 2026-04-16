/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_qt.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_QT_H
#define UI_CDLGTALK_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <WinMsgShow.h>
#include "WinMsgQTextEdit.h"

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_qt
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *conferenceController;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QLabel *labMaxCount;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *speakList;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labLoad;
    QLineEdit *lineSearch;
    QTableWidget *tableWidget;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labCompere;
    QLabel *labInitiator;
    QWidget *widgetMsgArea;
    QGridLayout *gridLayout_2;
    QWidget *ContactsInfo_chat;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelContactsInfo_chat;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnContactsInfo;
    QStackedWidget *stackedWidgetInfo;
    QWidget *pageContactsInfo;
    QGridLayout *gridLayout_5;
    QPushButton *btnMem;
    QPushButton *btnGrpDel;
    QLabel *labCreator;
    QFrame *lineContactInfo;
    QLabel *labelGroup;
    QPushButton *headIcoBtn;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelMsgID;
    QLabel *labelName;
    QPushButton *btnRule;
    QWidget *widgetMsgSend;
    QVBoxLayout *verticalLayout_3;
    WinMsgShow *widgetMsgShow;
    QWidget *sendMsgInfo;
    QGridLayout *gridLayout;
    QPushButton *btnFace;
    QPushButton *btnFileSend;
    QPushButton *btnDisk;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnVideo;
    WinMsgQTextEdit *sendMsg;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_10;
    QToolButton *btnSendImg;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetVideoShow;
    QWidget *peerDesc;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer;
    QWidget *otherDesc;
    QWidget *meDesc;
    QLabel *lab_io;
    QSpacerItem *horizontalSpacer_11;
    QWidget *bottomMenu;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_6;
    QLabel *user_val;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *duration;
    QLabel *duration_val;
    QWidget *isRecord;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *recordImg;
    QLabel *lable_t10;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lab_t1;
    QLabel *rate;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lab_t2;
    QLabel *loss;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btn_img1;
    QLabel *lab_t3;

    void setupUi(QWidget *CDlgTalk_qt)
    {
        if (CDlgTalk_qt->objectName().isEmpty())
            CDlgTalk_qt->setObjectName("CDlgTalk_qt");
        CDlgTalk_qt->resize(1945, 833);
        CDlgTalk_qt->setMinimumSize(QSize(0, 0));
        CDlgTalk_qt->setMaximumSize(QSize(16777215, 16777215));
        CDlgTalk_qt->setMouseTracking(true);
        CDlgTalk_qt->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(CDlgTalk_qt);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(CDlgTalk_qt);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        widget->setMouseTracking(true);
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        conferenceController = new QWidget(widget);
        conferenceController->setObjectName("conferenceController");
        conferenceController->setMinimumSize(QSize(400, 0));
        conferenceController->setStyleSheet(QString::fromUtf8("#conferenceController{ \n"
"background:#ffffff;\n"
"border-right:1px solid #000;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(conferenceController);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(conferenceController);
        widget_3->setObjectName("widget_3");
        horizontalLayout_7 = new QHBoxLayout(widget_3);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 10, 10, 0);
        label_3 = new QLabel(widget_3);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font-weight:bold;font-size:16px"));

        horizontalLayout_7->addWidget(label_3);

        labMaxCount = new QLabel(widget_3);
        labMaxCount->setObjectName("labMaxCount");

        horizontalLayout_7->addWidget(labMaxCount, 0, Qt::AlignRight);


        verticalLayout_6->addWidget(widget_3);

        widget_4 = new QWidget(conferenceController);
        widget_4->setObjectName("widget_4");
        verticalLayout_5 = new QVBoxLayout(widget_4);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 10, 0, 0);
        speakList = new QTableWidget(widget_4);
        if (speakList->columnCount() < 4)
            speakList->setColumnCount(4);
        QFont font;
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        speakList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        speakList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        speakList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        speakList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        speakList->setObjectName("speakList");

        verticalLayout_5->addWidget(speakList);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName("widget_2");
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(10, 7, 10, 7);
        labLoad = new QLabel(widget_2);
        labLoad->setObjectName("labLoad");
        labLoad->setStyleSheet(QString::fromUtf8("font-weight:bold;font-size:16px;"));

        horizontalLayout_5->addWidget(labLoad);

        lineSearch = new QLineEdit(widget_2);
        lineSearch->setObjectName("lineSearch");
        lineSearch->setMinimumSize(QSize(200, 0));
        lineSearch->setMaximumSize(QSize(200, 16777215));
        lineSearch->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_5->addWidget(lineSearch);


        verticalLayout_5->addWidget(widget_2);

        tableWidget = new QTableWidget(widget_4);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_5->addWidget(tableWidget);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 0));
        horizontalLayout_6 = new QHBoxLayout(widget_5);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(6, 0, 0, 0);
        labCompere = new QLabel(widget_5);
        labCompere->setObjectName("labCompere");

        horizontalLayout_6->addWidget(labCompere);

        labInitiator = new QLabel(widget_5);
        labInitiator->setObjectName("labInitiator");

        horizontalLayout_6->addWidget(labInitiator);


        verticalLayout_5->addWidget(widget_5, 0, Qt::AlignLeft);


        verticalLayout_6->addWidget(widget_4);


        horizontalLayout_4->addWidget(conferenceController);

        widgetMsgArea = new QWidget(widget);
        widgetMsgArea->setObjectName("widgetMsgArea");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetMsgArea->sizePolicy().hasHeightForWidth());
        widgetMsgArea->setSizePolicy(sizePolicy);
        widgetMsgArea->setMinimumSize(QSize(0, 0));
        widgetMsgArea->setMaximumSize(QSize(16777215, 16777215));
        widgetMsgArea->setMouseTracking(true);
        widgetMsgArea->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(widgetMsgArea);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        ContactsInfo_chat = new QWidget(widgetMsgArea);
        ContactsInfo_chat->setObjectName("ContactsInfo_chat");
        ContactsInfo_chat->setMinimumSize(QSize(0, 60));
        ContactsInfo_chat->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(ContactsInfo_chat);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(26, 0, 0, 0);
        labelContactsInfo_chat = new QLabel(ContactsInfo_chat);
        labelContactsInfo_chat->setObjectName("labelContactsInfo_chat");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelContactsInfo_chat->sizePolicy().hasHeightForWidth());
        labelContactsInfo_chat->setSizePolicy(sizePolicy1);
        labelContactsInfo_chat->setMinimumSize(QSize(250, 20));
        labelContactsInfo_chat->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("AdLib WGL4 BT")});
        font1.setPointSize(8);
        labelContactsInfo_chat->setFont(font1);
        labelContactsInfo_chat->setStyleSheet(QString::fromUtf8(""));
        labelContactsInfo_chat->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(labelContactsInfo_chat);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        btnContactsInfo = new QPushButton(ContactsInfo_chat);
        btnContactsInfo->setObjectName("btnContactsInfo");
        btnContactsInfo->setMinimumSize(QSize(0, 40));
        btnContactsInfo->setMaximumSize(QSize(16777215, 40));
        btnContactsInfo->setFlat(true);

        horizontalLayout_3->addWidget(btnContactsInfo);


        gridLayout_2->addWidget(ContactsInfo_chat, 0, 0, 1, 3);

        stackedWidgetInfo = new QStackedWidget(widgetMsgArea);
        stackedWidgetInfo->setObjectName("stackedWidgetInfo");
        stackedWidgetInfo->setMinimumSize(QSize(200, 0));
        stackedWidgetInfo->setMaximumSize(QSize(200, 16777215));
        stackedWidgetInfo->setMouseTracking(true);
        stackedWidgetInfo->setStyleSheet(QString::fromUtf8("border-left:1px solid #eee"));
        pageContactsInfo = new QWidget();
        pageContactsInfo->setObjectName("pageContactsInfo");
        pageContactsInfo->setMinimumSize(QSize(200, 0));
        pageContactsInfo->setMaximumSize(QSize(200, 16777215));
        pageContactsInfo->setMouseTracking(true);
        gridLayout_5 = new QGridLayout(pageContactsInfo);
        gridLayout_5->setObjectName("gridLayout_5");
        btnMem = new QPushButton(pageContactsInfo);
        btnMem->setObjectName("btnMem");
        btnMem->setMinimumSize(QSize(130, 30));
        btnMem->setStyleSheet(QString::fromUtf8("border:1px solid #999; border-radius:5%;\n"
"background:#fff;"));

        gridLayout_5->addWidget(btnMem, 5, 1, 1, 1);

        btnGrpDel = new QPushButton(pageContactsInfo);
        btnGrpDel->setObjectName("btnGrpDel");
        btnGrpDel->setEnabled(false);
        btnGrpDel->setMinimumSize(QSize(130, 30));
        btnGrpDel->setMaximumSize(QSize(100, 30));
        btnGrpDel->setStyleSheet(QString::fromUtf8("border:1px solid #999; border-radius:5%;\n"
"background:#fff;\n"
"color:#eee;"));

        gridLayout_5->addWidget(btnGrpDel, 10, 1, 1, 1, Qt::AlignHCenter);

        labCreator = new QLabel(pageContactsInfo);
        labCreator->setObjectName("labCreator");
        labCreator->setEnabled(false);

        gridLayout_5->addWidget(labCreator, 9, 1, 1, 2, Qt::AlignLeft);

        lineContactInfo = new QFrame(pageContactsInfo);
        lineContactInfo->setObjectName("lineContactInfo");
        lineContactInfo->setFrameShape(QFrame::Shape::HLine);
        lineContactInfo->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_5->addWidget(lineContactInfo, 4, 0, 1, 4);

        labelGroup = new QLabel(pageContactsInfo);
        labelGroup->setObjectName("labelGroup");
        labelGroup->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(labelGroup, 2, 0, 1, 4);

        headIcoBtn = new QPushButton(pageContactsInfo);
        headIcoBtn->setObjectName("headIcoBtn");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(headIcoBtn->sizePolicy().hasHeightForWidth());
        headIcoBtn->setSizePolicy(sizePolicy2);
        headIcoBtn->setMinimumSize(QSize(55, 55));
        headIcoBtn->setMaximumSize(QSize(55, 55));
        headIcoBtn->setAutoFillBackground(false);
        headIcoBtn->setStyleSheet(QString::fromUtf8("border:none;"));
        headIcoBtn->setProperty("hasborder", QVariant(true));

        gridLayout_5->addWidget(headIcoBtn, 0, 1, 1, 2, Qt::AlignHCenter);

        verticalSpacer_2 = new QSpacerItem(20, 294, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 13, 1, 1, 1);

        labelMsgID = new QLabel(pageContactsInfo);
        labelMsgID->setObjectName("labelMsgID");
        labelMsgID->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(labelMsgID, 3, 0, 1, 4);

        labelName = new QLabel(pageContactsInfo);
        labelName->setObjectName("labelName");
        labelName->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(labelName, 1, 0, 1, 4);

        btnRule = new QPushButton(pageContactsInfo);
        btnRule->setObjectName("btnRule");
        btnRule->setMinimumSize(QSize(130, 30));
        btnRule->setStyleSheet(QString::fromUtf8("border:1px solid #999; border-radius:5%;\n"
"background:#fff;"));

        gridLayout_5->addWidget(btnRule, 6, 1, 1, 2, Qt::AlignLeft);

        stackedWidgetInfo->addWidget(pageContactsInfo);

        gridLayout_2->addWidget(stackedWidgetInfo, 1, 2, 1, 1);

        widgetMsgSend = new QWidget(widgetMsgArea);
        widgetMsgSend->setObjectName("widgetMsgSend");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widgetMsgSend->sizePolicy().hasHeightForWidth());
        widgetMsgSend->setSizePolicy(sizePolicy3);
        widgetMsgSend->setMouseTracking(true);
        verticalLayout_3 = new QVBoxLayout(widgetMsgSend);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetMsgShow = new WinMsgShow(widgetMsgSend);
        widgetMsgShow->setObjectName("widgetMsgShow");
        widgetMsgShow->setAutoFillBackground(false);
        widgetMsgShow->setStyleSheet(QString::fromUtf8("background:rgb(245,245,245);\n"
"border-left:1px solid rgb(160,160,160);"));

        verticalLayout_3->addWidget(widgetMsgShow);

        sendMsgInfo = new QWidget(widgetMsgSend);
        sendMsgInfo->setObjectName("sendMsgInfo");
        sendMsgInfo->setMinimumSize(QSize(0, 197));
        sendMsgInfo->setMaximumSize(QSize(16777215, 197));
        sendMsgInfo->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(sendMsgInfo);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(13);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btnFace = new QPushButton(sendMsgInfo);
        btnFace->setObjectName("btnFace");
        sizePolicy2.setHeightForWidth(btnFace->sizePolicy().hasHeightForWidth());
        btnFace->setSizePolicy(sizePolicy2);
        btnFace->setMinimumSize(QSize(30, 30));
        btnFace->setMaximumSize(QSize(30, 30));
        btnFace->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnFace->setCheckable(true);
        btnFace->setProperty("hasborder", QVariant(true));

        gridLayout->addWidget(btnFace, 0, 0, 1, 1);

        btnFileSend = new QPushButton(sendMsgInfo);
        btnFileSend->setObjectName("btnFileSend");
        btnFileSend->setMinimumSize(QSize(30, 30));
        btnFileSend->setMaximumSize(QSize(30, 30));
        btnFileSend->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(btnFileSend, 0, 1, 1, 1);

        btnDisk = new QPushButton(sendMsgInfo);
        btnDisk->setObjectName("btnDisk");
        btnDisk->setMinimumSize(QSize(30, 30));
        btnDisk->setMaximumSize(QSize(30, 30));
        btnDisk->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnDisk->setStyleSheet(QString::fromUtf8(""));
        btnDisk->setIconSize(QSize(30, 30));

        gridLayout->addWidget(btnDisk, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(168, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 2);

        btnVideo = new QPushButton(sendMsgInfo);
        btnVideo->setObjectName("btnVideo");
        sizePolicy2.setHeightForWidth(btnVideo->sizePolicy().hasHeightForWidth());
        btnVideo->setSizePolicy(sizePolicy2);
        btnVideo->setMinimumSize(QSize(30, 30));
        btnVideo->setMaximumSize(QSize(30, 30));
        btnVideo->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnVideo->setProperty("hasborder", QVariant(true));

        gridLayout->addWidget(btnVideo, 0, 5, 1, 1, Qt::AlignRight);

        sendMsg = new WinMsgQTextEdit(sendMsgInfo);
        sendMsg->setObjectName("sendMsg");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(sendMsg->sizePolicy().hasHeightForWidth());
        sendMsg->setSizePolicy(sizePolicy4);
        sendMsg->setMinimumSize(QSize(0, 100));
        sendMsg->setMaximumSize(QSize(16777215, 100));
        sendMsg->setFocusPolicy(Qt::ClickFocus);
        sendMsg->setStyleSheet(QString::fromUtf8("border:none;"));
        sendMsg->setFrameShape(QFrame::Box);
        sendMsg->setTextInteractionFlags(Qt::TextEditorInteraction);

        gridLayout->addWidget(sendMsg, 1, 0, 1, 6);

        horizontalSpacer = new QSpacerItem(126, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 4);

        horizontalSpacer_10 = new QSpacerItem(151, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 2, 4, 1, 1);

        btnSendImg = new QToolButton(sendMsgInfo);
        btnSendImg->setObjectName("btnSendImg");
        btnSendImg->setMinimumSize(QSize(92, 24));
        btnSendImg->setPopupMode(QToolButton::MenuButtonPopup);
        btnSendImg->setArrowType(Qt::NoArrow);
        btnSendImg->setProperty("titleskin", QVariant(true));

        gridLayout->addWidget(btnSendImg, 2, 5, 1, 1);


        verticalLayout_3->addWidget(sendMsgInfo);


        gridLayout_2->addWidget(widgetMsgSend, 1, 1, 1, 1);


        horizontalLayout_4->addWidget(widgetMsgArea);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, -1, 0, -1);
        widgetVideoShow = new QWidget(widget);
        widgetVideoShow->setObjectName("widgetVideoShow");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(widgetVideoShow->sizePolicy().hasHeightForWidth());
        widgetVideoShow->setSizePolicy(sizePolicy5);
        widgetVideoShow->setMinimumSize(QSize(450, 0));
        widgetVideoShow->setMouseTracking(true);
        peerDesc = new QWidget(widgetVideoShow);
        peerDesc->setObjectName("peerDesc");
        peerDesc->setGeometry(QRect(9, -5, 450, 771));
        sizePolicy3.setHeightForWidth(peerDesc->sizePolicy().hasHeightForWidth());
        peerDesc->setSizePolicy(sizePolicy3);
        peerDesc->setMinimumSize(QSize(450, 500));
        peerDesc->setMaximumSize(QSize(16777215, 16777215));
        peerDesc->setMouseTracking(true);
        peerDesc->setStyleSheet(QString::fromUtf8("background-color:#000;\n"
"\n"
""));
        peerDesc->setProperty("leftbottomskin", QVariant(true));
        gridLayout_6 = new QGridLayout(peerDesc);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(2, 20, 2, 90);
        verticalSpacer = new QSpacerItem(20, 268, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 1, 3, 1, 1);

        otherDesc = new QWidget(peerDesc);
        otherDesc->setObjectName("otherDesc");
        otherDesc->setEnabled(false);
        sizePolicy2.setHeightForWidth(otherDesc->sizePolicy().hasHeightForWidth());
        otherDesc->setSizePolicy(sizePolicy2);
        otherDesc->setMinimumSize(QSize(330, 200));
        otherDesc->setMaximumSize(QSize(330, 200));
        otherDesc->setMouseTracking(true);
        otherDesc->setStyleSheet(QString::fromUtf8("background-color: rgb(219, 255, 240);"));

        gridLayout_6->addWidget(otherDesc, 0, 3, 1, 1);

        meDesc = new QWidget(peerDesc);
        meDesc->setObjectName("meDesc");
        sizePolicy2.setHeightForWidth(meDesc->sizePolicy().hasHeightForWidth());
        meDesc->setSizePolicy(sizePolicy2);
        meDesc->setMinimumSize(QSize(250, 140));
        meDesc->setMaximumSize(QSize(250, 140));
        meDesc->setMouseTracking(true);
        meDesc->setStyleSheet(QString::fromUtf8("background-color: #000;\n"
"padding-bottom:100px;"));

        gridLayout_6->addWidget(meDesc, 2, 3, 1, 1, Qt::AlignRight|Qt::AlignBottom);

        lab_io = new QLabel(peerDesc);
        lab_io->setObjectName("lab_io");
        lab_io->setMinimumSize(QSize(260, 0));
        lab_io->setMaximumSize(QSize(260, 16777215));
        lab_io->setStyleSheet(QString::fromUtf8("color:#fff;"));
        lab_io->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(lab_io, 3, 3, 1, 1, Qt::AlignRight);

        horizontalSpacer_11 = new QSpacerItem(700, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_11, 0, 2, 1, 1);

        bottomMenu = new QWidget(widgetVideoShow);
        bottomMenu->setObjectName("bottomMenu");
        bottomMenu->setGeometry(QRect(0, 780, 744, 80));
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(bottomMenu->sizePolicy().hasHeightForWidth());
        bottomMenu->setSizePolicy(sizePolicy6);
        bottomMenu->setMinimumSize(QSize(0, 65));
        bottomMenu->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(bottomMenu);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 0, 10, 8);
        widget_6 = new QWidget(bottomMenu);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(100, 0));
        user_val = new QLabel(widget_6);
        user_val->setObjectName("user_val");
        user_val->setGeometry(QRect(10, 20, 72, 25));
        user_val->setMinimumSize(QSize(0, 3));

        horizontalLayout->addWidget(widget_6);

        widget_8 = new QWidget(bottomMenu);
        widget_8->setObjectName("widget_8");
        widget_8->setStyleSheet(QString::fromUtf8("background:none;border-radius:10px"));
        horizontalLayout_11 = new QHBoxLayout(widget_8);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        duration = new QLabel(widget_8);
        duration->setObjectName("duration");

        horizontalLayout_11->addWidget(duration);

        duration_val = new QLabel(widget_8);
        duration_val->setObjectName("duration_val");

        horizontalLayout_11->addWidget(duration_val);


        horizontalLayout->addWidget(widget_8);

        isRecord = new QWidget(bottomMenu);
        isRecord->setObjectName("isRecord");
        isRecord->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_13 = new QHBoxLayout(isRecord);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        recordImg = new QPushButton(isRecord);
        recordImg->setObjectName("recordImg");
        recordImg->setMinimumSize(QSize(20, 20));
        recordImg->setMaximumSize(QSize(20, 20));

        horizontalLayout_13->addWidget(recordImg);

        lable_t10 = new QLabel(isRecord);
        lable_t10->setObjectName("lable_t10");

        horizontalLayout_13->addWidget(lable_t10);


        horizontalLayout->addWidget(isRecord);

        widget_11 = new QWidget(bottomMenu);
        widget_11->setObjectName("widget_11");
        widget_11->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_10 = new QHBoxLayout(widget_11);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        lab_t1 = new QLabel(widget_11);
        lab_t1->setObjectName("lab_t1");

        horizontalLayout_10->addWidget(lab_t1);

        rate = new QLabel(widget_11);
        rate->setObjectName("rate");

        horizontalLayout_10->addWidget(rate);


        horizontalLayout->addWidget(widget_11);

        widget_10 = new QWidget(bottomMenu);
        widget_10->setObjectName("widget_10");
        widget_10->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_9 = new QHBoxLayout(widget_10);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        lab_t2 = new QLabel(widget_10);
        lab_t2->setObjectName("lab_t2");

        horizontalLayout_9->addWidget(lab_t2);

        loss = new QLabel(widget_10);
        loss->setObjectName("loss");

        horizontalLayout_9->addWidget(loss);


        horizontalLayout->addWidget(widget_10);

        widget_7 = new QWidget(bottomMenu);
        widget_7->setObjectName("widget_7");
        widget_7->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_8 = new QHBoxLayout(widget_7);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        btn_img1 = new QPushButton(widget_7);
        btn_img1->setObjectName("btn_img1");

        horizontalLayout_8->addWidget(btn_img1);

        lab_t3 = new QLabel(widget_7);
        lab_t3->setObjectName("lab_t3");

        horizontalLayout_8->addWidget(lab_t3);


        horizontalLayout->addWidget(widget_7);


        verticalLayout_2->addWidget(widgetVideoShow);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout->addWidget(widget);


        retranslateUi(CDlgTalk_qt);

        stackedWidgetInfo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CDlgTalk_qt);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_qt)
    {
        CDlgTalk_qt->setWindowTitle(QCoreApplication::translate("CDlgTalk_qt", "\350\247\206\351\242\221", nullptr));
        label_3->setText(QCoreApplication::translate("CDlgTalk_qt", " \345\217\221\350\250\200\344\272\272\345\210\227\350\241\250", nullptr));
        labMaxCount->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = speakList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CDlgTalk_qt", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = speakList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CDlgTalk_qt", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = speakList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CDlgTalk_qt", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = speakList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CDlgTalk_qt", "\347\264\242\345\274\225", nullptr));
        labLoad->setText(QCoreApplication::translate("CDlgTalk_qt", "\346\255\243\345\234\250\345\212\240\350\275\275...", nullptr));
        lineSearch->setPlaceholderText(QCoreApplication::translate("CDlgTalk_qt", "\346\220\234\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CDlgTalk_qt", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CDlgTalk_qt", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("CDlgTalk_qt", "\350\247\222\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("CDlgTalk_qt", "ID", nullptr));
        labCompere->setText(QString());
        labInitiator->setText(QString());
        labelContactsInfo_chat->setText(QString());
        btnContactsInfo->setText(QString());
        btnMem->setText(QCoreApplication::translate("CDlgTalk_qt", "\345\210\206\347\273\204\346\210\220\345\221\230", nullptr));
        btnGrpDel->setText(QCoreApplication::translate("CDlgTalk_qt", "\345\210\240\351\231\244\347\276\244\347\273\204", nullptr));
        labCreator->setText(QString());
        labelGroup->setText(QCoreApplication::translate("CDlgTalk_qt", "TextLabel", nullptr));
        headIcoBtn->setText(QString());
        labelMsgID->setText(QCoreApplication::translate("CDlgTalk_qt", "TextLabel", nullptr));
        labelName->setText(QCoreApplication::translate("CDlgTalk_qt", "TextLabel", nullptr));
        btnRule->setText(QCoreApplication::translate("CDlgTalk_qt", "\350\247\204\345\210\231\350\256\276\347\275\256", nullptr));
        btnFace->setText(QString());
        btnFileSend->setText(QString());
        btnDisk->setText(QString());
        btnVideo->setText(QString());
        btnSendImg->setText(QCoreApplication::translate("CDlgTalk_qt", "\345\217\221\351\200\201", nullptr));
        lab_io->setText(QString());
        user_val->setText(QString());
        duration->setText(QCoreApplication::translate("CDlgTalk_qt", "\344\274\232\350\256\256\346\227\266\351\225\277\357\274\232", nullptr));
        duration_val->setText(QCoreApplication::translate("CDlgTalk_qt", "00:00:00", nullptr));
        recordImg->setText(QString());
        lable_t10->setText(QCoreApplication::translate("CDlgTalk_qt", "\345\275\225\345\210\266\344\270\255", nullptr));
        lab_t1->setText(QCoreApplication::translate("CDlgTalk_qt", "\347\275\221\347\273\234\351\200\237\347\216\207\357\274\232", nullptr));
        rate->setText(QCoreApplication::translate("CDlgTalk_qt", "10kb", nullptr));
        lab_t2->setText(QCoreApplication::translate("CDlgTalk_qt", "\344\270\242\345\214\205\347\216\207\357\274\232", nullptr));
        loss->setText(QCoreApplication::translate("CDlgTalk_qt", "0%", nullptr));
        btn_img1->setText(QString());
        lab_t3->setText(QCoreApplication::translate("CDlgTalk_qt", "\350\256\244\350\257\201\346\255\243\345\270\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_qt: public Ui_CDlgTalk_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_QT_H
