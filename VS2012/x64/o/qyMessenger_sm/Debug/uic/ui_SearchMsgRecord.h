/********************************************************************************
** Form generated from reading UI file 'SearchMsgRecord.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHMSGRECORD_H
#define UI_SEARCHMSGRECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchMsgRecord
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labCount;
    QPushButton *btnTalker;
    QPushButton *btnClose;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;

    void setupUi(QWidget *SearchMsgRecord)
    {
        if (SearchMsgRecord->objectName().isEmpty())
            SearchMsgRecord->setObjectName("SearchMsgRecord");
        SearchMsgRecord->resize(545, 603);
        SearchMsgRecord->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QWidget#widget{background:#fff}"));
        horizontalLayout = new QHBoxLayout(SearchMsgRecord);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(SearchMsgRecord);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        widget_2->setStyleSheet(QString::fromUtf8("border-bottom:1px solid #999;"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labCount = new QLabel(widget_2);
        labCount->setObjectName("labCount");
        labCount->setStyleSheet(QString::fromUtf8("font-size:17px;color:#000;"));

        horizontalLayout_2->addWidget(labCount);

        btnTalker = new QPushButton(widget_2);
        btnTalker->setObjectName("btnTalker");
        btnTalker->setMinimumSize(QSize(100, 25));
        btnTalker->setMaximumSize(QSize(100, 16777215));
        btnTalker->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnTalker->setStyleSheet(QString::fromUtf8("border:1px solid #999;border-radius:5%;"));

        horizontalLayout_2->addWidget(btnTalker);

        btnClose = new QPushButton(widget_2);
        btnClose->setObjectName("btnClose");
        btnClose->setMaximumSize(QSize(30, 30));
        btnClose->setSizeIncrement(QSize(30, 30));
        btnClose->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
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
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(widget_3);
        listWidget->setObjectName("listWidget");

        verticalLayout_2->addWidget(listWidget);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(SearchMsgRecord);
        QObject::connect(btnClose, &QPushButton::clicked, SearchMsgRecord, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(SearchMsgRecord);
    } // setupUi

    void retranslateUi(QWidget *SearchMsgRecord)
    {
        SearchMsgRecord->setWindowTitle(QCoreApplication::translate("SearchMsgRecord", "SearchMsgRecord", nullptr));
        labCount->setText(QCoreApplication::translate("SearchMsgRecord", "\346\235\241\347\233\270\345\205\263\350\201\212\345\244\251\350\256\260\345\275\225", nullptr));
        btnTalker->setText(QCoreApplication::translate("SearchMsgRecord", "\350\277\233\345\205\245\350\201\212\345\244\251", nullptr));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchMsgRecord: public Ui_SearchMsgRecord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHMSGRECORD_H
