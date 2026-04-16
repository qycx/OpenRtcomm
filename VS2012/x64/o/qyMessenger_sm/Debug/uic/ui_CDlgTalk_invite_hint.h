/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_invite_hint.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_INVITE_HINT_H
#define UI_CDLGTALK_INVITE_HINT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_invite_hintClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *closeBtn;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *invitedIcon;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labText;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labTime;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnRefuse;
    QPushButton *btnConsent;

    void setupUi(QWidget *CDlgTalk_invite_hintClass)
    {
        if (CDlgTalk_invite_hintClass->objectName().isEmpty())
            CDlgTalk_invite_hintClass->setObjectName("CDlgTalk_invite_hintClass");
        CDlgTalk_invite_hintClass->resize(347, 229);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Resources/Images/Login/qmClient.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CDlgTalk_invite_hintClass->setWindowIcon(icon);
        CDlgTalk_invite_hintClass->setStyleSheet(QString::fromUtf8("border-radius:10%;"));
        verticalLayout_2 = new QVBoxLayout(CDlgTalk_invite_hintClass);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(CDlgTalk_invite_hintClass);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{ background:#fff;border-radius:10%;}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        widget_4->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(5, 0, 0, 0);
        closeBtn = new QPushButton(widget_4);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setMinimumSize(QSize(30, 30));
        closeBtn->setMaximumSize(QSize(30, 30));
        closeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        closeBtn->setStyleSheet(QString::fromUtf8("border:none"));

        horizontalLayout_3->addWidget(closeBtn, 0, Qt::AlignRight);


        verticalLayout->addWidget(widget_4, 0, Qt::AlignRight);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName("widget_6");
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        invitedIcon = new QPushButton(widget_6);
        invitedIcon->setObjectName("invitedIcon");
        invitedIcon->setMinimumSize(QSize(60, 60));
        invitedIcon->setMaximumSize(QSize(60, 60));
        invitedIcon->setStyleSheet(QString::fromUtf8("border:none"));
        invitedIcon->setIconSize(QSize(60, 60));

        horizontalLayout_5->addWidget(invitedIcon);


        verticalLayout->addWidget(widget_6);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labText = new QLabel(widget_2);
        labText->setObjectName("labText");
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light")});
        font.setBold(true);
        labText->setFont(font);
        labText->setStyleSheet(QString::fromUtf8("font-size:20px;font-weight:bold;"));

        horizontalLayout_2->addWidget(labText);


        verticalLayout->addWidget(widget_2, 0, Qt::AlignHCenter);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        labTime = new QLabel(widget_5);
        labTime->setObjectName("labTime");
        labTime->setStyleSheet(QString::fromUtf8("font-size:14px;\n"
"color:#818181;\n"
"font-weight:400;"));

        horizontalLayout_4->addWidget(labTime, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(widget_5);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(11, 20, 11, 20);
        btnRefuse = new QPushButton(widget_3);
        btnRefuse->setObjectName("btnRefuse");
        btnRefuse->setMinimumSize(QSize(147, 36));
        btnRefuse->setMaximumSize(QSize(147, 16777215));
        btnRefuse->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnRefuse->setStyleSheet(QString::fromUtf8("background:#fff;\n"
"color:rgb(255,102,96);\n"
"font-size:16px;\n"
"border:1px solid #FF6767;\n"
"font-weight:bold;\n"
"border-radius:5%;"));

        horizontalLayout->addWidget(btnRefuse);

        btnConsent = new QPushButton(widget_3);
        btnConsent->setObjectName("btnConsent");
        btnConsent->setMinimumSize(QSize(147, 36));
        btnConsent->setMaximumSize(QSize(147, 16777215));
        btnConsent->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnConsent->setStyleSheet(QString::fromUtf8("background-color: QLinearGradient(x1:0,y1:0,x2:1,y2:0,stop:0 #5780D4, stop:1 #49AFD3);\n"
"color:#fff;\n"
"font-size:16px;\n"
"font-weight:bold;\n"
"border:none;\n"
"border-radius:5%;"));

        horizontalLayout->addWidget(btnConsent);


        verticalLayout->addWidget(widget_3);


        verticalLayout_2->addWidget(widget);


        retranslateUi(CDlgTalk_invite_hintClass);
        QObject::connect(closeBtn, &QPushButton::clicked, CDlgTalk_invite_hintClass, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(CDlgTalk_invite_hintClass);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_invite_hintClass)
    {
        CDlgTalk_invite_hintClass->setWindowTitle(QCoreApplication::translate("CDlgTalk_invite_hintClass", "CDlgTalk_invite_hint", nullptr));
        closeBtn->setText(QString());
        invitedIcon->setText(QString());
        labText->setText(QCoreApplication::translate("CDlgTalk_invite_hintClass", "\344\270\273\346\214\201\344\272\272\351\202\200\350\257\267\344\275\240\345\217\221\350\250\200", nullptr));
        labTime->setText(QCoreApplication::translate("CDlgTalk_invite_hintClass", "222", nullptr));
        btnRefuse->setText(QCoreApplication::translate("CDlgTalk_invite_hintClass", "\346\213\222\347\273\235", nullptr));
        btnConsent->setText(QCoreApplication::translate("CDlgTalk_invite_hintClass", "\345\220\214\346\204\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_invite_hintClass: public Ui_CDlgTalk_invite_hintClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_INVITE_HINT_H
