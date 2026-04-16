/********************************************************************************
** Form generated from reading UI file 'CDlgShareConfig.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGSHARECONFIG_H
#define UI_CDLGSHARECONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgShareConfigClass
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_t1;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_t2;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *boxEnableShare;
    QWidget *widget_71;
    QHBoxLayout *horizontalLayout1;
    QWidget *widget_81;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_t3;
    QWidget *widget_91;
    QHBoxLayout *horizontalLayout_41;
    QCheckBox *boxAutoShare;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_211;
    QWidget *widget_19;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_t4;
    QWidget *widget_20;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *rtspUrl;
    QWidget *widget_21;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_23;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_22;
    QHBoxLayout *horizontalLayout_23;
    QPushButton *btnOk;
    QWidget *err_widget;
    QVBoxLayout *verticalLayout_5;
    QLabel *err_txt;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *CDlgShareConfigClass)
    {
        if (CDlgShareConfigClass->objectName().isEmpty())
            CDlgShareConfigClass->setObjectName("CDlgShareConfigClass");
        CDlgShareConfigClass->resize(791, 633);
        widget = new QWidget(CDlgShareConfigClass);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 815, 636));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(100, -1, 100, -1);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget_10 = new QWidget(widget);
        widget_10->setObjectName("widget_10");
        widget_10->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_3 = new QHBoxLayout(widget_10);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_t1 = new QLabel(widget_10);
        label_t1->setObjectName("label_t1");
        label_t1->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(label_t1);


        verticalLayout_2->addWidget(widget_10);

        widget_7 = new QWidget(widget);
        widget_7->setObjectName("widget_7");
        widget_7->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout = new QHBoxLayout(widget_7);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_8 = new QWidget(widget_7);
        widget_8->setObjectName("widget_8");
        horizontalLayout_2 = new QHBoxLayout(widget_8);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 4, -1, -1);
        label_t2 = new QLabel(widget_8);
        label_t2->setObjectName("label_t2");

        horizontalLayout_2->addWidget(label_t2);


        horizontalLayout->addWidget(widget_8, 0, Qt::AlignRight);

        widget_9 = new QWidget(widget_7);
        widget_9->setObjectName("widget_9");
        horizontalLayout_4 = new QHBoxLayout(widget_9);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 4, -1, -1);
        boxEnableShare = new QCheckBox(widget_9);
        boxEnableShare->setObjectName("boxEnableShare");
        boxEnableShare->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(boxEnableShare);


        horizontalLayout->addWidget(widget_9, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_7);

        widget_71 = new QWidget(widget);
        widget_71->setObjectName("widget_71");
        widget_71->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout1 = new QHBoxLayout(widget_71);
        horizontalLayout1->setSpacing(0);
        horizontalLayout1->setContentsMargins(11, 11, 11, 11);
        horizontalLayout1->setObjectName("horizontalLayout1");
        horizontalLayout1->setContentsMargins(0, 0, 0, 0);
        widget_81 = new QWidget(widget_71);
        widget_81->setObjectName("widget_81");
        horizontalLayout_21 = new QHBoxLayout(widget_81);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        horizontalLayout_21->setContentsMargins(-1, 4, -1, -1);
        label_t3 = new QLabel(widget_81);
        label_t3->setObjectName("label_t3");

        horizontalLayout_21->addWidget(label_t3);


        horizontalLayout1->addWidget(widget_81, 0, Qt::AlignRight);

        widget_91 = new QWidget(widget_71);
        widget_91->setObjectName("widget_91");
        horizontalLayout_41 = new QHBoxLayout(widget_91);
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_41->setObjectName("horizontalLayout_41");
        horizontalLayout_41->setContentsMargins(-1, 4, -1, -1);
        boxAutoShare = new QCheckBox(widget_91);
        boxAutoShare->setObjectName("boxAutoShare");
        boxAutoShare->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_41->addWidget(boxAutoShare);


        horizontalLayout1->addWidget(widget_91, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_71);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_211 = new QHBoxLayout(widget_5);
        horizontalLayout_211->setSpacing(0);
        horizontalLayout_211->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_211->setObjectName("horizontalLayout_211");
        horizontalLayout_211->setContentsMargins(0, 0, 0, 0);
        widget_19 = new QWidget(widget_5);
        widget_19->setObjectName("widget_19");
        horizontalLayout_19 = new QHBoxLayout(widget_19);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalLayout_19->setContentsMargins(-1, 4, -1, -1);
        label_t4 = new QLabel(widget_19);
        label_t4->setObjectName("label_t4");

        horizontalLayout_19->addWidget(label_t4, 0, Qt::AlignRight);


        horizontalLayout_211->addWidget(widget_19, 0, Qt::AlignRight);

        widget_20 = new QWidget(widget_5);
        widget_20->setObjectName("widget_20");
        horizontalLayout_20 = new QHBoxLayout(widget_20);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        horizontalLayout_20->setContentsMargins(-1, 4, -1, -1);
        rtspUrl = new QLineEdit(widget_20);
        rtspUrl->setObjectName("rtspUrl");

        horizontalLayout_20->addWidget(rtspUrl);


        horizontalLayout_211->addWidget(widget_20, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_5);

        widget_21 = new QWidget(widget);
        widget_21->setObjectName("widget_21");
        widget_21->setStyleSheet(QString::fromUtf8("background:none;"));
        verticalLayout_3 = new QVBoxLayout(widget_21);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(widget_21);

        widget_23 = new QWidget(widget);
        widget_23->setObjectName("widget_23");
        widget_23->setStyleSheet(QString::fromUtf8("background:none;"));
        verticalLayout_4 = new QVBoxLayout(widget_23);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(-1, 10, -1, -1);
        widget_22 = new QWidget(widget_23);
        widget_22->setObjectName("widget_22");
        horizontalLayout_23 = new QHBoxLayout(widget_22);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        horizontalLayout_23->setContentsMargins(-1, 0, -1, -1);
        btnOk = new QPushButton(widget_22);
        btnOk->setObjectName("btnOk");

        horizontalLayout_23->addWidget(btnOk, 0, Qt::AlignLeft);


        verticalLayout_4->addWidget(widget_22, 0, Qt::AlignHCenter);

        err_widget = new QWidget(widget_23);
        err_widget->setObjectName("err_widget");
        verticalLayout_5 = new QVBoxLayout(err_widget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        err_txt = new QLabel(err_widget);
        err_txt->setObjectName("err_txt");

        verticalLayout_5->addWidget(err_txt);


        verticalLayout_4->addWidget(err_widget, 0, Qt::AlignHCenter);


        verticalLayout_2->addWidget(widget_23);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(CDlgShareConfigClass);

        QMetaObject::connectSlotsByName(CDlgShareConfigClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgShareConfigClass)
    {
        CDlgShareConfigClass->setWindowTitle(QCoreApplication::translate("CDlgShareConfigClass", "CDlgShareConfig", nullptr));
        label_t1->setText(QCoreApplication::translate("CDlgShareConfigClass", "\345\205\261\344\272\253\350\256\276\347\275\256", nullptr));
        label_t2->setText(QCoreApplication::translate("CDlgShareConfigClass", "\346\230\257\345\220\246\345\220\257\347\224\250\345\205\261\344\272\253\357\274\232", nullptr));
        boxEnableShare->setText(QCoreApplication::translate("CDlgShareConfigClass", "\345\220\257\347\224\250\345\205\261\344\272\253", nullptr));
        label_t3->setText(QCoreApplication::translate("CDlgShareConfigClass", "\350\207\252\345\212\250\345\274\200\345\220\257\345\205\261\344\272\253\357\274\232", nullptr));
        boxAutoShare->setText(QCoreApplication::translate("CDlgShareConfigClass", "\350\207\252\345\212\250\345\274\200\345\220\257", nullptr));
        label_t4->setText(QCoreApplication::translate("CDlgShareConfigClass", "Rtsp Url\357\274\232", nullptr));
        btnOk->setText(QCoreApplication::translate("CDlgShareConfigClass", "\347\241\256\350\256\244", nullptr));
        err_txt->setText(QCoreApplication::translate("CDlgShareConfigClass", "err", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgShareConfigClass: public Ui_CDlgShareConfigClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGSHARECONFIG_H
