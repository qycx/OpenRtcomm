/********************************************************************************
** Form generated from reading UI file 'WinEmotion.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINEMOTION_H
#define UI_WINEMOTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinEmotion
{
public:
    QGridLayout *gridLayout_2;
    QWidget *bottomWidget;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *emotionWidget;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;

    void setupUi(QWidget *WinEmotion)
    {
        if (WinEmotion->objectName().isEmpty())
            WinEmotion->setObjectName("WinEmotion");
        WinEmotion->resize(700, 350);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WinEmotion->sizePolicy().hasHeightForWidth());
        WinEmotion->setSizePolicy(sizePolicy);
        WinEmotion->setMinimumSize(QSize(700, 350));
        WinEmotion->setMaximumSize(QSize(700, 350));
        WinEmotion->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(WinEmotion);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        bottomWidget = new QWidget(WinEmotion);
        bottomWidget->setObjectName("bottomWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bottomWidget->sizePolicy().hasHeightForWidth());
        bottomWidget->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(bottomWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(bottomWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        emotionWidget = new QWidget();
        emotionWidget->setObjectName("emotionWidget");
        emotionWidget->setGeometry(QRect(0, 0, 680, 330));
        sizePolicy1.setHeightForWidth(emotionWidget->sizePolicy().hasHeightForWidth());
        emotionWidget->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(emotionWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addLayout(gridLayout);

        scrollArea->setWidget(emotionWidget);

        verticalLayout_3->addWidget(scrollArea);


        gridLayout_2->addWidget(bottomWidget, 0, 0, 1, 1);


        retranslateUi(WinEmotion);

        QMetaObject::connectSlotsByName(WinEmotion);
    } // setupUi

    void retranslateUi(QWidget *WinEmotion)
    {
        WinEmotion->setWindowTitle(QCoreApplication::translate("WinEmotion", "EmotionWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinEmotion: public Ui_WinEmotion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINEMOTION_H
