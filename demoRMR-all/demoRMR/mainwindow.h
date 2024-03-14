#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#ifdef _WIN32
#include<windows.h>
#endif
#include<iostream>
//#include<arpa/inet.h>
//#include<unistd.h>
//#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
//#include "ckobuki.h"
//#include "rplidar.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"
#include "robot.h"
#include <QPixmap>
#include "myframe.h"


#include <QJoysticks.h>
namespace Ui {
class MainWindow;
}

///toto je trieda s oknom.. ktora sa spusti ked sa spusti aplikacia.. su tu vsetky gombiky a spustania...
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool useCamera1;
  //  cv::VideoCapture cap;

    int actIndex;
    //    cv::Mat frame[3];
    bool backupAssistant;
    cv::Mat frame[3];
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int processThisLidar(LaserMeasurement laserData);

    int processThisRobot(TKobukiData robotdata);
    friend class MyFrame;

int processThisCamera(cv::Mat cameraData);

private slots:
    void on_pushButton_left_clicked();

    void on_pushButton_mode_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_estop_clicked();
    void getNewFrame();

    void on_pushButton_estop_pressed();


    void on_pushButton_estop_released();

    void on_pushButton_up_pressed();

    void on_pushButton_up_released();

    void on_pushButton_right_pressed();

    void on_pushButton_right_released();

    void on_pushButton_left_pressed();

    void on_pushButton_left_released();

    void on_pushButton_down_pressed();

    void on_pushButton_down_released();

    void on_pushButton_circle_pressed();

    void on_pushButton_circle_released();

    void on_actionHello_Kitty_triggered();

    void on_actionDark_Souls_triggered();

    void on_lineEdit_ip_textEdited(const QString &arg1);

private:

    double calculateEncoderDelta(int prev, int actual);
    //--skuste tu nic nevymazat... pridavajte co chcete, ale pri odoberani by sa mohol stat nejaky drobny problem, co bude vyhadzovat chyby
    Ui::MainWindow *ui;
     void paintEvent(QPaintEvent *event);// Q_DECL_OVERRIDE;
     int updateLaserPicture;
     LaserMeasurement copyOfLaserData;
     std::string ipaddress;
     Robot robot;
     TKobukiData robotdata;
     int datacounter;
     QTimer *timer;
     void setTheme(std::string theme);

     QJoysticks *instance;

     QPixmap estop_pixmap;
     QPixmap estop_pixmap_pressed;
     QPixmap estop_pixmap_clicked;
     QPixmap purple_right;
     QPixmap purple_left;
     QPixmap purple_up;
     QPixmap purple_down;
     QPixmap purple_right_pressed;
     QPixmap purple_left_pressed;
     QPixmap purple_up_pressed;
     QPixmap purple_down_pressed;
     QPixmap purple_circle;
     QPixmap purple_circle_pressed;

     QPixmap red_right;
     QPixmap red_left;
     QPixmap red_up;
     QPixmap red_down;
     QPixmap red_right_pressed;
     QPixmap red_left_pressed;
     QPixmap red_up_pressed;
     QPixmap red_down_pressed;
     QPixmap red_circle;
     QPixmap red_circle_pressed;

     QPixmap red_square;
     QPixmap green_circle;



     double forwardspeed;//mm/s
     double rotationspeed;//omega/s

     int prev_x;
     int prev_y;
     int prev_gyro;
    bool first_run;

    int start_left;
    int start_right;
    int start_gyro;

    int prev_left;
    int prev_right;

    double delta_wheel_left;
    double delta_wheel_right;

    double robotX;
    double robotY;
    double robotFi;
    double prev_fi;

    bool estop;
    bool connected;

    std::string theme;

public slots:
     void setUiValues(double robotX,double robotY,double robotFi);
signals:
     void uiValuesChanged(double newrobotX,double newrobotY,double newrobotFi); ///toto nema telo


};

#endif // MAINWINDOW_H
