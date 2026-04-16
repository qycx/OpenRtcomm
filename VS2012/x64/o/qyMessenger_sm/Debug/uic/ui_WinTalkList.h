/********************************************************************************
** Form generated from reading UI file 'WinTalkList.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINTALKLIST_H
#define UI_WINTALKLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinTalkList
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidgetMsg;

    void setupUi(QWidget *WinTalkList)
    {
        if (WinTalkList->objectName().isEmpty())
            WinTalkList->setObjectName("WinTalkList");
        WinTalkList->resize(305, 809);
        gridLayout = new QGridLayout(WinTalkList);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidgetMsg = new QListWidget(WinTalkList);
        listWidgetMsg->setObjectName("listWidgetMsg");

        gridLayout->addWidget(listWidgetMsg, 0, 0, 1, 1);


        retranslateUi(WinTalkList);

        QMetaObject::connectSlotsByName(WinTalkList);
    } // setupUi

    void retranslateUi(QWidget *WinTalkList)
    {
        WinTalkList->setWindowTitle(QCoreApplication::translate("WinTalkList", "WinTalkList", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinTalkList: public Ui_WinTalkList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINTALKLIST_H
