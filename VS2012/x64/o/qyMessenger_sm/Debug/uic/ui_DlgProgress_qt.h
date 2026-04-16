/********************************************************************************
** Form generated from reading UI file 'DlgProgress_qt.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPROGRESS_QT_H
#define UI_DLGPROGRESS_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgProgress_qt
{
public:
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;

    void setupUi(QWidget *DlgProgress_qt)
    {
        if (DlgProgress_qt->objectName().isEmpty())
            DlgProgress_qt->setObjectName("DlgProgress_qt");
        DlgProgress_qt->resize(478, 50);
        horizontalLayout = new QHBoxLayout(DlgProgress_qt);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        progressBar = new QProgressBar(DlgProgress_qt);
        progressBar->setObjectName("progressBar");
        progressBar->setMaximum(30);
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);


        retranslateUi(DlgProgress_qt);

        QMetaObject::connectSlotsByName(DlgProgress_qt);
    } // setupUi

    void retranslateUi(QWidget *DlgProgress_qt)
    {
        DlgProgress_qt->setWindowTitle(QCoreApplication::translate("DlgProgress_qt", "DlgProgress_qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgProgress_qt: public Ui_DlgProgress_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPROGRESS_QT_H
