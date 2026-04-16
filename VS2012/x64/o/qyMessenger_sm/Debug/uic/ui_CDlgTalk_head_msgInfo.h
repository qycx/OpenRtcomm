/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_head_msgInfo.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_HEAD_MSGINFO_H
#define UI_CDLGTALK_HEAD_MSGINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_head_msgInfoClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lab_head;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lab_name;
    QLabel *label_sex;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *dw;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_staticMessengerId;
    QLabel *lab_MessagerId;
    QLabel *label_3;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *msgDo;

    void setupUi(QWidget *CDlgTalk_head_msgInfoClass)
    {
        if (CDlgTalk_head_msgInfoClass->objectName().isEmpty())
            CDlgTalk_head_msgInfoClass->setObjectName("CDlgTalk_head_msgInfoClass");
        CDlgTalk_head_msgInfoClass->resize(273, 267);
        horizontalLayout = new QHBoxLayout(CDlgTalk_head_msgInfoClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgTalk_head_msgInfoClass);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(140, 0));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget\n"
"{\n"
"  \n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 0, 10, 10);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 70));
        widget_2->setMaximumSize(QSize(16777215, 60));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget#widget_2\n"
"{\n"
" border-bottom:1px solid #e5e5e5;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 20);
        lab_head = new QLabel(widget_2);
        lab_head->setObjectName("lab_head");
        lab_head->setMinimumSize(QSize(70, 70));
        lab_head->setMaximumSize(QSize(70, 70));

        horizontalLayout_2->addWidget(lab_head);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(8);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 12, 0, 0);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 30));
        widget_5->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lab_name = new QLabel(widget_5);
        lab_name->setObjectName("lab_name");
        lab_name->setContextMenuPolicy(Qt::NoContextMenu);
        lab_name->setStyleSheet(QString::fromUtf8("color:#333333;\n"
"font: 22px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-weight:500;"));
        lab_name->setTextInteractionFlags(Qt::TextSelectableByMouse);

        horizontalLayout_3->addWidget(lab_name);

        label_sex = new QLabel(widget_5);
        label_sex->setObjectName("label_sex");
        label_sex->setMinimumSize(QSize(20, 20));
        label_sex->setMaximumSize(QSize(20, 20));
        label_sex->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(label_sex);

        horizontalSpacer = new QSpacerItem(130, 17, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(widget_5);

        verticalSpacer = new QSpacerItem(20, 7, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(widget_4);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 12, 0, 0);
        label_2 = new QLabel(widget_3);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 18));
        label_2->setMaximumSize(QSize(16777215, 18));

        verticalLayout_4->addWidget(label_2);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(0, 30));
        widget_6->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_6);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color:#666666;\n"
"font-size:18px;"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        dw = new QLabel(widget_6);
        dw->setObjectName("dw");
        dw->setStyleSheet(QString::fromUtf8("font-size:18px"));

        horizontalLayout_4->addWidget(dw);


        verticalLayout_4->addWidget(widget_6);

        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName("widget_8");
        widget_8->setMinimumSize(QSize(0, 30));
        widget_8->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_5 = new QHBoxLayout(widget_8);
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_staticMessengerId = new QLabel(widget_8);
        label_staticMessengerId->setObjectName("label_staticMessengerId");
        label_staticMessengerId->setMinimumSize(QSize(110, 0));
        label_staticMessengerId->setStyleSheet(QString::fromUtf8("color:#666666;font-size:16px;"));
        label_staticMessengerId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_staticMessengerId);

        lab_MessagerId = new QLabel(widget_8);
        lab_MessagerId->setObjectName("lab_MessagerId");
        lab_MessagerId->setContextMenuPolicy(Qt::NoContextMenu);
        lab_MessagerId->setStyleSheet(QString::fromUtf8("color:#333333;\n"
"font-size:18px"));
        lab_MessagerId->setTextInteractionFlags(Qt::TextSelectableByMouse);

        horizontalLayout_5->addWidget(lab_MessagerId);


        verticalLayout_4->addWidget(widget_8);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName("label_3");

        verticalLayout_4->addWidget(label_3);


        verticalLayout->addWidget(widget_3);

        widget_9 = new QWidget(widget);
        widget_9->setObjectName("widget_9");
        widget_9->setMinimumSize(QSize(32, 52));
        widget_9->setMaximumSize(QSize(16777215, 52));
        widget_9->setStyleSheet(QString::fromUtf8("border-top:1px solid #e5e5e5;"));
        horizontalLayout_6 = new QHBoxLayout(widget_9);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 10, 0, 0);
        msgDo = new QPushButton(widget_9);
        msgDo->setObjectName("msgDo");
        msgDo->setMinimumSize(QSize(110, 31));
        msgDo->setMaximumSize(QSize(110, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        msgDo->setFont(font);
        msgDo->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        msgDo->setStyleSheet(QString::fromUtf8("background:rgb(7,193,96);border:none;color:#fff;border-radius:5%;font-size:16px"));

        horizontalLayout_6->addWidget(msgDo);


        verticalLayout->addWidget(widget_9);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgTalk_head_msgInfoClass);

        QMetaObject::connectSlotsByName(CDlgTalk_head_msgInfoClass);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_head_msgInfoClass)
    {
        CDlgTalk_head_msgInfoClass->setWindowTitle(QCoreApplication::translate("CDlgTalk_head_msgInfoClass", "CDlgTalk_head_msgInfo", nullptr));
        lab_head->setText(QString());
        lab_name->setText(QString());
        label_sex->setText(QString());
        label_2->setText(QString());
        label->setText(QCoreApplication::translate("CDlgTalk_head_msgInfoClass", "      \351\203\250  \351\227\250:", nullptr));
        dw->setText(QString());
        label_staticMessengerId->setText(QCoreApplication::translate("CDlgTalk_head_msgInfoClass", "Messenger ID:", nullptr));
        lab_MessagerId->setText(QString());
        label_3->setText(QString());
        msgDo->setText(QCoreApplication::translate("CDlgTalk_head_msgInfoClass", "\345\217\221\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_head_msgInfoClass: public Ui_CDlgTalk_head_msgInfoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_HEAD_MSGINFO_H
