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
#include "point.h"
#include "ramp.h"
#include "controller.h"
#include <mutex>

#include <QDir>
#include <QDebug>
#include <chrono>


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
    cv::Mat frame[3];
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int processThisLidar(LaserMeasurement laserData);

    int processThisRobot(TKobukiData robotdata);
    friend class MyFrame;

    int processThisCamera(cv::Mat cameraData);
    int processThisSkeleton(skeleton skeledata);

private slots:

    void on_pushButton_mode_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_estop_clicked();
    void getNewFrame();

    void on_pushButton_estop_pressed();


    void on_pushButton_estop_released();

    void on_actionHello_Kitty_triggered();

    void on_actionDark_Souls_triggered();

    void on_lineEdit_ip_textEdited(const QString &arg1);

    void on_pushButton_camera_clicked();

    void on_pushButton_point_type_clicked();

    void on_pushButton_addpoint_clicked();

    void on_pushButton_startmission_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_removepoint_clicked();

private:
    void onFrameClicked(int x, int y);
    void detectBall(cv::Mat src);
    double calculateEncoderDelta(int prev, int actual);
    bool isFingerUp(float down, float mid_down, float mid_up, float up);
    //--skuste tu nic nevymazat... pridavajte co chcete, ale pri odoberani by sa mohol stat nejaky drobny problem, co bude vyhadzovat chyby
    Ui::MainWindow *ui;
     void paintEvent(QPaintEvent *event);// Q_DECL_OVERRIDE;
     int updateLaserPicture;
     LaserMeasurement copyOfLaserData;
     std::string ipaddress;
     Robot robot;
     TKobukiData robotdata;
     int updateSkeletonPicture;
     skeleton skeleJoints;
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
    bool rot_only;
    bool go;

    std::shared_ptr<PIController> controller;
    std::shared_ptr<Point> actual_point;
    std::shared_ptr<Point> set_point;
    std::shared_ptr<Point> desired_point;
    std::vector<Point> points_vector;


    double delta_wheel_left;
    double delta_wheel_right;

    std::atomic<double> robotX;
    std::atomic<double> robotY;
    std::atomic<double> robotFi;
    double prev_fi;

    int operation;

    bool estop;
    bool connected;

    bool backup_assistant;

    bool gestures;

    bool skeleton_rotation;

    bool found_ball;

    int ball_index;

    bool operational;

    bool add_points;

    bool start_mission;

    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

    std::string theme;

    double imageWidth;
    double imageHeight;

public slots:
     void setUiValues(double robotX,double robotY,double robotFi);
signals:
     void uiValuesChanged(double newrobotX,double newrobotY,double newrobotFi); ///toto nema telo


};

#endif // MAINWINDOW_H
