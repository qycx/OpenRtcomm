/********************************************************************************
** Form generated from reading UI file 'MsgRecordItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGRECORDITEM_H
#define UI_MSGRECORDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgRecordItem
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnHead;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labName;
    QLabel *labMsg;

    void setupUi(QWidget *MsgRecordItem)
    {
        if (MsgRecordItem->objectName().isEmpty())
            MsgRecordItem->setObjectName("MsgRecordItem");
        MsgRecordItem->resize(527, 78);
        MsgRecordItem->setMinimumSize(QSize(500, 0));
        MsgRecordItem->setMaximumSize(QSize(700, 16777215));
        verticalLayout = new QVBoxLayout(MsgRecordItem);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(MsgRecordItem);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{ border-bottom:1px solid #999;}"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        btnHead = new QPushButton(widget);
        btnHead->setObjectName("btnHead");
        btnHead->setEnabled(false);
        btnHead->setMinimumSize(QSize(50, 50));
        btnHead->setMaximumSize(QSize(50, 50));
        btnHead->setStyleSheet(QString::fromUtf8("border:none;"));
        btnHead->setIconSize(QSize(50, 50));

        horizontalLayout->addWidget(btnHead);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 0, 0, 0);
        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 20));
        widget_2->setMaximumSize(QSize(16777215, 20));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labName = new QLabel(widget_2);
        labName->setObjectName("labName");
        labName->setMinimumSize(QSize(150, 0));
        labName->setMaximumSize(QSize(16777215, 16777215));
        labName->setStyleSheet(QString::fromUtf8("color:#888;"));

        horizontalLayout_2->addWidget(labName, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_2);

        labMsg = new QLabel(widget_3);
        labMsg->setObjectName("labMsg");
        labMsg->setMinimumSize(QSize(630, 20));
        labMsg->setMaximumSize(QSize(630, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setBold(false);
        labMsg->setFont(font);
        labMsg->setStyleSheet(QString::fromUtf8("font-size:18px;\n"
"font-weight:400;\n"
""));
        labMsg->setWordWrap(true);

        verticalLayout_2->addWidget(labMsg);


        horizontalLayout->addWidget(widget_3);


        verticalLayout->addWidget(widget);


        retranslateUi(MsgRecordItem);

        QMetaObject::connectSlotsByName(MsgRecordItem);
    } // setupUi

    void retranslateUi(QWidget *MsgRecordItem)
    {
        MsgRecordItem->setWindowTitle(QCoreApplication::translate("MsgRecordItem", "MsgRecordItem", nullptr));
        btnHead->setText(QString());
        labName->setText(QCoreApplication::translate("MsgRecordItem", "\346\235\216\345\233\233", nullptr));
        labMsg->setText(QCoreApplication::translate("MsgRecordItem", "\346\230\257\347\232\204\345\217\221\351\200\201\345\210\260\345\217\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MsgRecordItem: public Ui_MsgRecordItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGRECORDITEM_H
