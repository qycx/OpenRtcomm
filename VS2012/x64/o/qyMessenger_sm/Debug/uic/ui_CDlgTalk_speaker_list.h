/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_speaker_list.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_SPEAKER_LIST_H
#define UI_CDLGTALK_SPEAKER_LIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_speaker_list
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *btnClose;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_staticInitiator;
    QLabel *label_initiator;

    void setupUi(QWidget *CDlgTalk_speaker_list)
    {
        if (CDlgTalk_speaker_list->objectName().isEmpty())
            CDlgTalk_speaker_list->setObjectName("CDlgTalk_speaker_list");
        CDlgTalk_speaker_list->resize(328, 379);
        horizontalLayout = new QHBoxLayout(CDlgTalk_speaker_list);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgTalk_speaker_list);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background:#fff;"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 5, 10, 10);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:16px;"));

        horizontalLayout_2->addWidget(label);

        btnClose = new QPushButton(widget_2);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        btnClose->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnClose->setStyleSheet(QString::fromUtf8("image: url(:Resources/Images/WinMain/sysbtn_close_normal.png);\n"
"border:none;"));
        btnClose->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(widget_3);
        listWidget->setObjectName("listWidget");

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_staticInitiator = new QLabel(widget_3);
        label_staticInitiator->setObjectName("label_staticInitiator");

        horizontalLayout_3->addWidget(label_staticInitiator);

        label_initiator = new QLabel(widget_3);
        label_initiator->setObjectName("label_initiator");

        horizontalLayout_3->addWidget(label_initiator);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgTalk_speaker_list);
        QObject::connect(btnClose, &QPushButton::clicked, CDlgTalk_speaker_list, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(CDlgTalk_speaker_list);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_speaker_list)
    {
        CDlgTalk_speaker_list->setWindowTitle(QCoreApplication::translate("CDlgTalk_speaker_list", "CDlgTalk_speaker_list", nullptr));
        label->setText(QCoreApplication::translate("CDlgTalk_speaker_list", " \345\217\221\350\250\200\344\272\272\345\210\227\350\241\250", nullptr));
        btnClose->setText(QString());
        label_staticInitiator->setText(QCoreApplication::translate("CDlgTalk_speaker_list", "Initiator:", nullptr));
        label_initiator->setText(QCoreApplication::translate("CDlgTalk_speaker_list", "188", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_speaker_list: public Ui_CDlgTalk_speaker_list {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_SPEAKER_LIST_H
