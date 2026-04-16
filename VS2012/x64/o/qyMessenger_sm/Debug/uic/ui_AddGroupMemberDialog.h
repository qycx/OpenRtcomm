/********************************************************************************
** Form generated from reading UI file 'AddGroupMemberDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDGROUPMEMBERDIALOG_H
#define UI_ADDGROUPMEMBERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddGroupMemberDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QWidget *wid_search;
    QHBoxLayout *horizontalLayout_7;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidget;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnClose;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLineEdit *groupName;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lab_count_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *lab_count;
    QListWidget *listWidget_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *AddGroupMemberDialog)
    {
        if (AddGroupMemberDialog->objectName().isEmpty())
            AddGroupMemberDialog->setObjectName("AddGroupMemberDialog");
        AddGroupMemberDialog->resize(750, 600);
        AddGroupMemberDialog->setMinimumSize(QSize(750, 600));
        AddGroupMemberDialog->setMaximumSize(QSize(750, 600));
        horizontalLayout = new QHBoxLayout(AddGroupMemberDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(AddGroupMemberDialog);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget\n"
"{\n"
"  background:#fafafa;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(350, 0));
        widget_2->setMaximumSize(QSize(350, 16777215));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget#widget_2\n"
"{\n"
"  border-right:1px solid #e7e7e7;\n"
"}"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 20, 1, 1);
        wid_search = new QWidget(widget_2);
        wid_search->setObjectName("wid_search");
        wid_search->setMinimumSize(QSize(0, 24));
        wid_search->setMaximumSize(QSize(16777215, 24));
        horizontalLayout_7 = new QHBoxLayout(wid_search);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        widget_8 = new QWidget(wid_search);
        widget_8->setObjectName("widget_8");
        widget_8->setMinimumSize(QSize(220, 0));
        widget_8->setMaximumSize(QSize(220, 16777215));
        widget_8->setStyleSheet(QString::fromUtf8("#widget_8\n"
"{\n"
"border:1px solid #dddddd;\n"
"border-radius:5%;\n"
" }"));
        horizontalLayout_8 = new QHBoxLayout(widget_8);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(4, 0, 4, 0);
        label_3 = new QLabel(widget_8);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(20, 20));
        label_3->setMaximumSize(QSize(20, 20));
        label_3->setStyleSheet(QString::fromUtf8("image:url(:/Resources/Images/WinMain/serch.png)"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_3);

        lineEdit_2 = new QLineEdit(widget_8);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setStyleSheet(QString::fromUtf8("border:none;"));
        lineEdit_2->setClearButtonEnabled(true);

        horizontalLayout_8->addWidget(lineEdit_2);


        horizontalLayout_7->addWidget(widget_8);


        verticalLayout->addWidget(wid_search);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(widget_4);
        listWidget->setObjectName("listWidget");
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget\n"
"{\n"
"border:none;\n"
"background:transparent;\n"
"}\n"
"QListWidget::item{background:transparent;}"));

        horizontalLayout_3->addWidget(listWidget);


        verticalLayout->addWidget(widget_4);


        horizontalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(1, 2, 1, 10);
        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName("widget_9");
        widget_9->setMinimumSize(QSize(0, 20));
        verticalLayout_3 = new QVBoxLayout(widget_9);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnClose = new QPushButton(widget_9);
        btnClose->setObjectName("btnClose");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnClose->sizePolicy().hasHeightForWidth());
        btnClose->setSizePolicy(sizePolicy);
        btnClose->setMinimumSize(QSize(20, 20));
        btnClose->setMaximumSize(QSize(20, 20));
        btnClose->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnClose->setStyleSheet(QString::fromUtf8("border:none;"));

        verticalLayout_3->addWidget(btnClose, 0, Qt::AlignRight);


        verticalLayout_2->addWidget(widget_9);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName("widget_7");
        widget_7->setMinimumSize(QSize(0, 30));
        widget_7->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(20, 0, 15, 0);
        label_2 = new QLabel(widget_7);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color:#000;\n"
"font-weight:500;"));

        horizontalLayout_6->addWidget(label_2);

        groupName = new QLineEdit(widget_7);
        groupName->setObjectName("groupName");
        groupName->setMinimumSize(QSize(233, 0));
        groupName->setStyleSheet(QString::fromUtf8("border-radius:5%;\n"
"border:1px solid #eee;"));
        groupName->setClearButtonEnabled(true);

        horizontalLayout_6->addWidget(groupName);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        lab_count_2 = new QLabel(widget_7);
        lab_count_2->setObjectName("lab_count_2");
        lab_count_2->setStyleSheet(QString::fromUtf8("color:#666666;"));

        horizontalLayout_6->addWidget(lab_count_2);


        verticalLayout_2->addWidget(widget_7);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 24));
        widget_5->setMaximumSize(QSize(16777215, 24));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(20, 0, 15, 0);
        label = new QLabel(widget_5);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color:#666666;"));

        horizontalLayout_4->addWidget(label);

        horizontalSpacer = new QSpacerItem(112, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        lab_count = new QLabel(widget_5);
        lab_count->setObjectName("lab_count");
        lab_count->setStyleSheet(QString::fromUtf8("color:#666666;"));

        horizontalLayout_4->addWidget(lab_count);


        verticalLayout_2->addWidget(widget_5);

        listWidget_2 = new QListWidget(widget_3);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setStyleSheet(QString::fromUtf8("QListWidget\n"
"{\n"
"border:none;\n"
"background:transparent;\n"
"}\n"
"QListWidget::item{background:transparent;}"));

        verticalLayout_2->addWidget(listWidget_2);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(0, 30));
        widget_6->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 10, 0);
        horizontalSpacer_2 = new QSpacerItem(77, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(widget_6);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(80, 30));
        pushButton->setMaximumSize(QSize(80, 30));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border:none;\n"
"color:#ffffff;\n"
"background:rgb(22,154,218);\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border-radius:5%;\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
" background:rgb(22,154,218);\n"
"}"));

        horizontalLayout_5->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_6);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(80, 30));
        pushButton_2->setMaximumSize(QSize(80, 30));
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border:none;\n"
"color:#ffffff;\n"
"background:gray;\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border-radius:5%;\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
" background:gray;\n"
"}"));

        horizontalLayout_5->addWidget(pushButton_2);


        verticalLayout_2->addWidget(widget_6);


        horizontalLayout_2->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(AddGroupMemberDialog);
        QObject::connect(pushButton_2, &QPushButton::clicked, AddGroupMemberDialog, qOverload<>(&QDialog::close));
        QObject::connect(pushButton, SIGNAL(clicked()), AddGroupMemberDialog, SLOT(slot_button()));
        QObject::connect(lineEdit_2, SIGNAL(textChanged(QString)), AddGroupMemberDialog, SLOT(slot_text_changed(QString)));
        QObject::connect(btnClose, &QPushButton::clicked, AddGroupMemberDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(AddGroupMemberDialog);
    } // setupUi

    void retranslateUi(QDialog *AddGroupMemberDialog)
    {
        AddGroupMemberDialog->setWindowTitle(QCoreApplication::translate("AddGroupMemberDialog", "AddGroupMemberDialog", nullptr));
        label_3->setText(QString());
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("AddGroupMemberDialog", "\346\220\234\347\264\242", nullptr));
        btnClose->setText(QString());
        label_2->setText(QCoreApplication::translate("AddGroupMemberDialog", "\347\276\244\345\220\215\347\247\260:", nullptr));
        groupName->setPlaceholderText(QCoreApplication::translate("AddGroupMemberDialog", "\350\276\223\345\205\245\347\276\244\345\220\215\347\247\260", nullptr));
        lab_count_2->setText(QString());
        label->setText(QCoreApplication::translate("AddGroupMemberDialog", "\350\257\267\345\213\276\351\200\211\350\246\201\346\267\273\345\212\240\347\232\204\350\201\224\347\263\273\344\272\272", nullptr));
        lab_count->setText(QString());
        pushButton->setText(QCoreApplication::translate("AddGroupMemberDialog", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AddGroupMemberDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddGroupMemberDialog: public Ui_AddGroupMemberDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDGROUPMEMBERDIALOG_H
