/********************************************************************************
** Form generated from reading UI file 'WinContactItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINCONTACTITEM_H
#define UI_WINCONTACTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinContactItem
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLabel *headName;
    QLabel *lab_count;
    QLabel *lab_online;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userName;
    QLabel *sendTime;
    QLabel *signName;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *WinContactItem)
    {
        if (WinContactItem->objectName().isEmpty())
            WinContactItem->setObjectName("WinContactItem");
        WinContactItem->resize(322, 80);
        WinContactItem->setMinimumSize(QSize(322, 80));
        WinContactItem->setMaximumSize(QSize(426, 80));
        horizontalLayout = new QHBoxLayout(WinContactItem);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(6, 0, 6, 0);
        widget = new QWidget(WinContactItem);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(75, 75));
        widget->setMaximumSize(QSize(75, 75));
        headName = new QLabel(widget);
        headName->setObjectName("headName");
        headName->setGeometry(QRect(10, 10, 50, 50));
        headName->setMinimumSize(QSize(50, 50));
        headName->setMaximumSize(QSize(50, 50));
        lab_count = new QLabel(widget);
        lab_count->setObjectName("lab_count");
        lab_count->setGeometry(QRect(50, 5, 20, 12));
        lab_count->setMinimumSize(QSize(20, 12));
        lab_count->setMaximumSize(QSize(20, 12));
        lab_count->setStyleSheet(QString::fromUtf8("background:red;\n"
"border-radius:6px;\n"
"color:#ffffff;\n"
"font-size:10px;"));
        lab_count->setAlignment(Qt::AlignCenter);
        lab_online = new QLabel(widget);
        lab_online->setObjectName("lab_online");
        lab_online->setGeometry(QRect(50, 50, 13, 13));
        lab_online->setMinimumSize(QSize(13, 13));
        lab_online->setMaximumSize(QSize(13, 13));
        lab_online->setStyleSheet(QString::fromUtf8("background:rgb(77, 217, 101);border-radius:6px;"));

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        verticalSpacer = new QSpacerItem(353, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget_2 = new QWidget(WinContactItem);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 24));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        userName = new QLabel(widget_2);
        userName->setObjectName("userName");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userName->sizePolicy().hasHeightForWidth());
        userName->setSizePolicy(sizePolicy);
        userName->setMinimumSize(QSize(0, 24));
        userName->setMaximumSize(QSize(16777215, 24));
        userName->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(userName);

        sendTime = new QLabel(widget_2);
        sendTime->setObjectName("sendTime");
        sendTime->setMinimumSize(QSize(80, 24));
        sendTime->setMaximumSize(QSize(80, 16777215));
        sendTime->setStyleSheet(QString::fromUtf8("color:#999;\n"
"font-size:12px;"));
        sendTime->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(sendTime, 0, Qt::AlignRight);


        verticalLayout->addWidget(widget_2);

        signName = new QLabel(WinContactItem);
        signName->setObjectName("signName");
        sizePolicy.setHeightForWidth(signName->sizePolicy().hasHeightForWidth());
        signName->setSizePolicy(sizePolicy);
        signName->setMinimumSize(QSize(0, 16));
        signName->setMaximumSize(QSize(16777215, 16));

        verticalLayout->addWidget(signName);

        verticalSpacer_2 = new QSpacerItem(353, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(WinContactItem);

        QMetaObject::connectSlotsByName(WinContactItem);
    } // setupUi

    void retranslateUi(QWidget *WinContactItem)
    {
        WinContactItem->setWindowTitle(QCoreApplication::translate("WinContactItem", "Form", nullptr));
        headName->setText(QString());
        lab_count->setText(QCoreApplication::translate("WinContactItem", "0", nullptr));
        lab_online->setText(QString());
        userName->setText(QString());
        sendTime->setText(QCoreApplication::translate("WinContactItem", "00:00:00", nullptr));
        signName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WinContactItem: public Ui_WinContactItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINCONTACTITEM_H
