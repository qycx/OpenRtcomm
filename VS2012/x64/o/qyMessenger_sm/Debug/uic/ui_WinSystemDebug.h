/********************************************************************************
** Form generated from reading UI file 'WinSystemDebug.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSYSTEMDEBUG_H
#define UI_WINSYSTEMDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSystemDebug
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *WinSystemDebug)
    {
        if (WinSystemDebug->objectName().isEmpty())
            WinSystemDebug->setObjectName("WinSystemDebug");
        WinSystemDebug->resize(561, 100);
        WinSystemDebug->setMinimumSize(QSize(0, 100));
        WinSystemDebug->setMaximumSize(QSize(16777215, 100));
        WinSystemDebug->setStyleSheet(QString::fromUtf8("QLabel{font-size:17px;\n"
"font-weight:500;\n"
"}"));
        verticalLayout = new QVBoxLayout(WinSystemDebug);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(WinSystemDebug);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(200, 50));

        verticalLayout->addWidget(pushButton);


        retranslateUi(WinSystemDebug);

        QMetaObject::connectSlotsByName(WinSystemDebug);
    } // setupUi

    void retranslateUi(QWidget *WinSystemDebug)
    {
        WinSystemDebug->setWindowTitle(QCoreApplication::translate("WinSystemDebug", "WinSystemDebug", nullptr));
        pushButton->setText(QCoreApplication::translate("WinSystemDebug", "\346\211\223\345\274\200\347\263\273\347\273\237\347\212\266\346\200\201\347\252\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinSystemDebug: public Ui_WinSystemDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSYSTEMDEBUG_H
