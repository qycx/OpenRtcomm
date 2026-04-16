/********************************************************************************
** Form generated from reading UI file 'DlgNotification_qt.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGNOTIFICATION_QT_H
#define UI_DLGNOTIFICATION_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgNotification_qt
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labMsg;

    void setupUi(QWidget *DlgNotification_qt)
    {
        if (DlgNotification_qt->objectName().isEmpty())
            DlgNotification_qt->setObjectName("DlgNotification_qt");
        DlgNotification_qt->resize(200, 140);
        DlgNotification_qt->setMinimumSize(QSize(200, 140));
        verticalLayout = new QVBoxLayout(DlgNotification_qt);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(DlgNotification_qt);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(200, 140));
        widget_2->setStyleSheet(QString::fromUtf8("#widget_2 {background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(79, 245, 12, 255), stop:1 rgba(8, 247, 235, 255))}"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labMsg = new QLabel(widget_2);
        labMsg->setObjectName("labMsg");
        labMsg->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setBold(true);
        labMsg->setFont(font);
        labMsg->setStyleSheet(QString::fromUtf8("font-size:16px;\n"
"font-weight:500;"));
        labMsg->setWordWrap(true);

        verticalLayout_2->addWidget(labMsg, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout->addWidget(widget_2);


        retranslateUi(DlgNotification_qt);

        QMetaObject::connectSlotsByName(DlgNotification_qt);
    } // setupUi

    void retranslateUi(QWidget *DlgNotification_qt)
    {
        DlgNotification_qt->setWindowTitle(QCoreApplication::translate("DlgNotification_qt", "DlgNotification_qt", nullptr));
        labMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DlgNotification_qt: public Ui_DlgNotification_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGNOTIFICATION_QT_H
