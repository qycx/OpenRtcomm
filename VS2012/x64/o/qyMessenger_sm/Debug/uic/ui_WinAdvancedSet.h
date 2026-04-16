/********************************************************************************
** Form generated from reading UI file 'WinAdvancedSet.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINADVANCEDSET_H
#define UI_WINADVANCEDSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinAdvancedSet
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *WinAdvancedSet)
    {
        if (WinAdvancedSet->objectName().isEmpty())
            WinAdvancedSet->setObjectName("WinAdvancedSet");
        WinAdvancedSet->resize(752, 564);
        gridLayout = new QGridLayout(WinAdvancedSet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(WinAdvancedSet);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(20);
        label->setFont(font);
        label->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(597, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 508, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(WinAdvancedSet);

        QMetaObject::connectSlotsByName(WinAdvancedSet);
    } // setupUi

    void retranslateUi(QWidget *WinAdvancedSet)
    {
        WinAdvancedSet->setWindowTitle(QCoreApplication::translate("WinAdvancedSet", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("WinAdvancedSet", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinAdvancedSet: public Ui_WinAdvancedSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINADVANCEDSET_H
