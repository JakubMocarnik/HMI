/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <myframe.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHello_Kitty;
    QAction *actionDark_Souls;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    MyFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_estop;
    QPushButton *pushButton_up;
    QPushButton *pushButton_down;
    QPushButton *pushButton_left;
    QPushButton *pushButton_circle;
    QPushButton *pushButton_right;
    QGridLayout *gridLayout_7;
    QLabel *label_warning;
    QHBoxLayout *horizontalLayout;
    QLabel *label_ip;
    QLineEdit *lineEdit_ip;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_led;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_mode;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menuStyle;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1221, 553);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionHello_Kitty = new QAction(MainWindow);
        actionHello_Kitty->setObjectName(QString::fromUtf8("actionHello_Kitty"));
        actionDark_Souls = new QAction(MainWindow);
        actionDark_Souls->setObjectName(QString::fromUtf8("actionDark_Souls"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        frame = new MyFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(600, 450));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        horizontalLayout_4->addWidget(frame);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_2, 1, 2, 1, 1);

        pushButton_estop = new QPushButton(centralWidget);
        pushButton_estop->setObjectName(QString::fromUtf8("pushButton_estop"));

        gridLayout_4->addWidget(pushButton_estop, 0, 2, 1, 1);

        pushButton_up = new QPushButton(centralWidget);
        pushButton_up->setObjectName(QString::fromUtf8("pushButton_up"));

        gridLayout_4->addWidget(pushButton_up, 2, 2, 1, 1);

        pushButton_down = new QPushButton(centralWidget);
        pushButton_down->setObjectName(QString::fromUtf8("pushButton_down"));

        gridLayout_4->addWidget(pushButton_down, 4, 2, 1, 1);

        pushButton_left = new QPushButton(centralWidget);
        pushButton_left->setObjectName(QString::fromUtf8("pushButton_left"));

        gridLayout_4->addWidget(pushButton_left, 3, 1, 1, 1);

        pushButton_circle = new QPushButton(centralWidget);
        pushButton_circle->setObjectName(QString::fromUtf8("pushButton_circle"));
        pushButton_circle->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(pushButton_circle, 3, 2, 1, 1);

        pushButton_right = new QPushButton(centralWidget);
        pushButton_right->setObjectName(QString::fromUtf8("pushButton_right"));

        gridLayout_4->addWidget(pushButton_right, 3, 3, 1, 1);


        gridLayout_3->addLayout(gridLayout_4, 4, 1, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_warning = new QLabel(centralWidget);
        label_warning->setObjectName(QString::fromUtf8("label_warning"));
        label_warning->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_warning, 5, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_ip = new QLabel(centralWidget);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setMaximumSize(QSize(100, 16777215));
        label_ip->setLayoutDirection(Qt::RightToLeft);
        label_ip->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_ip);

        lineEdit_ip = new QLineEdit(centralWidget);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setMinimumSize(QSize(110, 0));
        lineEdit_ip->setMaximumSize(QSize(110, 16777215));
        lineEdit_ip->setLayoutDirection(Qt::RightToLeft);
        lineEdit_ip->setMaxLength(15);

        horizontalLayout->addWidget(lineEdit_ip);


        gridLayout_7->addLayout(horizontalLayout, 0, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_led = new QLabel(centralWidget);
        label_led->setObjectName(QString::fromUtf8("label_led"));
        label_led->setMaximumSize(QSize(100, 16777215));
        label_led->setLayoutDirection(Qt::RightToLeft);
        label_led->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_led);

        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        pushButton_connect->setMaximumSize(QSize(110, 16777215));
        pushButton_connect->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(pushButton_connect);


        gridLayout_7->addLayout(horizontalLayout_2, 2, 2, 1, 1);

        pushButton_mode = new QPushButton(centralWidget);
        pushButton_mode->setObjectName(QString::fromUtf8("pushButton_mode"));
        pushButton_mode->setMaximumSize(QSize(110, 16777215));
        pushButton_mode->setLayoutDirection(Qt::RightToLeft);
        pushButton_mode->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(pushButton_mode, 3, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_7->addItem(verticalSpacer_4, 4, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_7, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer_3, 3, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1221, 26));
        menuStyle = new QMenu(menuBar);
        menuStyle->setObjectName(QString::fromUtf8("menuStyle"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
#if QT_CONFIG(shortcut)
        label_ip->setBuddy(lineEdit_ip);
        label_led->setBuddy(pushButton_connect);
#endif // QT_CONFIG(shortcut)

        menuBar->addAction(menuStyle->menuAction());
        menuStyle->addAction(actionHello_Kitty);
        menuStyle->addAction(actionDark_Souls);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionHello_Kitty->setText(QCoreApplication::translate("MainWindow", "Hello Kitty", nullptr));
        actionDark_Souls->setText(QCoreApplication::translate("MainWindow", "Dark Souls", nullptr));
        pushButton_estop->setText(QString());
        pushButton_up->setText(QString());
        pushButton_down->setText(QString());
        pushButton_left->setText(QString());
        pushButton_circle->setText(QString());
        pushButton_right->setText(QString());
        label_warning->setText(QString());
        label_ip->setText(QCoreApplication::translate("MainWindow", "IP ADDRESS:", nullptr));
        label_led->setText(QCoreApplication::translate("MainWindow", "LED", nullptr));
        pushButton_connect->setText(QCoreApplication::translate("MainWindow", "CONNECT", nullptr));
        pushButton_mode->setText(QCoreApplication::translate("MainWindow", "GESTURES", nullptr));
        menuStyle->setTitle(QCoreApplication::translate("MainWindow", "Style", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H