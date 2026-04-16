/********************************************************************************
** Form generated from reading UI file 'CloudDiskWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOUDDISKWIDGET_H
#define UI_CLOUDDISKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CloudDiskWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QListWidget *listWidget;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpinBox *spinBox;
    QPushButton *pushButton_5;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;

    void setupUi(QWidget *CloudDiskWidget)
    {
        if (CloudDiskWidget->objectName().isEmpty())
            CloudDiskWidget->setObjectName("CloudDiskWidget");
        CloudDiskWidget->resize(933, 691);
        CloudDiskWidget->setMinimumSize(QSize(800, 540));
        horizontalLayout = new QHBoxLayout(CloudDiskWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(CloudDiskWidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("#widget\n"
"{\n"
" \n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:18px;\n"
"font-weight:400;"));

        horizontalLayout_2->addWidget(label);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(30, 30));
        pushButton->setMaximumSize(QSize(30, 30));
        pushButton->setStyleSheet(QString::fromUtf8("image: url(:Resources/Images/WinMain/sysbtn_close_normal.png);\n"
"border:none;"));
        pushButton->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(20, 10, 20, 20);
        tableWidget = new QTableWidget(widget_3);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);

        verticalLayout_2->addWidget(tableWidget);

        listWidget = new QListWidget(widget_3);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(0, 150));
        listWidget->setMaximumSize(QSize(16777215, 150));

        verticalLayout_2->addWidget(listWidget);

        frame = new QFrame(widget_3);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(0, 40));
        frame->setMaximumSize(QSize(16777215, 40));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(frame);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(320, 34));
        widget_4->setMaximumSize(QSize(320, 34));
        widget_4->setStyleSheet(QString::fromUtf8("#widget_4\n"
"{\n"
" border:1px solid #dddddd;\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(4, 0, 4, 0);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(30, 30));
        label_2->setMaximumSize(QSize(30, 30));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/Resources/Images/WinMain/search_icon.png);"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit = new QLineEdit(widget_4);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setMaximumSize(QSize(16777215, 30));
        lineEdit->setStyleSheet(QString::fromUtf8("border:none;"));
        lineEdit->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(lineEdit);


        horizontalLayout_4->addWidget(widget_4);

        btnSearch = new QPushButton(frame);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setMinimumSize(QSize(30, 34));
        btnSearch->setMaximumSize(QSize(30, 34));
        btnSearch->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_4->addWidget(btnSearch);

        horizontalSpacer = new QSpacerItem(119, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(60, 34));
        pushButton_2->setMaximumSize(QSize(60, 34));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(60, 34));
        pushButton_3->setMaximumSize(QSize(60, 34));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(60, 34));
        pushButton_4->setMaximumSize(QSize(60, 34));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_4);

        spinBox = new QSpinBox(frame);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimumSize(QSize(50, 34));
        spinBox->setMaximumSize(QSize(50, 34));
        spinBox->setMinimum(1);
        spinBox->setMaximum(999999);

        horizontalLayout_4->addWidget(spinBox);

        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(60, 34));
        pushButton_5->setMaximumSize(QSize(60, 34));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_5);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(widget_3);
        frame_2->setObjectName("frame_2");
        frame_2->setMinimumSize(QSize(0, 40));
        frame_2->setMaximumSize(QSize(16777215, 40));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_2);
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButton_6 = new QPushButton(frame_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setEnabled(false);
        pushButton_6->setMinimumSize(QSize(60, 34));
        pushButton_6->setMaximumSize(QSize(60, 34));
        pushButton_6->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}\n"
"QPushButton#pushButton_6{ color:#999}\n"
"QPushButton#pushButton_9{ color:#999}"));

        horizontalLayout_5->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(frame_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setMinimumSize(QSize(60, 34));
        pushButton_7->setMaximumSize(QSize(60, 34));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_5->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(frame_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setMinimumSize(QSize(60, 34));
        pushButton_8->setMaximumSize(QSize(60, 34));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_5->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(frame_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setEnabled(false);
        pushButton_9->setMinimumSize(QSize(60, 34));
        pushButton_9->setMaximumSize(QSize(60, 34));
        pushButton_9->setCursor(QCursor(Qt::CursorShape::ForbiddenCursor));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}\n"
"QPushButton#pushButton_9{ color:#999}"));

        horizontalLayout_5->addWidget(pushButton_9);

        horizontalSpacer_2 = new QSpacerItem(273, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButton_10 = new QPushButton(frame_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setMinimumSize(QSize(120, 34));
        pushButton_10->setMaximumSize(QSize(120, 34));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_5->addWidget(pushButton_10);

        pushButton_11 = new QPushButton(frame_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setMinimumSize(QSize(60, 34));
        pushButton_11->setMaximumSize(QSize(60, 34));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" border:1px solid #dddddd;\n"
" color:#333333;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background: #dddddd;\n"
"}"));

        horizontalLayout_5->addWidget(pushButton_11);


        verticalLayout_2->addWidget(frame_2);


        verticalLayout->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        retranslateUi(CloudDiskWidget);
        QObject::connect(pushButton, &QPushButton::clicked, CloudDiskWidget, qOverload<>(&QWidget::close));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), CloudDiskWidget, SLOT(slot_edit_return()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_page()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_page()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_page()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_page()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_file()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_file()));
        QObject::connect(pushButton_8, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_file()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_file()));
        QObject::connect(pushButton_10, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_file()));
        QObject::connect(pushButton_11, SIGNAL(clicked()), CloudDiskWidget, SLOT(slot_button_file()));

        QMetaObject::connectSlotsByName(CloudDiskWidget);
    } // setupUi

    void retranslateUi(QWidget *CloudDiskWidget)
    {
        CloudDiskWidget->setWindowTitle(QCoreApplication::translate("CloudDiskWidget", "w", nullptr));
        label->setText(QCoreApplication::translate("CloudDiskWidget", "\347\275\221\347\233\230", nullptr));
        pushButton->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CloudDiskWidget", "\344\270\212\344\274\240\344\272\272ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CloudDiskWidget", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CloudDiskWidget", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CloudDiskWidget", "\344\270\212\344\274\240\346\227\266\351\227\264", nullptr));
        label_2->setText(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("CloudDiskWidget", "\350\276\223\345\205\245\346\220\234\347\264\242\345\205\263\351\224\256\345\255\227", nullptr));
        btnSearch->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("CloudDiskWidget", "\351\246\226\351\241\265", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CloudDiskWidget", "\344\270\212\344\270\200\351\241\265", nullptr));
        pushButton_4->setText(QCoreApplication::translate("CloudDiskWidget", "\344\270\213\344\270\200\351\241\265", nullptr));
        pushButton_5->setText(QCoreApplication::translate("CloudDiskWidget", "GO", nullptr));
        pushButton_6->setText(QCoreApplication::translate("CloudDiskWidget", "\344\270\213\350\275\275", nullptr));
        pushButton_7->setText(QCoreApplication::translate("CloudDiskWidget", "\344\270\212\344\274\240", nullptr));
        pushButton_8->setText(QCoreApplication::translate("CloudDiskWidget", "\345\210\267\346\226\260", nullptr));
        pushButton_9->setText(QCoreApplication::translate("CloudDiskWidget", "\345\210\240\351\231\244", nullptr));
        pushButton_10->setText(QCoreApplication::translate("CloudDiskWidget", "\346\230\276\347\244\272\346\211\200\346\234\211\344\270\213\350\275\275", nullptr));
        pushButton_11->setText(QCoreApplication::translate("CloudDiskWidget", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CloudDiskWidget: public Ui_CloudDiskWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOUDDISKWIDGET_H
