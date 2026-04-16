/********************************************************************************
** Form generated from reading UI file 'CDlgTalk_grp_members.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGTALK_GRP_MEMBERS_H
#define UI_CDLGTALK_GRP_MEMBERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgTalk_grp_members
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *btnClose;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;

    void setupUi(QWidget *CDlgTalk_grp_members)
    {
        if (CDlgTalk_grp_members->objectName().isEmpty())
            CDlgTalk_grp_members->setObjectName("CDlgTalk_grp_members");
        CDlgTalk_grp_members->resize(572, 467);
        horizontalLayout = new QHBoxLayout(CDlgTalk_grp_members);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CDlgTalk_grp_members);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background:#fff"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(8, 3, 8, 8);
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
        label->setStyleSheet(QString::fromUtf8("font-size:16px"));

        horizontalLayout_2->addWidget(label);

        btnClose = new QPushButton(widget_2);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        btnClose->setStyleSheet(QString::fromUtf8("image: url(:Resources/Images/WinMain/sysbtn_close_normal.png);\n"
"border:none;"));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 10, 0, 0);
        tableWidget = new QTableWidget(widget_3);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_2->addWidget(tableWidget);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(CDlgTalk_grp_members);
        QObject::connect(btnClose, &QPushButton::clicked, CDlgTalk_grp_members, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(CDlgTalk_grp_members);
    } // setupUi

    void retranslateUi(QWidget *CDlgTalk_grp_members)
    {
        CDlgTalk_grp_members->setWindowTitle(QCoreApplication::translate("CDlgTalk_grp_members", "CDlgTalk_grp_members", nullptr));
        label->setText(QCoreApplication::translate("CDlgTalk_grp_members", " \347\273\204\346\210\220\345\221\230\345\210\227\350\241\250", nullptr));
        btnClose->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CDlgTalk_grp_members", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CDlgTalk_grp_members", "MessengerID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CDlgTalk_grp_members", "\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgTalk_grp_members: public Ui_CDlgTalk_grp_members {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGTALK_GRP_MEMBERS_H
