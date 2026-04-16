/********************************************************************************
** Form generated from reading UI file 'CQmcLogin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CQMCLOGIN_H
#define UI_CQMCLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CQmcLogin
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *winWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *bodywidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btn_img;
    QLabel *label_title;
    QLabel *label_status;

    void setupUi(QWidget *CQmcLogin)
    {
        if (CQmcLogin->objectName().isEmpty())
            CQmcLogin->setObjectName("CQmcLogin");
        CQmcLogin->resize(747, 453);
        CQmcLogin->setMinimumSize(QSize(747, 453));
        CQmcLogin->setMaximumSize(QSize(747, 453));
        CQmcLogin->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(CQmcLogin);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        winWidget = new QWidget(CQmcLogin);
        winWidget->setObjectName("winWidget");
        winWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(winWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        bodywidget = new QWidget(winWidget);
        bodywidget->setObjectName("bodywidget");
        bodywidget->setStyleSheet(QString::fromUtf8("background:none"));
        bodywidget->setProperty("bottomskin", QVariant(true));
        verticalLayout_3 = new QVBoxLayout(bodywidget);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(72, 90, 72, 40);
        btn_img = new QPushButton(bodywidget);
        btn_img->setObjectName("btn_img");
        btn_img->setMinimumSize(QSize(636, 628));
        btn_img->setMaximumSize(QSize(636, 628));

        verticalLayout_3->addWidget(btn_img, 0, Qt::AlignHCenter);

        label_title = new QLabel(bodywidget);
        label_title->setObjectName("label_title");

        verticalLayout_3->addWidget(label_title, 0, Qt::AlignHCenter);

        label_status = new QLabel(bodywidget);
        label_status->setObjectName("label_status");

        verticalLayout_3->addWidget(label_status, 0, Qt::AlignHCenter);


        horizontalLayout->addWidget(bodywidget, 0, Qt::AlignVCenter);


        horizontalLayout_2->addWidget(winWidget);


        retranslateUi(CQmcLogin);

        QMetaObject::connectSlotsByName(CQmcLogin);
    } // setupUi

    void retranslateUi(QWidget *CQmcLogin)
    {
        CQmcLogin->setWindowTitle(QCoreApplication::translate("CQmcLogin", "\347\231\273\345\275\225", nullptr));
        btn_img->setText(QString());
        label_title->setText(QCoreApplication::translate("CQmcLogin", "\345\217\214\345\220\221\350\256\244\350\257\201\344\270\255", nullptr));
        label_status->setText(QCoreApplication::translate("CQmcLogin", "\347\273\210\347\253\257\350\256\276\345\244\207\350\256\244\350\257\201\344\270\255...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CQmcLogin: public Ui_CQmcLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CQMCLOGIN_H
