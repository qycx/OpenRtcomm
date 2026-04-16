/********************************************************************************
** Form generated from reading UI file 'WinMsgBox.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINMSGBOX_H
#define UI_WINMSGBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinMsgBox
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QWidget *centerWidget;
    QLabel *MessageIcon;
    QLabel *MessageContent;
    QWidget *bottomWidget;
    QPushButton *pButtonOk;
    QPushButton *pButtonCancel;

    void setupUi(QWidget *WinMsgBox)
    {
        if (WinMsgBox->objectName().isEmpty())
            WinMsgBox->setObjectName("WinMsgBox");
        WinMsgBox->resize(402, 219);
        WinMsgBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(WinMsgBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(WinMsgBox);
        titleWidget->setObjectName("titleWidget");
        titleWidget->setProperty("titleskin", QVariant(true));

        verticalLayout->addWidget(titleWidget);

        centerWidget = new QWidget(WinMsgBox);
        centerWidget->setObjectName("centerWidget");
        MessageIcon = new QLabel(centerWidget);
        MessageIcon->setObjectName("MessageIcon");
        MessageIcon->setGeometry(QRect(50, 40, 61, 51));
        MessageContent = new QLabel(centerWidget);
        MessageContent->setObjectName("MessageContent");
        MessageContent->setGeometry(QRect(120, 50, 251, 41));
        MessageContent->setWordWrap(true);
        MessageContent->setMargin(2);

        verticalLayout->addWidget(centerWidget);

        bottomWidget = new QWidget(WinMsgBox);
        bottomWidget->setObjectName("bottomWidget");
        bottomWidget->setProperty("bottomskin", QVariant(true));
        pButtonOk = new QPushButton(bottomWidget);
        pButtonOk->setObjectName("pButtonOk");
        pButtonOk->setGeometry(QRect(170, 10, 93, 29));
        pButtonCancel = new QPushButton(bottomWidget);
        pButtonCancel->setObjectName("pButtonCancel");
        pButtonCancel->setGeometry(QRect(280, 10, 93, 29));

        verticalLayout->addWidget(bottomWidget);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 12);
        verticalLayout->setStretch(2, 5);

        retranslateUi(WinMsgBox);

        QMetaObject::connectSlotsByName(WinMsgBox);
    } // setupUi

    void retranslateUi(QWidget *WinMsgBox)
    {
        WinMsgBox->setWindowTitle(QCoreApplication::translate("WinMsgBox", "Form", nullptr));
        MessageIcon->setText(QString());
        MessageContent->setText(QString());
        pButtonOk->setText(QCoreApplication::translate("WinMsgBox", "\347\241\256 \345\256\232", nullptr));
        pButtonCancel->setText(QCoreApplication::translate("WinMsgBox", "\345\217\226 \346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinMsgBox: public Ui_WinMsgBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINMSGBOX_H
