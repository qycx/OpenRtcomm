/********************************************************************************
** Form generated from reading UI file 'CDlgNvrConfig.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGNVRCONFIG_H
#define UI_CDLGNVRCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgNvrConfigClass
{
public:
    QVBoxLayout *verticalLayout;
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
    QCheckBox *boxNvrEna;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_t3;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *boxNvrDh;
    QRadioButton *boxNvrHik;
    QRadioButton *boxNvrD4k;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_21;
    QWidget *widget_19;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_t4;
    QWidget *widget_20;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *NvrIp;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_10;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_t5;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *NvrName;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_13;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_t6;
    QWidget *widget_16;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *NvrPwd;
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

    void setupUi(QDialog *CDlgNvrConfigClass)
    {
        if (CDlgNvrConfigClass->objectName().isEmpty())
            CDlgNvrConfigClass->setObjectName("CDlgNvrConfigClass");
        CDlgNvrConfigClass->resize(815, 636);
        verticalLayout = new QVBoxLayout(CDlgNvrConfigClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgNvrConfigClass);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(100, -1, 100, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

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
        boxNvrEna = new QCheckBox(widget_9);
        boxNvrEna->setObjectName("boxNvrEna");
        boxNvrEna->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(boxNvrEna);


        horizontalLayout->addWidget(widget_9, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_7);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName("widget_6");
        widget_6->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_11 = new QWidget(widget_6);
        widget_11->setObjectName("widget_11");
        horizontalLayout_6 = new QHBoxLayout(widget_11);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(-1, 4, -1, -1);
        label_t3 = new QLabel(widget_11);
        label_t3->setObjectName("label_t3");

        horizontalLayout_6->addWidget(label_t3);


        horizontalLayout_5->addWidget(widget_11, 0, Qt::AlignRight);

        widget_12 = new QWidget(widget_6);
        widget_12->setObjectName("widget_12");
        horizontalLayout_7 = new QHBoxLayout(widget_12);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, 4, -1, -1);
        boxNvrDh = new QRadioButton(widget_12);
        boxNvrDh->setObjectName("boxNvrDh");

        horizontalLayout_7->addWidget(boxNvrDh);

        boxNvrHik = new QRadioButton(widget_12);
        boxNvrHik->setObjectName("boxNvrHik");

        horizontalLayout_7->addWidget(boxNvrHik);

        boxNvrD4k = new QRadioButton(widget_12);
        boxNvrD4k->setObjectName("boxNvrD4k");

        horizontalLayout_7->addWidget(boxNvrD4k);


        horizontalLayout_5->addWidget(widget_12);


        verticalLayout_2->addWidget(widget_6);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_21 = new QHBoxLayout(widget_5);
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        horizontalLayout_21->setContentsMargins(0, 0, 0, 0);
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


        horizontalLayout_21->addWidget(widget_19, 0, Qt::AlignRight);

        widget_20 = new QWidget(widget_5);
        widget_20->setObjectName("widget_20");
        horizontalLayout_20 = new QHBoxLayout(widget_20);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        horizontalLayout_20->setContentsMargins(-1, 4, -1, -1);
        NvrIp = new QLineEdit(widget_20);
        NvrIp->setObjectName("NvrIp");

        horizontalLayout_20->addWidget(NvrIp);


        horizontalLayout_21->addWidget(widget_20, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_5);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_10 = new QHBoxLayout(widget_2);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        widget_14 = new QWidget(widget_2);
        widget_14->setObjectName("widget_14");
        horizontalLayout_9 = new QHBoxLayout(widget_14);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(-1, 4, -1, -1);
        label_t5 = new QLabel(widget_14);
        label_t5->setObjectName("label_t5");

        horizontalLayout_9->addWidget(label_t5, 0, Qt::AlignRight);


        horizontalLayout_10->addWidget(widget_14, 0, Qt::AlignRight);

        widget_13 = new QWidget(widget_2);
        widget_13->setObjectName("widget_13");
        horizontalLayout_8 = new QHBoxLayout(widget_13);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(-1, 4, -1, -1);
        NvrName = new QLineEdit(widget_13);
        NvrName->setObjectName("NvrName");

        horizontalLayout_8->addWidget(NvrName);


        horizontalLayout_10->addWidget(widget_13, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        widget_3->setStyleSheet(QString::fromUtf8("background:none;"));
        horizontalLayout_13 = new QHBoxLayout(widget_3);
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        widget_15 = new QWidget(widget_3);
        widget_15->setObjectName("widget_15");
        horizontalLayout_11 = new QHBoxLayout(widget_15);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(-1, 4, -1, -1);
        label_t6 = new QLabel(widget_15);
        label_t6->setObjectName("label_t6");

        horizontalLayout_11->addWidget(label_t6, 0, Qt::AlignRight);


        horizontalLayout_13->addWidget(widget_15, 0, Qt::AlignRight);

        widget_16 = new QWidget(widget_3);
        widget_16->setObjectName("widget_16");
        horizontalLayout_12 = new QHBoxLayout(widget_16);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(-1, 4, -1, -1);
        NvrPwd = new QLineEdit(widget_16);
        NvrPwd->setObjectName("NvrPwd");

        horizontalLayout_12->addWidget(NvrPwd);


        horizontalLayout_13->addWidget(widget_16, 0, Qt::AlignLeft);


        verticalLayout_2->addWidget(widget_3);

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


        verticalLayout->addWidget(widget);


        retranslateUi(CDlgNvrConfigClass);

        QMetaObject::connectSlotsByName(CDlgNvrConfigClass);
    } // setupUi

    void retranslateUi(QDialog *CDlgNvrConfigClass)
    {
        CDlgNvrConfigClass->setWindowTitle(QCoreApplication::translate("CDlgNvrConfigClass", "CDlgNvrConfig", nullptr));
        label_t1->setText(QCoreApplication::translate("CDlgNvrConfigClass", "NVR\350\256\276\347\275\256", nullptr));
        label_t2->setText(QCoreApplication::translate("CDlgNvrConfigClass", "\346\230\257\345\220\246\345\274\200\345\220\257NVR\357\274\232", nullptr));
        boxNvrEna->setText(QCoreApplication::translate("CDlgNvrConfigClass", "\345\274\200\345\220\257", nullptr));
        label_t3->setText(QCoreApplication::translate("CDlgNvrConfigClass", "NVR\350\256\276\345\244\207\347\261\273\345\236\213\357\274\232", nullptr));
        boxNvrDh->setText(QCoreApplication::translate("CDlgNvrConfigClass", "\345\244\247\345\215\216", nullptr));
        boxNvrHik->setText(QCoreApplication::translate("CDlgNvrConfigClass", "\346\265\267\345\272\267", nullptr));
        boxNvrD4k->setText(QCoreApplication::translate("CDlgNvrConfigClass", "D4k", nullptr));
        label_t4->setText(QCoreApplication::translate("CDlgNvrConfigClass", "NVR IP\345\234\260\345\235\200\357\274\232", nullptr));
        label_t5->setText(QCoreApplication::translate("CDlgNvrConfigClass", "NVR \347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_t6->setText(QCoreApplication::translate("CDlgNvrConfigClass", "NVR \345\257\206\347\240\201\357\274\232", nullptr));
        btnOk->setText(QCoreApplication::translate("CDlgNvrConfigClass", "\347\241\256\350\256\244", nullptr));
        err_txt->setText(QCoreApplication::translate("CDlgNvrConfigClass", "err", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgNvrConfigClass: public Ui_CDlgNvrConfigClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGNVRCONFIG_H
