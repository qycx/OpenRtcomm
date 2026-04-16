/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_msgr_detail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_MSGR_DETAIL_H
#define UI_CDLGTALK_MSGR_DETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_msgr_detail
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *centerWidget;
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label1_9;
    QLabel *label1_11;
    QLabel *labSyr;
    QLabel *label7;
    QLabel *label1_7;
    QLabel *label1_10;
    QLabel *label1_8;
    QLabel *label1_6;
    QLabel *label4;
    QLabel *label;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label5;
    QLabel *label_2;
    QLabel *labMsgrId;
    QLabel *labelGroup;
    QLabel *labelName;
    QPushButton *headIcoBtn;
    QLabel *idinfo;
    QWidget *bottomWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSendMsg;
    QPushButton *benSendMeeting;
    QPushButton *setBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *CDlgTalk_msgr_detail)
    {
        if (CDlgTalk_msgr_detail->objectName().isEmpty())
            CDlgTalk_msgr_detail->setObjectName("CDlgTalk_msgr_detail");
        CDlgTalk_msgr_detail->resize(883, 681);
        CDlgTalk_msgr_detail->setMouseTracking(true);
        verticalLayout = new QVBoxLayout(CDlgTalk_msgr_detail);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        centerWidget = new QWidget(CDlgTalk_msgr_detail);
        centerWidget->setObjectName("centerWidget");
        formLayoutWidget = new QWidget(centerWidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(180, 190, 511, 211));
        gridLayout = new QGridLayout(formLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label1_9 = new QLabel(formLayoutWidget);
        label1_9->setObjectName("label1_9");
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        label1_9->setFont(font);
        label1_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label1_9, 5, 0, 1, 1);

        label1_11 = new QLabel(formLayoutWidget);
        label1_11->setObjectName("label1_11");
        label1_11->setFont(font);
        label1_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label1_11, 4, 2, 1, 1);

        labSyr = new QLabel(formLayoutWidget);
        labSyr->setObjectName("labSyr");
        QFont font1;
        font1.setPointSize(10);
        labSyr->setFont(font1);

        gridLayout->addWidget(labSyr, 1, 3, 1, 1);

        label7 = new QLabel(formLayoutWidget);
        label7->setObjectName("label7");
        label7->setFont(font1);

        gridLayout->addWidget(label7, 4, 3, 1, 1);

        label1_7 = new QLabel(formLayoutWidget);
        label1_7->setObjectName("label1_7");
        label1_7->setFont(font);
        label1_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label1_7, 3, 0, 1, 1);

        label1_10 = new QLabel(formLayoutWidget);
        label1_10->setObjectName("label1_10");
        label1_10->setFont(font);
        label1_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label1_10, 1, 2, 1, 1);

        label1_8 = new QLabel(formLayoutWidget);
        label1_8->setObjectName("label1_8");
        label1_8->setFont(font);
        label1_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label1_8, 4, 0, 1, 1);

        label1_6 = new QLabel(formLayoutWidget);
        label1_6->setObjectName("label1_6");
        label1_6->setFont(font);
        label1_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label1_6, 1, 0, 1, 1);

        label4 = new QLabel(formLayoutWidget);
        label4->setObjectName("label4");
        label4->setFont(font1);

        gridLayout->addWidget(label4, 4, 1, 1, 1);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label1 = new QLabel(formLayoutWidget);
        label1->setObjectName("label1");
        label1->setFont(font1);

        gridLayout->addWidget(label1, 0, 1, 1, 1);

        label2 = new QLabel(formLayoutWidget);
        label2->setObjectName("label2");
        label2->setFont(font1);

        gridLayout->addWidget(label2, 1, 1, 1, 1);

        label3 = new QLabel(formLayoutWidget);
        label3->setObjectName("label3");
        label3->setFont(font1);

        gridLayout->addWidget(label3, 3, 1, 1, 1);

        label5 = new QLabel(formLayoutWidget);
        label5->setObjectName("label5");
        label5->setFont(font1);

        gridLayout->addWidget(label5, 5, 1, 1, 1);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 1, Qt::AlignRight);

        labMsgrId = new QLabel(formLayoutWidget);
        labMsgrId->setObjectName("labMsgrId");

        gridLayout->addWidget(labMsgrId, 2, 1, 1, 1);

        labelGroup = new QLabel(centerWidget);
        labelGroup->setObjectName("labelGroup");
        labelGroup->setGeometry(QRect(380, 120, 271, 21));
        labelName = new QLabel(centerWidget);
        labelName->setObjectName("labelName");
        labelName->setGeometry(QRect(380, 90, 271, 21));
        headIcoBtn = new QPushButton(centerWidget);
        headIcoBtn->setObjectName("headIcoBtn");
        headIcoBtn->setGeometry(QRect(320, 90, 55, 55));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(headIcoBtn->sizePolicy().hasHeightForWidth());
        headIcoBtn->setSizePolicy(sizePolicy);
        headIcoBtn->setMinimumSize(QSize(55, 55));
        headIcoBtn->setMaximumSize(QSize(55, 55));
        headIcoBtn->setProperty("hasborder", QVariant(true));
        idinfo = new QLabel(centerWidget);
        idinfo->setObjectName("idinfo");
        idinfo->setEnabled(true);
        idinfo->setGeometry(QRect(350, 40, 271, 21));

        verticalLayout->addWidget(centerWidget);

        bottomWidget = new QWidget(CDlgTalk_msgr_detail);
        bottomWidget->setObjectName("bottomWidget");
        bottomWidget->setMinimumSize(QSize(0, 200));
        bottomWidget->setMaximumSize(QSize(16777215, 200));
        horizontalLayout = new QHBoxLayout(bottomWidget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 30);
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

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);

        retranslateUi(CDlgTalk_msgr_detail);

        QMetaObject::connectSlotsByName(CDlgTalk_msgr_detail);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_msgr_detail)
    {
        CDlgTalk_msgr_detail->setWindowTitle(QCoreApplication::translate("CDlgTalk_msgr_detail", "CDlgTalk_msgr_detail", nullptr));
        label1_9->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\344\275\277\347\224\250\345\234\260\347\202\271\357\274\232", nullptr));
        label1_11->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\350\201\224\347\263\273\347\224\265\350\257\235\357\274\232", nullptr));
        labSyr->setText(QString());
        label7->setText(QString());
        label1_7->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\346\234\272\345\231\250\347\261\273\345\236\213\357\274\232", nullptr));
        label1_10->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\344\275\277\347\224\250\344\272\272\357\274\232", nullptr));
        label1_8->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\344\270\273\350\246\201\347\224\250\351\200\224\357\274\232", nullptr));
        label1_6->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\351\203\250  \351\227\250\357\274\232", nullptr));
        label4->setText(QString());
        label->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\345\215\225  \344\275\215\357\274\232", nullptr));
        label1->setText(QString());
        label2->setText(QString());
        label3->setText(QString());
        label5->setText(QString());
        label_2->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "MESSENGER_ID\357\274\232", nullptr));
        labMsgrId->setText(QString());
        labelGroup->setText(QString());
        labelName->setText(QString());
        headIcoBtn->setText(QString());
        idinfo->setText(QString());
        btnSendMsg->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\345\217\221\346\266\210\346\201\257", nullptr));
        benSendMeeting->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\345\217\221\350\265\267\344\274\232\350\256\256", nullptr));
        setBtn->setText(QCoreApplication::translate("CDlgTalk_msgr_detail", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_msgr_detail: public Ui_CDlgTalk_msgr_detail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_MSGR_DETAIL_H
