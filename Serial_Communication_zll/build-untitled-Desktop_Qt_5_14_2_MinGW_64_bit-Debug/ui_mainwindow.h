/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QComboBox *PortBox;
    QSpacerItem *verticalSpacer;
    QComboBox *BaudBox;
    QSpacerItem *verticalSpacer_4;
    QComboBox *BitBox;
    QSpacerItem *verticalSpacer_5;
    QComboBox *ParityBox;
    QSpacerItem *verticalSpacer_6;
    QComboBox *StopBox;
    QSpacerItem *verticalSpacer_7;
    QComboBox *ControlBox;
    QSpacerItem *verticalSpacer_8;
    QPushButton *OpenSerialButton;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_10;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_12;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_13;
    QLabel *label_6;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *ClearShowButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *ClearButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *SendEditBtn1;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_8;
    QTextEdit *DataReceived;
    QLabel *label_9;
    QTextEdit *DataSend;
    QLabel *label_7;
    QPlainTextEdit *Edit1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(862, 718);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(167, 23, 95, 481));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        PortBox = new QComboBox(widget);
        PortBox->setObjectName(QString::fromUtf8("PortBox"));
        PortBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        verticalLayout->addWidget(PortBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        BaudBox = new QComboBox(widget);
        BaudBox->setObjectName(QString::fromUtf8("BaudBox"));

        verticalLayout->addWidget(BaudBox);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        BitBox = new QComboBox(widget);
        BitBox->setObjectName(QString::fromUtf8("BitBox"));

        verticalLayout->addWidget(BitBox);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        ParityBox = new QComboBox(widget);
        ParityBox->setObjectName(QString::fromUtf8("ParityBox"));

        verticalLayout->addWidget(ParityBox);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        StopBox = new QComboBox(widget);
        StopBox->setObjectName(QString::fromUtf8("StopBox"));

        verticalLayout->addWidget(StopBox);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        ControlBox = new QComboBox(widget);
        ControlBox->setObjectName(QString::fromUtf8("ControlBox"));

        verticalLayout->addWidget(ControlBox);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        OpenSerialButton = new QPushButton(widget);
        OpenSerialButton->setObjectName(QString::fromUtf8("OpenSerialButton"));

        verticalLayout->addWidget(OpenSerialButton);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(90, 30, 47, 391));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_9);

        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_10);

        label_3 = new QLabel(widget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_11);

        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_12);

        label_5 = new QLabel(widget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_13);

        label_6 = new QLabel(widget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(570, 110, 95, 341));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ClearShowButton = new QPushButton(widget2);
        ClearShowButton->setObjectName(QString::fromUtf8("ClearShowButton"));

        verticalLayout_3->addWidget(ClearShowButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        ClearButton = new QPushButton(widget2);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));

        verticalLayout_3->addWidget(ClearButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        SendEditBtn1 = new QPushButton(widget2);
        SendEditBtn1->setObjectName(QString::fromUtf8("SendEditBtn1"));

        verticalLayout_3->addWidget(SendEditBtn1);

        widget3 = new QWidget(centralwidget);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(290, 30, 258, 471));
        verticalLayout_4 = new QVBoxLayout(widget3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(widget3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_4->addWidget(label_8);

        DataReceived = new QTextEdit(widget3);
        DataReceived->setObjectName(QString::fromUtf8("DataReceived"));

        verticalLayout_4->addWidget(DataReceived);

        label_9 = new QLabel(widget3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_4->addWidget(label_9);

        DataSend = new QTextEdit(widget3);
        DataSend->setObjectName(QString::fromUtf8("DataSend"));

        verticalLayout_4->addWidget(DataSend);

        label_7 = new QLabel(widget3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_4->addWidget(label_7);

        Edit1 = new QPlainTextEdit(widget3);
        Edit1->setObjectName(QString::fromUtf8("Edit1"));

        verticalLayout_4->addWidget(Edit1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 862, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        OpenSerialButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\346\265\201", nullptr));
        ClearShowButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        ClearButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\217\221\351\200\201", nullptr));
        SendEditBtn1->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\347\252\227\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
