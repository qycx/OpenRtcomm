/********************************************************************************
** Form generated from reading UI file 'CDlgShareDynBmps_qt.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDLGSHAREDYNBMPS_QT_H
#define UI_CDLGSHAREDYNBMPS_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgShareDynBmps_qtClass
{
public:
    QWidget *widget_pic0;
    QPushButton *pushButton_shareScreen;
    QPushButton *pushButton_webcam1;
    QPushButton *pushButton_ic;

    void setupUi(QWidget *CDlgShareDynBmps_qtClass)
    {
        if (CDlgShareDynBmps_qtClass->objectName().isEmpty())
            CDlgShareDynBmps_qtClass->setObjectName("CDlgShareDynBmps_qtClass");
        CDlgShareDynBmps_qtClass->resize(572, 389);
        widget_pic0 = new QWidget(CDlgShareDynBmps_qtClass);
        widget_pic0->setObjectName("widget_pic0");
        widget_pic0->setGeometry(QRect(40, 30, 481, 331));
        pushButton_shareScreen = new QPushButton(widget_pic0);
        pushButton_shareScreen->setObjectName("pushButton_shareScreen");
        pushButton_shareScreen->setGeometry(QRect(300, 80, 121, 31));
        pushButton_webcam1 = new QPushButton(CDlgShareDynBmps_qtClass);
        pushButton_webcam1->setObjectName("pushButton_webcam1");
        pushButton_webcam1->setGeometry(QRect(370, 160, 93, 28));
        pushButton_ic = new QPushButton(CDlgShareDynBmps_qtClass);
        pushButton_ic->setObjectName("pushButton_ic");
        pushButton_ic->setGeometry(QRect(370, 200, 93, 28));

        retranslateUi(CDlgShareDynBmps_qtClass);

        QMetaObject::connectSlotsByName(CDlgShareDynBmps_qtClass);
    } // setupUi

    void retranslateUi(QWidget *CDlgShareDynBmps_qtClass)
    {
        CDlgShareDynBmps_qtClass->setWindowTitle(QCoreApplication::translate("CDlgShareDynBmps_qtClass", "CDlgShareDynBmps_qt", nullptr));
        pushButton_shareScreen->setText(QCoreApplication::translate("CDlgShareDynBmps_qtClass", "shareScreen", nullptr));
        pushButton_webcam1->setText(QCoreApplication::translate("CDlgShareDynBmps_qtClass", "webcam1", nullptr));
        pushButton_ic->setText(QCoreApplication::translate("CDlgShareDynBmps_qtClass", "ic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgShareDynBmps_qtClass: public Ui_CDlgShareDynBmps_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDLGSHAREDYNBMPS_QT_H
