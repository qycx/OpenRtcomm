/********************************************************************************
** Form generated from reading UI file 'WinContactsList.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINCONTACTSLIST_H
#define UI_WINCONTACTSLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinContactsList
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidgetContacts;

    void setupUi(QWidget *WinContactsList)
    {
        if (WinContactsList->objectName().isEmpty())
            WinContactsList->setObjectName("WinContactsList");
        WinContactsList->resize(305, 805);
        WinContactsList->setProperty("leftbottomskin", QVariant(true));
        gridLayout = new QGridLayout(WinContactsList);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeWidgetContacts = new QTreeWidget(WinContactsList);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetContacts->setHeaderItem(__qtreewidgetitem);
        treeWidgetContacts->setObjectName("treeWidgetContacts");
        treeWidgetContacts->setStyleSheet(QString::fromUtf8("QScrollBar{width:8px}"));
        treeWidgetContacts->setFrameShape(QFrame::NoFrame);
        treeWidgetContacts->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidgetContacts->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidgetContacts->setEditTriggers(QAbstractItemView::AllEditTriggers);
        treeWidgetContacts->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidgetContacts->setIndentation(0);
        treeWidgetContacts->setAnimated(false);
        treeWidgetContacts->setHeaderHidden(true);
        treeWidgetContacts->setExpandsOnDoubleClick(false);

        gridLayout->addWidget(treeWidgetContacts, 0, 0, 1, 1);


        retranslateUi(WinContactsList);

        QMetaObject::connectSlotsByName(WinContactsList);
    } // setupUi

    void retranslateUi(QWidget *WinContactsList)
    {
        WinContactsList->setWindowTitle(QCoreApplication::translate("WinContactsList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinContactsList: public Ui_WinContactsList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINCONTACTSLIST_H
