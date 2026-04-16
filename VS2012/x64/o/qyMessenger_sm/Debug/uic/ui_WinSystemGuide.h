/********************************************************************************
** Form generated from reading UI file 'WinSystemGuide.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSYSTEMGUIDE_H
#define UI_WINSYSTEMGUIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSystemGuide
{
public:
    QLabel *label;

    void setupUi(QWidget *WinSystemGuide)
    {
        if (WinSystemGuide->objectName().isEmpty())
            WinSystemGuide->setObjectName("WinSystemGuide");
        WinSystemGuide->resize(502, 143);
        label = new QLabel(WinSystemGuide);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 50, 411, 31));
        label->setStyleSheet(QString::fromUtf8("font-size:20px"));

        retranslateUi(WinSystemGuide);

        QMetaObject::connectSlotsByName(WinSystemGuide);
    } // setupUi

    void retranslateUi(QWidget *WinSystemGuide)
    {
        WinSystemGuide->setWindowTitle(QCoreApplication::translate("WinSystemGuide", "WinSystemGuide", nullptr));
        label->setText(QCoreApplication::translate("WinSystemGuide", "\350\257\267\350\256\277\351\227\256https://bbs.qycx.com \347\275\221\347\253\231\346\235\245\350\216\267\345\217\226\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinSystemGuide: public Ui_WinSystemGuide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSYSTEMGUIDE_H
