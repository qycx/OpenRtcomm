/********************************************************************************
** Form generated from reading UI file 'TipViewIM.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPVIEWIM_H
#define UI_TIPVIEWIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "TipListView.h"

QT_BEGIN_NAMESPACE

class Ui_TipViewIM
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    TipListView *listView;
    QWidget *widget_2;
    QPushButton *btn_lose;

    void setupUi(QWidget *TipViewIM)
    {
        if (TipViewIM->objectName().isEmpty())
            TipViewIM->setObjectName("TipViewIM");
        TipViewIM->resize(300, 148);
        TipViewIM->setMinimumSize(QSize(300, 130));
        TipViewIM->setMaximumSize(QSize(300, 16777215));
        horizontalLayout = new QHBoxLayout(TipViewIM);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(TipViewIM);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget\n"
"{\n"
"border-radius:5px;\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 35));
        label->setMaximumSize(QSize(16777215, 35));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setBold(true);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:#353535;\n"
"font: 15px;\n"
"margin-left:12px;\n"
"font-weight:bold;"));
        label->setMargin(0);

        verticalLayout->addWidget(label);

        listView = new TipListView(widget);
        listView->setObjectName("listView");
        listView->setStyleSheet(QString::fromUtf8("QListView#listView\n"
"{\n"
" border:0px;\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
""));

        verticalLayout->addWidget(listView);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 35));
        widget_2->setMaximumSize(QSize(16777215, 35));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget#widget_2\n"
"{\n"
"border-top: 1px solid #e7e7e7;\n"
"}"));
        btn_lose = new QPushButton(widget_2);
        btn_lose->setObjectName("btn_lose");
        btn_lose->setGeometry(QRect(200, 6, 75, 24));
        btn_lose->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_lose->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(35, 163, 35);\n"
"font: 14px;\n"
"}\n"
"QPushButton:pressed {  \n"
"color: #ff0000;\n"
"font: 14px;\n"
"border:0px;\n"
"}  \n"
""));
        btn_lose->setFlat(true);

        verticalLayout->addWidget(widget_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(TipViewIM);
        QObject::connect(btn_lose, SIGNAL(clicked()), TipViewIM, SLOT(button_lose()));

        QMetaObject::connectSlotsByName(TipViewIM);
    } // setupUi

    void retranslateUi(QWidget *TipViewIM)
    {
        TipViewIM->setWindowTitle(QCoreApplication::translate("TipViewIM", "TipViewIM", nullptr));
        label->setText(QCoreApplication::translate("TipViewIM", "\346\226\260\346\266\210\346\201\257(1)", nullptr));
        btn_lose->setText(QCoreApplication::translate("TipViewIM", "\345\277\275\347\225\245\345\205\250\351\203\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TipViewIM: public Ui_TipViewIM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPVIEWIM_H
