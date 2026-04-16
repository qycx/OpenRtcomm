/********************************************************************************
** Form generated from reading UI file 'QualitySelSetDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUALITYSELSETDIALOG_H
#define UI_QUALITYSELSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QualitySelSetDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *closeBtn;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QPushButton *Btn_1080p;
    QPushButton *Btn_720p;
    QPushButton *Btn_480p;
    QPushButton *Btn_240p;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *label_desc;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *comboBox_codec;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *comboBox_usMaxSpeakers;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_8;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_err;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_6;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *QualitySelSetDialog)
    {
        if (QualitySelSetDialog->objectName().isEmpty())
            QualitySelSetDialog->setObjectName("QualitySelSetDialog");
        QualitySelSetDialog->resize(550, 450);
        QualitySelSetDialog->setMinimumSize(QSize(550, 450));
        QualitySelSetDialog->setMaximumSize(QSize(550, 450));
        QualitySelSetDialog->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 1px solid #dddddd; \n"
"    padding: 1px 18px 1px 3px; \n"
"    color: #000;\n"
"    background: transparent;\n"
"padding-left:10px;\n"
"}\n"
"QLabel{\n"
"font-size:18px;\n"
"}\n"
"QComboBox QAbstractItemView::item {\n"
"    height: 26px;  \n"
"}\n"
"QComboBox::drop-down {\n"
"      subcontrol-origin: padding; \n"
"    subcontrol-position: top right; \n"
"    width: 15px;\n"
"padding-right:6px;\n"
" border:none;\n"
"}\n"
"QComboBox::down-arrow {\n"
"width: 15px; \n"
"\343\200\200\343\200\200background: transparent; \n"
"\343\200\200\343\200\200padding: 0px 0px 0px 0px;\n"
"	image: url(:/Resources/Images/WinMain/drop.png);\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(QualitySelSetDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(QualitySelSetDialog);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget\n"
"{\n"
" 	border:1px solid rgb(211,211,211);\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(20);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 20);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:20px;"));

        horizontalLayout_2->addWidget(label);

        closeBtn = new QPushButton(widget_2);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setMinimumSize(QSize(30, 30));
        closeBtn->setMaximumSize(QSize(30, 30));
        closeBtn->setInputMethodHints(Qt::ImhNone);
        closeBtn->setIconSize(QSize(30, 30));
        closeBtn->setAutoDefault(true);
        closeBtn->setFlat(true);

        horizontalLayout_2->addWidget(closeBtn);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(15, 0, 0, 0);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(0, 30));
        widget_4->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(200, 0));
        label_2->setMaximumSize(QSize(200, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(widget_4);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(120, 26));
        comboBox->setMaximumSize(QSize(16777215, 26));
        comboBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 35));
        widget_5->setMaximumSize(QSize(16777215, 35));
        widget_5->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"  border:1px solid #dddddd;\n"
"   border-radius:5%;\n"
"}\n"
"QPushButton:checked\n"
"{\n"
" background:#1296db;\n"
"color:#ffffff;\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_5);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(200, 0));
        label_3->setMaximumSize(QSize(200, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        Btn_1080p = new QPushButton(widget_5);
        buttonGroup = new QButtonGroup(QualitySelSetDialog);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(Btn_1080p);
        Btn_1080p->setObjectName("Btn_1080p");
        Btn_1080p->setMinimumSize(QSize(55, 30));
        Btn_1080p->setMaximumSize(QSize(55, 26));
        Btn_1080p->setCheckable(true);
        Btn_1080p->setChecked(false);

        horizontalLayout_4->addWidget(Btn_1080p);

        Btn_720p = new QPushButton(widget_5);
        buttonGroup->addButton(Btn_720p);
        Btn_720p->setObjectName("Btn_720p");
        Btn_720p->setMinimumSize(QSize(45, 30));
        Btn_720p->setMaximumSize(QSize(40, 26));
        Btn_720p->setCheckable(true);
        Btn_720p->setChecked(false);

        horizontalLayout_4->addWidget(Btn_720p);

        Btn_480p = new QPushButton(widget_5);
        buttonGroup->addButton(Btn_480p);
        Btn_480p->setObjectName("Btn_480p");
        Btn_480p->setMinimumSize(QSize(45, 30));
        Btn_480p->setMaximumSize(QSize(45, 30));
        Btn_480p->setCheckable(true);
        Btn_480p->setChecked(false);

        horizontalLayout_4->addWidget(Btn_480p);

        Btn_240p = new QPushButton(widget_5);
        buttonGroup->addButton(Btn_240p);
        Btn_240p->setObjectName("Btn_240p");
        Btn_240p->setMinimumSize(QSize(45, 30));
        Btn_240p->setMaximumSize(QSize(45, 30));
        Btn_240p->setCheckable(true);
        Btn_240p->setChecked(false);

        horizontalLayout_4->addWidget(Btn_240p);

        horizontalSpacer_2 = new QSpacerItem(148, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(0, 60));
        widget_6->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget_6);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(200, 0));
        label_4->setMaximumSize(QSize(200, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_4);

        label_desc = new QLabel(widget_6);
        label_desc->setObjectName("label_desc");
        label_desc->setStyleSheet(QString::fromUtf8("font-size:12px;"));
        label_desc->setWordWrap(true);

        horizontalLayout_5->addWidget(label_desc);


        verticalLayout_2->addWidget(widget_6);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName("widget_7");
        widget_7->setMinimumSize(QSize(0, 30));
        widget_7->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget_7);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(200, 0));
        label_6->setMaximumSize(QSize(200, 16777215));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_6);

        comboBox_codec = new QComboBox(widget_7);
        comboBox_codec->addItem(QString());
        comboBox_codec->addItem(QString());
        comboBox_codec->addItem(QString());
        comboBox_codec->setObjectName("comboBox_codec");
        comboBox_codec->setMinimumSize(QSize(120, 26));
        comboBox_codec->setMaximumSize(QSize(16777215, 26));
        comboBox_codec->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(comboBox_codec);

        horizontalSpacer_3 = new QSpacerItem(148, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(widget_7);

        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName("widget_8");
        widget_8->setMinimumSize(QSize(0, 30));
        widget_8->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setSpacing(10);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget_8);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(200, 0));
        label_7->setMaximumSize(QSize(200, 16777215));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_7);

        comboBox_usMaxSpeakers = new QComboBox(widget_8);
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->addItem(QString());
        comboBox_usMaxSpeakers->setObjectName("comboBox_usMaxSpeakers");
        comboBox_usMaxSpeakers->setMinimumSize(QSize(120, 26));
        comboBox_usMaxSpeakers->setMaximumSize(QSize(16777215, 26));
        comboBox_usMaxSpeakers->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_7->addWidget(comboBox_usMaxSpeakers);

        horizontalSpacer_4 = new QSpacerItem(141, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(widget_8);

        label_8 = new QLabel(widget_3);
        label_8->setObjectName("label_8");

        verticalLayout_2->addWidget(label_8);

        widget_11 = new QWidget(widget_3);
        widget_11->setObjectName("widget_11");
        widget_11->setMinimumSize(QSize(0, 40));
        widget_11->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_11 = new QHBoxLayout(widget_11);
        horizontalLayout_11->setSpacing(10);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 20, 0);
        label_err = new QLabel(widget_11);
        label_err->setObjectName("label_err");
        label_err->setStyleSheet(QString::fromUtf8("font-size:22px;\n"
"color:red;"));

        horizontalLayout_11->addWidget(label_err);

        horizontalSpacer_8 = new QSpacerItem(225, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_8);

        pushButton_6 = new QPushButton(widget_11);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(60, 30));
        pushButton_6->setMaximumSize(QSize(60, 30));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:none;\n"
" background:#1296db;\n"
"color:#ffffff;\n"
"border-radius:5%;\n"
"}"));

        horizontalLayout_11->addWidget(pushButton_6);


        verticalLayout_2->addWidget(widget_11);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(QualitySelSetDialog);
        QObject::connect(Btn_1080p, SIGNAL(toggled(bool)), QualitySelSetDialog, SLOT(slot_resulation_toggled(bool)));
        QObject::connect(Btn_720p, SIGNAL(toggled(bool)), QualitySelSetDialog, SLOT(slot_resulation_toggled(bool)));
        QObject::connect(Btn_240p, SIGNAL(toggled(bool)), QualitySelSetDialog, SLOT(slot_resulation_toggled(bool)));
        QObject::connect(pushButton_6, SIGNAL(clicked()), QualitySelSetDialog, SLOT(slot_button_ok()));
        QObject::connect(closeBtn, &QPushButton::clicked, QualitySelSetDialog, qOverload<>(&QDialog::close));
        QObject::connect(Btn_480p, SIGNAL(toggled(bool)), QualitySelSetDialog, SLOT(slot_resulation_toggled(bool)));

        QMetaObject::connectSlotsByName(QualitySelSetDialog);
    } // setupUi

    void retranslateUi(QDialog *QualitySelSetDialog)
    {
        QualitySelSetDialog->setWindowTitle(QCoreApplication::translate("QualitySelSetDialog", "QualitySelSetDialog", nullptr));
        label->setText(QCoreApplication::translate("QualitySelSetDialog", "\344\274\232\350\256\256\350\256\276\347\275\256", nullptr));
        closeBtn->setText(QString());
        label_2->setText(QCoreApplication::translate("QualitySelSetDialog", "\347\247\215\347\261\273:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("QualitySelSetDialog", "AV", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("QualitySelSetDialog", "Webcam", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("QualitySelSetDialog", "Screen", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("QualitySelSetDialog", "Media File", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("QualitySelSetDialog", "Mddia Device", nullptr));

        label_3->setText(QCoreApplication::translate("QualitySelSetDialog", "\344\274\232\350\256\256\350\247\206\351\242\221:", nullptr));
        Btn_1080p->setText(QCoreApplication::translate("QualitySelSetDialog", "\345\205\250\351\253\230\346\270\205", nullptr));
        Btn_720p->setText(QCoreApplication::translate("QualitySelSetDialog", "\351\253\230\346\270\205", nullptr));
        Btn_480p->setText(QCoreApplication::translate("QualitySelSetDialog", "480p", nullptr));
        Btn_240p->setText(QCoreApplication::translate("QualitySelSetDialog", "240p", nullptr));
        label_4->setText(QCoreApplication::translate("QualitySelSetDialog", "\347\224\273\350\264\250\346\217\217\350\277\260:", nullptr));
        label_desc->setText(QString());
        label_6->setText(QCoreApplication::translate("QualitySelSetDialog", "Video Codec:", nullptr));
        comboBox_codec->setItemText(0, QCoreApplication::translate("QualitySelSetDialog", "VP80", nullptr));
        comboBox_codec->setItemText(1, QCoreApplication::translate("QualitySelSetDialog", "h264", nullptr));
        comboBox_codec->setItemText(2, QCoreApplication::translate("QualitySelSetDialog", "HEVC", nullptr));

        label_7->setText(QCoreApplication::translate("QualitySelSetDialog", "\346\234\200\345\244\232\345\217\221\350\250\200\346\225\260(1-16):", nullptr));
        comboBox_usMaxSpeakers->setItemText(0, QCoreApplication::translate("QualitySelSetDialog", "1", nullptr));
        comboBox_usMaxSpeakers->setItemText(1, QCoreApplication::translate("QualitySelSetDialog", "2", nullptr));
        comboBox_usMaxSpeakers->setItemText(2, QCoreApplication::translate("QualitySelSetDialog", "3", nullptr));
        comboBox_usMaxSpeakers->setItemText(3, QCoreApplication::translate("QualitySelSetDialog", "4", nullptr));
        comboBox_usMaxSpeakers->setItemText(4, QCoreApplication::translate("QualitySelSetDialog", "5", nullptr));
        comboBox_usMaxSpeakers->setItemText(5, QCoreApplication::translate("QualitySelSetDialog", "6", nullptr));
        comboBox_usMaxSpeakers->setItemText(6, QCoreApplication::translate("QualitySelSetDialog", "7", nullptr));
        comboBox_usMaxSpeakers->setItemText(7, QCoreApplication::translate("QualitySelSetDialog", "8", nullptr));
        comboBox_usMaxSpeakers->setItemText(8, QCoreApplication::translate("QualitySelSetDialog", "9", nullptr));
        comboBox_usMaxSpeakers->setItemText(9, QCoreApplication::translate("QualitySelSetDialog", "10", nullptr));
        comboBox_usMaxSpeakers->setItemText(10, QCoreApplication::translate("QualitySelSetDialog", "11", nullptr));
        comboBox_usMaxSpeakers->setItemText(11, QCoreApplication::translate("QualitySelSetDialog", "12", nullptr));
        comboBox_usMaxSpeakers->setItemText(12, QCoreApplication::translate("QualitySelSetDialog", "13", nullptr));
        comboBox_usMaxSpeakers->setItemText(13, QCoreApplication::translate("QualitySelSetDialog", "14", nullptr));
        comboBox_usMaxSpeakers->setItemText(14, QCoreApplication::translate("QualitySelSetDialog", "15", nullptr));
        comboBox_usMaxSpeakers->setItemText(15, QCoreApplication::translate("QualitySelSetDialog", "16", nullptr));

        comboBox_usMaxSpeakers->setCurrentText(QCoreApplication::translate("QualitySelSetDialog", "1", nullptr));
        label_8->setText(QString());
        label_err->setText(QCoreApplication::translate("QualitySelSetDialog", "xxxxxxxx!", nullptr));
        pushButton_6->setText(QCoreApplication::translate("QualitySelSetDialog", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QualitySelSetDialog: public Ui_QualitySelSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUALITYSELSETDIALOG_H
