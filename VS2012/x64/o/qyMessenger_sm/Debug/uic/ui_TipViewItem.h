/********************************************************************************
** Form generated from reading UI file 'TipViewItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPVIEWITEM_H
#define UI_TIPVIEWITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TipViewItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *lab_photo;
    QLabel *lab_name;
    QLabel *lab_count;

    void setupUi(QWidget *TipViewItem)
    {
        if (TipViewItem->objectName().isEmpty())
            TipViewItem->setObjectName("TipViewItem");
        TipViewItem->resize(400, 62);
        TipViewItem->setMinimumSize(QSize(0, 60));
        TipViewItem->setMaximumSize(QSize(16777215, 62));
        horizontalLayout = new QHBoxLayout(TipViewItem);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(25, -1, 20, -1);
        lab_photo = new QLabel(TipViewItem);
        lab_photo->setObjectName("lab_photo");
        lab_photo->setMinimumSize(QSize(40, 40));
        lab_photo->setMaximumSize(QSize(40, 40));
        lab_photo->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 0);"));

        horizontalLayout->addWidget(lab_photo);

        lab_name = new QLabel(TipViewItem);
        lab_name->setObjectName("lab_name");
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setBold(true);
        font.setItalic(false);
        lab_name->setFont(font);
        lab_name->setStyleSheet(QString::fromUtf8("color: #353535;\n"
"font: 15px;\n"
"font-weight:bold;"));

        horizontalLayout->addWidget(lab_name);

        lab_count = new QLabel(TipViewItem);
        lab_count->setObjectName("lab_count");
        lab_count->setMinimumSize(QSize(24, 18));
        lab_count->setMaximumSize(QSize(24, 18));
        lab_count->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 27, 46);\n"
"color: rgb(255, 255, 255);\n"
"font: 12px;\n"
"border-radius:5px;"));
        lab_count->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lab_count);


        retranslateUi(TipViewItem);

        QMetaObject::connectSlotsByName(TipViewItem);
    } // setupUi

    void retranslateUi(QWidget *TipViewItem)
    {
        TipViewItem->setWindowTitle(QCoreApplication::translate("TipViewItem", "TipViewItem", nullptr));
        lab_photo->setText(QString());
        lab_name->setText(QString());
        lab_count->setText(QCoreApplication::translate("TipViewItem", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TipViewItem: public Ui_TipViewItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPVIEWITEM_H
