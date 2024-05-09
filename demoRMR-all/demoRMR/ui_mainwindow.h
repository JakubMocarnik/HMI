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
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_estop;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_led;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_mode;
    QHBoxLayout *horizontalLayout;
    QLabel *label_ip;
    QLineEdit *lineEdit_ip;
    QSpacerItem *verticalSpacer_7;
    QPushButton *pushButton_startmission;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_camera;
    QPushButton *pushButton_camera;
    QLabel *label_warning;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_removepoint;
    QPushButton *pushButton_addpoint;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_point_type;
    QPushButton *pushButton_point_type;
    QMenuBar *menuBar;
    QMenu *menuStyle;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(871, 637);
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
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton_estop = new QPushButton(centralWidget);
        pushButton_estop->setObjectName(QString::fromUtf8("pushButton_estop"));

        gridLayout_4->addWidget(pushButton_estop, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_4, 3, 1, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
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

        pushButton_reset = new QPushButton(centralWidget);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));
        pushButton_reset->setMaximumSize(QSize(110, 16777215));
        pushButton_reset->setLayoutDirection(Qt::RightToLeft);

        gridLayout_7->addWidget(pushButton_reset, 12, 2, 1, 1);

        pushButton_mode = new QPushButton(centralWidget);
        pushButton_mode->setObjectName(QString::fromUtf8("pushButton_mode"));
        pushButton_mode->setMaximumSize(QSize(110, 16777215));
        pushButton_mode->setLayoutDirection(Qt::RightToLeft);
        pushButton_mode->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(pushButton_mode, 4, 2, 1, 1);

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

        verticalSpacer_7 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_7->addItem(verticalSpacer_7, 11, 2, 1, 1);

        pushButton_startmission = new QPushButton(centralWidget);
        pushButton_startmission->setObjectName(QString::fromUtf8("pushButton_startmission"));
        pushButton_startmission->setMaximumSize(QSize(110, 16777215));
        pushButton_startmission->setLayoutDirection(Qt::RightToLeft);

        gridLayout_7->addWidget(pushButton_startmission, 13, 2, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_camera = new QLabel(centralWidget);
        label_camera->setObjectName(QString::fromUtf8("label_camera"));
        label_camera->setMaximumSize(QSize(100, 16777215));
        label_camera->setLayoutDirection(Qt::RightToLeft);
        label_camera->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_camera);

        pushButton_camera = new QPushButton(centralWidget);
        pushButton_camera->setObjectName(QString::fromUtf8("pushButton_camera"));
        pushButton_camera->setMaximumSize(QSize(110, 16777215));
        pushButton_camera->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_11->addWidget(pushButton_camera);


        gridLayout_7->addLayout(horizontalLayout_11, 3, 2, 1, 1);

        label_warning = new QLabel(centralWidget);
        label_warning->setObjectName(QString::fromUtf8("label_warning"));
        label_warning->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_warning, 18, 2, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_7->addItem(verticalSpacer_6, 6, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_7->addItem(verticalSpacer_4, 17, 2, 1, 1);

        pushButton_removepoint = new QPushButton(centralWidget);
        pushButton_removepoint->setObjectName(QString::fromUtf8("pushButton_removepoint"));
        pushButton_removepoint->setMaximumSize(QSize(110, 16777215));
        pushButton_removepoint->setLayoutDirection(Qt::RightToLeft);

        gridLayout_7->addWidget(pushButton_removepoint, 9, 2, 1, 1);

        pushButton_addpoint = new QPushButton(centralWidget);
        pushButton_addpoint->setObjectName(QString::fromUtf8("pushButton_addpoint"));
        pushButton_addpoint->setMaximumSize(QSize(110, 16777215));
        pushButton_addpoint->setLayoutDirection(Qt::RightToLeft);

        gridLayout_7->addWidget(pushButton_addpoint, 8, 2, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_point_type = new QLabel(centralWidget);
        label_point_type->setObjectName(QString::fromUtf8("label_point_type"));
        label_point_type->setMaximumSize(QSize(100, 16777215));
        label_point_type->setLayoutDirection(Qt::RightToLeft);
        label_point_type->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_point_type);

        pushButton_point_type = new QPushButton(centralWidget);
        pushButton_point_type->setObjectName(QString::fromUtf8("pushButton_point_type"));
        pushButton_point_type->setMaximumSize(QSize(110, 16777215));
        pushButton_point_type->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_15->addWidget(pushButton_point_type);


        gridLayout_7->addLayout(horizontalLayout_15, 7, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_7, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 871, 26));
        menuStyle = new QMenu(menuBar);
        menuStyle->setObjectName(QString::fromUtf8("menuStyle"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
#if QT_CONFIG(shortcut)
        label_led->setBuddy(pushButton_connect);
        label_ip->setBuddy(lineEdit_ip);
        label_camera->setBuddy(pushButton_camera);
        label_point_type->setBuddy(pushButton_point_type);
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
        label_led->setText(QCoreApplication::translate("MainWindow", "LED", nullptr));
        pushButton_connect->setText(QCoreApplication::translate("MainWindow", "CONNECT", nullptr));
        pushButton_reset->setText(QCoreApplication::translate("MainWindow", "RESET MISSION", nullptr));
        pushButton_mode->setText(QCoreApplication::translate("MainWindow", "LOAD MAP", nullptr));
        label_ip->setText(QCoreApplication::translate("MainWindow", "IP ADDRESS:", nullptr));
        pushButton_startmission->setText(QCoreApplication::translate("MainWindow", "START MISSION", nullptr));
        label_camera->setText(QCoreApplication::translate("MainWindow", "VIEW:", nullptr));
        pushButton_camera->setText(QCoreApplication::translate("MainWindow", "LIDAR", nullptr));
        label_warning->setText(QString());
        pushButton_removepoint->setText(QCoreApplication::translate("MainWindow", "REMOVE POINT", nullptr));
        pushButton_addpoint->setText(QCoreApplication::translate("MainWindow", "ADD POINTS", nullptr));
        label_point_type->setText(QCoreApplication::translate("MainWindow", "POINT TYPE:", nullptr));
        pushButton_point_type->setText(QCoreApplication::translate("MainWindow", "CROSSING", nullptr));
        menuStyle->setTitle(QCoreApplication::translate("MainWindow", "Style", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
