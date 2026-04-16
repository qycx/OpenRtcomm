/********************************************************************************
** Form generated from reading UI file 'WinSystemAbout.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSYSTEMABOUT_H
#define UI_WINSYSTEMABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSystemAbout
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *BtnIcon;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *labLine1;
    QLabel *labLine2;
    QLabel *labLine4;
    QPushButton *pushButton;

    void setupUi(QWidget *WinSystemAbout)
    {
        if (WinSystemAbout->objectName().isEmpty())
            WinSystemAbout->setObjectName("WinSystemAbout");
        WinSystemAbout->resize(600, 200);
        WinSystemAbout->setMaximumSize(QSize(600, 200));
        WinSystemAbout->setStyleSheet(QString::fromUtf8("font-size:18px"));
        horizontalLayout = new QHBoxLayout(WinSystemAbout);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        BtnIcon = new QPushButton(WinSystemAbout);
        BtnIcon->setObjectName("BtnIcon");
        BtnIcon->setMaximumSize(QSize(70, 70));
        BtnIcon->setStyleSheet(QString::fromUtf8("border:none;"));
        BtnIcon->setInputMethodHints(Qt::ImhNone);
        BtnIcon->setIconSize(QSize(70, 70));

        horizontalLayout->addWidget(BtnIcon);

        widget = new QWidget(WinSystemAbout);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        labLine1 = new QLabel(widget);
        labLine1->setObjectName("labLine1");

        verticalLayout->addWidget(labLine1);

        labLine2 = new QLabel(widget);
        labLine2->setObjectName("labLine2");

        verticalLayout->addWidget(labLine2);

        labLine4 = new QLabel(widget);
        labLine4->setObjectName("labLine4");

        verticalLayout->addWidget(labLine4);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(100, 16777215));

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        horizontalLayout->addWidget(widget);


        retranslateUi(WinSystemAbout);
        QObject::connect(pushButton, &QPushButton::clicked, WinSystemAbout, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(WinSystemAbout);
    } // setupUi

    void retranslateUi(QWidget *WinSystemAbout)
    {
        WinSystemAbout->setWindowTitle(QCoreApplication::translate("WinSystemAbout", "WinSystemAbout", nullptr));
        BtnIcon->setText(QString());
        labLine1->setText(QCoreApplication::translate("WinSystemAbout", "TextLabel", nullptr));
        labLine2->setText(QCoreApplication::translate("WinSystemAbout", "TextLabel", nullptr));
        labLine4->setText(QCoreApplication::translate("WinSystemAbout", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("WinSystemAbout", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinSystemAbout: public Ui_WinSystemAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSYSTEMABOUT_H
