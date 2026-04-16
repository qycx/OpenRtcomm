/********************************************************************************
** Form generated from reading UI file 'DlgAvAccept.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGAVACCEPT_H
#define UI_DLGAVACCEPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgAvAccept
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnFaceIcon;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *hint_name;
    QLabel *hint;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAccept;
    QLabel *label_2;
    QPushButton *btnCancel;
    QLabel *label;

    void setupUi(QWidget *DlgAvAccept)
    {
        if (DlgAvAccept->objectName().isEmpty())
            DlgAvAccept->setObjectName("DlgAvAccept");
        DlgAvAccept->resize(338, 140);
        DlgAvAccept->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border:none;\n"
"}\n"
"QWidget#DlgAvAccept{\n"
"background:#fff;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(DlgAvAccept);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(DlgAvAccept);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(8, 0, 0, 0);
        btnFaceIcon = new QToolButton(widget);
        btnFaceIcon->setObjectName("btnFaceIcon");
        btnFaceIcon->setStyleSheet(QString::fromUtf8("border:none;"));
        btnFaceIcon->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(btnFaceIcon);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(7, 0, 0, 0);
        hint_name = new QLabel(widget_3);
        hint_name->setObjectName("hint_name");
        hint_name->setMinimumSize(QSize(0, 40));
        hint_name->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("AdLib WGL4 BT")});
        font.setBold(false);
        hint_name->setFont(font);
        hint_name->setStyleSheet(QString::fromUtf8("font-size:18px;\n"
"font-weight:400;"));
        hint_name->setWordWrap(true);

        verticalLayout_2->addWidget(hint_name);

        hint = new QLabel(widget_3);
        hint->setObjectName("hint");
        hint->setMinimumSize(QSize(0, 20));
        hint->setMaximumSize(QSize(16777215, 15));
        hint->setWordWrap(true);

        verticalLayout_2->addWidget(hint);


        horizontalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(DlgAvAccept);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAccept = new QPushButton(widget_2);
        btnAccept->setObjectName("btnAccept");
        btnAccept->setMinimumSize(QSize(60, 50));
        btnAccept->setIconSize(QSize(60, 60));
        btnAccept->setAutoDefault(false);
        btnAccept->setFlat(false);

        horizontalLayout->addWidget(btnAccept);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(18, 0));

        horizontalLayout->addWidget(label_2);

        btnCancel = new QPushButton(widget_2);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setMinimumSize(QSize(60, 50));
        btnCancel->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(btnCancel);

        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setMinimumSize(QSize(18, 17));

        horizontalLayout->addWidget(label);


        verticalLayout->addWidget(widget_2);


        retranslateUi(DlgAvAccept);

        QMetaObject::connectSlotsByName(DlgAvAccept);
    } // setupUi

    void retranslateUi(QWidget *DlgAvAccept)
    {
        DlgAvAccept->setWindowTitle(QCoreApplication::translate("DlgAvAccept", "DlgAvAccept", nullptr));
        btnFaceIcon->setText(QString());
        hint_name->setText(QString());
        hint->setText(QString());
        btnAccept->setText(QCoreApplication::translate("DlgAvAccept", "Accept", nullptr));
        label_2->setText(QString());
        btnCancel->setText(QCoreApplication::translate("DlgAvAccept", "Cancel", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DlgAvAccept: public Ui_DlgAvAccept {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGAVACCEPT_H
