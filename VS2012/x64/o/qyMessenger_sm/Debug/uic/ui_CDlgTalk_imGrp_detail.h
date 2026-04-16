/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_imGrp_detail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_IMGRP_DETAIL_H
#define UI_CDLGTALK_IMGRP_DETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_imGrp_detail
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *centerWidget;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelGroupInfo;
    QFrame *line;
    QWidget *bottomWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSendMsg;
    QPushButton *benSendMeeting;
    QPushButton *setBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *CDlgTalk_imGrp_detail)
    {
        if (CDlgTalk_imGrp_detail->objectName().isEmpty())
            CDlgTalk_imGrp_detail->setObjectName("CDlgTalk_imGrp_detail");
        CDlgTalk_imGrp_detail->resize(843, 743);
        CDlgTalk_imGrp_detail->setMouseTracking(true);
        verticalLayout = new QVBoxLayout(CDlgTalk_imGrp_detail);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        centerWidget = new QWidget(CDlgTalk_imGrp_detail);
        centerWidget->setObjectName("centerWidget");
        gridLayout_2 = new QGridLayout(centerWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        scrollArea = new QScrollArea(centerWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 780, 550));
        scrollAreaWidgetContents->setMinimumSize(QSize(780, 550));
        scrollAreaWidgetContents->setMaximumSize(QSize(780, 550));
        gridLayoutWidget = new QWidget(scrollAreaWidgetContents);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 40, 721, 491));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(15);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout->setContentsMargins(30, 30, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 2, 0, 1, 1);

        labelGroupInfo = new QLabel(centerWidget);
        labelGroupInfo->setObjectName("labelGroupInfo");
        labelGroupInfo->setEnabled(true);

        gridLayout_2->addWidget(labelGroupInfo, 0, 0, 1, 1);

        line = new QFrame(centerWidget);
        line->setObjectName("line");
        line->setMinimumSize(QSize(0, 5));
        line->setMaximumSize(QSize(16777215, 5));
        line->setStyleSheet(QString::fromUtf8("color: rgb(0, 85, 255);"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 1);


        verticalLayout->addWidget(centerWidget);

        bottomWidget = new QWidget(CDlgTalk_imGrp_detail);
        bottomWidget->setObjectName("bottomWidget");
        bottomWidget->setMinimumSize(QSize(0, 120));
        bottomWidget->setMaximumSize(QSize(16777215, 120));
        horizontalLayout = new QHBoxLayout(bottomWidget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 15);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnSendMsg = new QPushButton(bottomWidget);
        btnSendMsg->setObjectName("btnSendMsg");
        btnSendMsg->setMinimumSize(QSize(100, 40));
        btnSendMsg->setMaximumSize(QSize(100, 40));

        horizontalLayout->addWidget(btnSendMsg);

        benSendMeeting = new QPushButton(bottomWidget);
        benSendMeeting->setObjectName("benSendMeeting");
        benSendMeeting->setMinimumSize(QSize(100, 40));
        benSendMeeting->setMaximumSize(QSize(100, 40));

        horizontalLayout->addWidget(benSendMeeting);

        setBtn = new QPushButton(bottomWidget);
        setBtn->setObjectName("setBtn");
        setBtn->setMinimumSize(QSize(100, 40));
        setBtn->setMaximumSize(QSize(100, 40));

        horizontalLayout->addWidget(setBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(bottomWidget);

        verticalLayout->setStretch(1, 1);

        retranslateUi(CDlgTalk_imGrp_detail);

        QMetaObject::connectSlotsByName(CDlgTalk_imGrp_detail);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_imGrp_detail)
    {
        CDlgTalk_imGrp_detail->setWindowTitle(QCoreApplication::translate("CDlgTalk_imGrp_detail", "CDlgTalk_imGrp_detail", nullptr));
        labelGroupInfo->setText(QString());
        btnSendMsg->setText(QCoreApplication::translate("CDlgTalk_imGrp_detail", "\345\217\221\346\266\210\346\201\257", nullptr));
        benSendMeeting->setText(QCoreApplication::translate("CDlgTalk_imGrp_detail", "\345\217\221\350\265\267\344\274\232\350\256\256", nullptr));
        setBtn->setText(QCoreApplication::translate("CDlgTalk_imGrp_detail", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_imGrp_detail: public Ui_CDlgTalk_imGrp_detail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_IMGRP_DETAIL_H
