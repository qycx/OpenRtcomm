/********************************************************************************
** Form generated from reading UI file 'CDlgTalkMoreMenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALKMOREMENU_H
#define UI_CDLGTALKMOREMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalkMoreMenu
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QToolButton *toolBtnMember;
    QToolButton *toolBtnFacility;
    QToolButton *toolBtnMake;
    QToolButton *toolBtnController;
    QToolButton *toolBtnDish;
    QToolButton *toolBtnThis;
    QToolButton *toolBtnFullScreen;

    void setupUi(QWidget *CDlgTalkMoreMenu)
    {
        if (CDlgTalkMoreMenu->objectName().isEmpty())
            CDlgTalkMoreMenu->setObjectName("CDlgTalkMoreMenu");
        CDlgTalkMoreMenu->resize(373, 167);
        horizontalLayout = new QHBoxLayout(CDlgTalkMoreMenu);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgTalkMoreMenu);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(70, 65));
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"border:1px solid #888;\n"
"background:#ffffff;}\n"
"\n"
"QToolButton{\n"
" border:none;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 3, 0, 0);
        toolBtnMember = new QToolButton(widget);
        toolBtnMember->setObjectName("toolBtnMember");
        toolBtnMember->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnMember, 1, 4, 1, 1);

        toolBtnFacility = new QToolButton(widget);
        toolBtnFacility->setObjectName("toolBtnFacility");
        toolBtnFacility->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnFacility, 0, 0, 1, 1);

        toolBtnMake = new QToolButton(widget);
        toolBtnMake->setObjectName("toolBtnMake");
        toolBtnMake->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnMake, 1, 2, 1, 1);

        toolBtnController = new QToolButton(widget);
        toolBtnController->setObjectName("toolBtnController");
        toolBtnController->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnController, 1, 0, 1, 1);

        toolBtnDish = new QToolButton(widget);
        toolBtnDish->setObjectName("toolBtnDish");
        toolBtnDish->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnDish, 0, 1, 1, 1);

        toolBtnThis = new QToolButton(widget);
        toolBtnThis->setObjectName("toolBtnThis");
        toolBtnThis->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnThis, 0, 2, 1, 1);

        toolBtnFullScreen = new QToolButton(widget);
        toolBtnFullScreen->setObjectName("toolBtnFullScreen");
        toolBtnFullScreen->setMinimumSize(QSize(70, 65));

        gridLayout->addWidget(toolBtnFullScreen, 0, 4, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgTalkMoreMenu);

        QMetaObject::connectSlotsByName(CDlgTalkMoreMenu);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalkMoreMenu)
    {
        CDlgTalkMoreMenu->setWindowTitle(QCoreApplication::translate("CDlgTalkMoreMenu", "CDlgTalkMoreMenu", nullptr));
        toolBtnMember->setText(QString());
        toolBtnFacility->setText(QString());
        toolBtnMake->setText(QString());
        toolBtnController->setText(QCoreApplication::translate("CDlgTalkMoreMenu", "...", nullptr));
        toolBtnDish->setText(QString());
        toolBtnThis->setText(QString());
        toolBtnFullScreen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CDlgTalkMoreMenu: public Ui_CDlgTalkMoreMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALKMOREMENU_H
