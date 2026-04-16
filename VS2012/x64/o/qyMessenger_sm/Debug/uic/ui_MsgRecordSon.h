/********************************************************************************
** Form generated from reading UI file 'MsgRecordSon.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGRECORDSON_H
#define UI_MSGRECORDSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgRecordSon
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labValue;
    QPushButton *btnClose;
    QListWidget *listWidget;

    void setupUi(QWidget *MsgRecordSon)
    {
        if (MsgRecordSon->objectName().isEmpty())
            MsgRecordSon->setObjectName("MsgRecordSon");
        MsgRecordSon->resize(441, 600);
        MsgRecordSon->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(MsgRecordSon);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(MsgRecordSon);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));
        widget->setStyleSheet(QString::fromUtf8("border-bottom:1px solid #999;"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labValue = new QLabel(widget);
        labValue->setObjectName("labValue");

        horizontalLayout->addWidget(labValue);

        btnClose = new QPushButton(widget);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        btnClose->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnClose->setStyleSheet(QString::fromUtf8("image: url(:Resources/Images/WinMain/sysbtn_close_normal.png);\n"
"border:none;"));

        horizontalLayout->addWidget(btnClose, 0, Qt::AlignRight);


        verticalLayout->addWidget(widget);

        listWidget = new QListWidget(MsgRecordSon);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);


        retranslateUi(MsgRecordSon);
        QObject::connect(btnClose, &QPushButton::clicked, MsgRecordSon, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(MsgRecordSon);
    } // setupUi

    void retranslateUi(QWidget *MsgRecordSon)
    {
        MsgRecordSon->setWindowTitle(QCoreApplication::translate("MsgRecordSon", "MsgRecordSon", nullptr));
        labValue->setText(QCoreApplication::translate("MsgRecordSon", "\344\270\212\344\270\213\346\226\207\350\257\246\346\203\205", nullptr));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MsgRecordSon: public Ui_MsgRecordSon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGRECORDSON_H
