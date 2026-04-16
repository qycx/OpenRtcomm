/********************************************************************************
** Form generated from reading UI file 'WinSystemPwd.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSYSTEMPWD_H
#define UI_WINSYSTEMPWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinSystemPwd
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_passwd1;
    QLineEdit *lineEdit_passwd0;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLabel *label_name;
    QLabel *label_hint;

    void setupUi(QWidget *WinSystemPwd)
    {
        if (WinSystemPwd->objectName().isEmpty())
            WinSystemPwd->setObjectName("WinSystemPwd");
        WinSystemPwd->resize(546, 370);
        horizontalLayout = new QHBoxLayout(WinSystemPwd);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(WinSystemPwd);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("font-size:17px;\n"
""));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 50));
        label_2->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 50));
        label_3->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_passwd1 = new QLineEdit(widget);
        lineEdit_passwd1->setObjectName("lineEdit_passwd1");
        lineEdit_passwd1->setMinimumSize(QSize(0, 30));
        lineEdit_passwd1->setMaximumSize(QSize(16777215, 30));
        lineEdit_passwd1->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_passwd1, 2, 1, 1, 1);

        lineEdit_passwd0 = new QLineEdit(widget);
        lineEdit_passwd0->setObjectName("lineEdit_passwd0");
        lineEdit_passwd0->setMinimumSize(QSize(0, 30));
        lineEdit_passwd0->setMaximumSize(QSize(16777215, 30));
        lineEdit_passwd0->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_passwd0, 1, 1, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 40));
        pushButton->setMaximumSize(QSize(100, 40));
        pushButton->setStyleSheet(QString::fromUtf8("background:rgb(22, 154, 218);\n"
"border:none;\n"
"color:#fff;\n"
"border-radius:5%;"));

        gridLayout->addWidget(pushButton, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 50));
        label->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_name = new QLabel(widget);
        label_name->setObjectName("label_name");
        label_name->setMinimumSize(QSize(0, 50));
        label_name->setMaximumSize(QSize(16777215, 50));
        label_name->setStyleSheet(QString::fromUtf8("font-weight:500;"));

        gridLayout->addWidget(label_name, 0, 1, 1, 1);

        label_hint = new QLabel(widget);
        label_hint->setObjectName("label_hint");
        label_hint->setStyleSheet(QString::fromUtf8("color:red;"));

        gridLayout->addWidget(label_hint, 3, 1, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(WinSystemPwd);

        QMetaObject::connectSlotsByName(WinSystemPwd);
    } // setupUi

    void retranslateUi(QWidget *WinSystemPwd)
    {
        WinSystemPwd->setWindowTitle(QCoreApplication::translate("WinSystemPwd", "WinSystemPwd", nullptr));
        label_2->setText(QCoreApplication::translate("WinSystemPwd", "\350\276\223\345\205\245\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("WinSystemPwd", "\347\241\256\350\256\244\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        lineEdit_passwd1->setText(QString());
        pushButton->setText(QCoreApplication::translate("WinSystemPwd", "\347\241\256 \350\256\244", nullptr));
        label->setText(QCoreApplication::translate("WinSystemPwd", "\350\201\224\347\263\273\344\272\272\350\264\246\346\210\267\357\274\232", nullptr));
        label_name->setText(QString());
        label_hint->setText(QCoreApplication::translate("WinSystemPwd", "\346\226\260\345\257\206\347\240\201\344\270\215\344\270\200\350\207\264\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinSystemPwd: public Ui_WinSystemPwd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSYSTEMPWD_H
