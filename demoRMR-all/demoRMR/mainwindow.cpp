#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFileDialog>
#include <math.h>


#define WHEELBASE 0.23
#define WHEELRADIUS 0.035
#define TICKTOMETER 0.000085292090497737556558
#define TICKTORAD 0.002436916871363930187454
#define ENCODEROVERFLOW 65535

#define WITHIN_TOLERANCE 30
#define WITHIN_TOLERANCE_THETA 0.0174533

///TOTO JE DEMO PROGRAM...AK SI HO NASIEL NA PC V LABAKU NEPREPISUJ NIC,ALE SKOPIRUJ SI MA NIEKAM DO INEHO FOLDERA
/// AK HO MAS Z GITU A ROBIS NA LABAKOVOM PC, TAK SI HO VLOZ DO FOLDERA KTORY JE JASNE ODLISITELNY OD TVOJICH KOLEGOV
/// NASLEDNE V POLOZKE Projects SKONTROLUJ CI JE VYPNUTY shadow build...
/// POTOM MIESTO TYCHTO PAR RIADKOV NAPIS SVOJE MENO ALEBO NEJAKY INY LUKRATIVNY IDENTIFIKATOR
/// KED SA NAJBLIZSIE PUSTIS DO PRACE, SKONTROLUJ CI JE MIESTO TOHTO TEXTU TVOJ IDENTIFIKATOR
/// AZ POTOM ZACNI ROBIT... AK TO NESPRAVIS, POJDU BODY DOLE... A NIE JEDEN,ALEBO DVA ALE BUDES RAD
/// AK SA DOSTANES NA SKUSKU


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //tu je napevno nastavena ip. treba zmenit na to co ste si zadali do text boxu alebo nejaku inu pevnu. co bude spravna
    ipaddress="127.0.0.1";//192.168.1.11toto je na niektory realny robot.. na lokal budete davat "127.0.0.1"
  //  cap.open("http://192.168.1.11:8000/stream.mjpg");
    ui->setupUi(this);
    datacounter=0;
  //  timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(getNewFrame()));
    go = false;
    actIndex=-1;
    useCamera1= false;
    first_run = true;
    robotX = 0;
    robotY = 0;
    robotFi = 0;
    prev_x = 0;
    prev_y = 0;
    prev_gyro = 0;
    prev_left = 0;
    prev_right = 0;
    datacounter=0;
    rot_only = false;
    controller = make_shared<PIController>(3,0.1,2);
    actual_point = make_shared<Point>(0,0,0);
    set_point = make_shared<Point>(0,0,0);
    desired_point = make_shared<Point>(0,0,0);
    controller->clearIntegral();

    connected=false;
    backup_assistant = false;
    gestures=false;

    skeleton_rotation = false;

    estop_pixmap.load(":/resources/img/estop.png");
    estop_pixmap_clicked.load(":/resources/img/estop_clicked.png");
    estop_pixmap_pressed.load(":/resources/img/estop_pressed.png");

    purple_right.load(":/resources/img/purple_right.png");
    purple_left.load(":/resources/img/purple_left.png");
    purple_up.load(":/resources/img/purple_up.png");
    purple_down.load(":/resources/img/purple_down.png");
    purple_right_pressed.load(":/resources/img/purple_right_pressed.png");
    purple_left_pressed.load(":/resources/img/purple_left_pressed.png");
    purple_up_pressed.load(":/resources/img/purple_up_pressed.png");
    purple_down_pressed.load(":/resources/img/purple_down_pressed.png");
    purple_circle.load(":/resources/img/purple_circle.png");
    purple_circle_pressed.load(":/resources/img/purple_circle_pressed.png");

    red_right.load(":/resources/img/red_right.png");
    red_left.load(":/resources/img/red_left.png");
    red_up.load(":/resources/img/red_up.png");
    red_down.load(":/resources/img/red_down.png");
    red_right_pressed.load(":/resources/img/red_right_pressed.png");
    red_left_pressed.load(":/resources/img/red_left_pressed.png");
    red_up_pressed.load(":/resources/img/red_up_pressed.png");
    red_down_pressed.load(":/resources/img/red_down_pressed.png");
    red_circle.load(":/resources/img/red_circle.png");
    red_circle_pressed.load(":/resources/img/red_circle_pressed.png");

    red_square.load(":/resources/img/red_square.png");
    green_circle.load(":/resources/img/green_circle.png");


    ui->pushButton_estop->setIcon(estop_pixmap);
    ui->pushButton_up->setIcon(purple_up);
    ui->pushButton_right->setIcon(purple_right);
    ui->pushButton_down->setIcon(purple_down);
    ui->pushButton_left->setIcon(purple_left);
    ui->pushButton_circle->setIcon(purple_circle);

    ui->label_led->setPixmap(red_square);

    ui->centralWidget->setStyleSheet("background-color:rgba(245, 168, 213,255)"); //pink colour

    ui->menuBar->setStyleSheet("QMenuBar{background-color:rgba(245, 168, 213,255); font-weight: bold; color:#d1007a ;};"
                               "QMenuBar::item{background-color:transparent;};"
                               "QMenuBar::item:selected{background-color:transparent;};"
                               "QMenuBar::item:pressed{background-color:transparent;};");

    ui->menuStyle->setStyleSheet("QMenu{background-color:#d1007a};"
                                 "QMenu::item{background-color:#d1007a};"
                                 "QMenu::item:selected{background-color:#d1007a}"); //TODO: find out how to change color with hover.... literally spent hours ....

    ui->statusBar->setStyleSheet("background-color:rgba(245, 168, 213,255)");

    ui->frame->setMainWindow(this);

    theme = "Hello Kitty";
    //button 3,2,5

    QSize estop_size;
    estop_size.setHeight(100);
    estop_size.setWidth(100);

    QSize arrow_size;
    arrow_size.setWidth(100);
    arrow_size.setHeight(100);

    QSize circle_size;
    circle_size.setHeight(50);
    circle_size.setWidth(50);

    QSize led_size;
    led_size.setHeight(22);
    led_size.setWidth(22);

    ui->label_led->setStyleSheet("background-color:transparent");

    red_square = red_square.scaled(led_size,Qt::KeepAspectRatio);
    green_circle = green_circle.scaled(led_size,Qt::KeepAspectRatio);

    ui->label_led->setPixmap(red_square);

    ui->pushButton_estop->setIconSize(estop_size);
    ui->pushButton_estop->setFixedSize(estop_size);
    ui->pushButton_estop->setStyleSheet("background-color:transparent");

    ui->pushButton_up->setIconSize(arrow_size);
    ui->pushButton_up->setFixedSize(arrow_size);
    ui->pushButton_up->setStyleSheet("background-color:transparent");

    ui->pushButton_right->setIconSize(arrow_size);
    ui->pushButton_right->setFixedSize(arrow_size);
    ui->pushButton_right->setStyleSheet("background-color:transparent");

    ui->pushButton_down->setIconSize(arrow_size);
    ui->pushButton_down->setFixedSize(arrow_size);
    ui->pushButton_down->setStyleSheet("background-color:transparent");

    ui->pushButton_left->setIconSize(arrow_size);
    ui->pushButton_left->setFixedSize(arrow_size);
    ui->pushButton_left->setStyleSheet("background-color:transparent");

    ui->pushButton_circle->setIconSize(circle_size);
    ui->pushButton_circle->setFixedSize(circle_size);
    ui->pushButton_circle->setStyleSheet("background-color:transparent");
    ui->gridLayout_4->setAlignment(ui->pushButton_circle,Qt::AlignCenter);

    ui->lineEdit_ip->setText(QString::fromStdString(ipaddress));
    ui->lineEdit_ip->setStyleSheet("QLineEdit {"
                           "    qproperty-alignment: AlignCenter;"
                           "    background-color: white;"
                           "}");

    ui->pushButton_mode->setStyleSheet("background-color: #d1007a;"
                                       "font-weight: bold;"
                                       "color: white");
    ui->pushButton_connect->setStyleSheet("background-color: #d1007a;"
                                          "font-weight: bold;"
                                          "color: white");
    ui->pushButton_camera->setStyleSheet("background-color: #d1007a;"
                                          "font-weight: bold;"
                                          "color: white");

    ui->pushButton_point_type->setStyleSheet("background-color: #d1007a;"
                                             "font-weight: bold;"
                                             "color: white");
    ui->pushButton_removepoint->setStyleSheet("background-color: #d1007a;"
                                              "font-weight: bold;"
                                              "color: white");
    ui->pushButton_addpoint->setStyleSheet("background-color: #d1007a;"
                                           "font-weight: bold;"
                                           "color: white");
    ui->pushButton_reset->setStyleSheet("background-color: #d1007a;"
                                        "font-weight: bold;"
                                        "color: white");
    ui->pushButton_startmission->setStyleSheet("background-color: #d1007a;"
                                               "font-weight: bold;"
                                               "color: white");

    ui->label_ip->setStyleSheet("font-weight: bold;"
                                "color: #d1007a");

    ui->label_camera->setStyleSheet("font-weight: bold;"
                                "color: #d1007a");


    ui->label_point_type->setStyleSheet("font-weight: bold;"
                                    "color: #d1007a");

    ui->label_warning->setStyleSheet("font-weight: bold;"
                                     "font-size:20px;"
                                "color: red");

    //TODO: ZVACSI FONT / DAJ HO NAD to

    //TODO: get rid of or set color to MainToolbar
    estop = false;
    connect(ui->frame,&MyFrame::clicked,this, &MainWindow::onFrameClicked);
    operational = false;
    found_ball = false;
    add_points = false;
    start_mission = false;
    ball_index = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{}

void MainWindow::onFrameClicked(int x, int y){
    //ak je connectnuty, ak je flag zadavaj body
    if (connected && add_points && !start_mission){
        Point p(x*10.0,y*10.0,0);
        if (operational){
            p.setOperation(true);
        }
        else {
            p.setOperation(false);
        }
        points_vector.push_back(p);
    }
    //print points_vectore
    std::cout << "POINTS VECTOR: ";
    for (int i = 0; i < points_vector.size(); i++){
        std::cout << points_vector[i].getX() << " " << points_vector[i].getY() << " " << points_vector[i].getOperation() << std::endl;
    }
}
/// toto je slot. niekde v kode existuje signal, ktory je prepojeny. pouziva sa napriklad (v tomto pripade) ak chcete dostat data z jedneho vlakna (robot) do ineho (ui)
/// prepojenie signal slot je vo funkcii  on_pushButton_left_clicked
void  MainWindow::setUiValues(double robotX,double robotY,double robotFi)
{
     // ui->lineEdit_2->setText(QString::number(robotX));
     // ui->lineEdit_3->setText(QString::number(robotY));
     // ui->lineEdit_4->setText(QString::number(robotFi));
}

double MainWindow::calculateEncoderDelta(int prev, int actual) {
    int delta;
    if (actual > 60000 && prev < 5000) {
        delta = actual - prev - ENCODEROVERFLOW;
    }
    else if (actual < 5000 && prev > 60000) {
        delta = actual - prev + ENCODEROVERFLOW;
    }
    else {
        delta = actual - prev;
    }
    return TICKTOMETER*delta;

}

///toto je calback na data z robota, ktory ste podhodili robotu vo funkcii on_pushButton_left_clicked
/// vola sa vzdy ked dojdu nove data z robota. nemusite nic riesit, proste sa to stane
int MainWindow::processThisRobot(TKobukiData robotdata)
{
    //TODO: atomic double robotX, robotY, robotFi
    if(first_run){
        start_left = robotdata.EncoderLeft;
        start_right = robotdata.EncoderRight;
        start_gyro = robotdata.GyroAngle;
        first_run = false;
        prev_left = start_left;
        prev_right = start_right;
    }

    {
        delta_wheel_right = calculateEncoderDelta(prev_right, robotdata.EncoderRight); //TODO: vyhodit funkciu kvoli speed a dat kod napriamo sem?
        delta_wheel_left = calculateEncoderDelta(prev_left, robotdata.EncoderLeft);
        robotFi = robotFi + (delta_wheel_right - delta_wheel_left) / WHEELBASE/PI*180.0;
        if (robotFi >= 180){
            robotFi = robotFi - 360;
        }
        else if (robotFi < -180) {
            robotFi = robotFi + 360;
        }
        if (delta_wheel_left == delta_wheel_right) {
            robotX = robotX + (delta_wheel_left + delta_wheel_right)/2*cos(robotFi*PI/180.0);
            robotY = robotY + (delta_wheel_left + delta_wheel_right)/2*sin(robotFi*PI/180.0);
        }
        else {
            robotX = robotX + (delta_wheel_right+delta_wheel_left)/(delta_wheel_right-delta_wheel_left)*WHEELBASE/2*(sin(robotFi*PI/180.0)-sin(prev_fi*PI/180.0));
            robotY = robotY - (delta_wheel_right+delta_wheel_left)/(delta_wheel_right-delta_wheel_left)*WHEELBASE/2*(cos(robotFi*PI/180.0)-cos(prev_fi*PI/180.0));
        }


        prev_right=robotdata.EncoderRight;
        prev_left=robotdata.EncoderLeft;
        prev_fi = robotFi;

        actual_point->setPoint(robotX*1000, robotY*1000, robotFi*PI/180.0);


        //TODO: go a connected atomic bool?
        if (go && connected) {

            double rot_speed;
            int trans_speed, radius;

            if (!points_vector.empty()){
                desired_point->setPoint(points_vector[0].getX(),points_vector[0].getY(),0);
            }
            else {
                go = false;
                start_mission = false;
                ui->pushButton_startmission->setText("START MISSION");
                return 0;
            }
            //toto vzdy nastavi ciel, ak je vo vektore bodov aspon jeden bod
            controller->computeErrors(*actual_point,*desired_point);

            controller->compute(*actual_point,*desired_point,(double)1/40, &trans_speed, &rot_speed);

            if(abs(controller->error_distance) < WITHIN_TOLERANCE){
                controller->clearIntegral();
                robot.setTranslationSpeed(0);
                controller->ramp.clear_time_hard();
                if (!points_vector.empty()){
                    //toto asi nemusi byt v ife - just to be sure
                    points_vector.erase(points_vector.begin());
                }
                std::cout << "clear integral" << std::endl;
                return 0;
            }

            if (abs(controller->error_angle) >= PI/4 && !rot_only){
                //ak je uhol moc velky nastavi sa flag na rotaciu na mieste
                rot_only = true;
                controller->ramp.clear_time_hard();
                controller->clearIntegral();
                std::cout << "ONLY ROT: " << controller->error_angle << std::endl;
                std::cout << "Actual Theta: " << actual_point->getTheta() << std::endl;
                std::cout << "Desired Theta: " << atan2(desired_point->getY()-actual_point->getY(),desired_point->getX()-actual_point->getX()) << std::endl;
            }

            if (rot_only){
                //ROTATION
                robot.setRotationSpeed(rot_speed);
            }
            else{
                //ARC
                radius = trans_speed/rot_speed;
                if(radius > 32767)
                    radius = 32767;
                else if(radius < -32767)
                    radius = -32767;
                robot.setArcSpeed(trans_speed,radius);
            }
            if (rot_only && abs(controller->error_angle)<=4*PI/180){
                rot_only = false;
                controller->ramp.clear_time_hard();
                controller->clearIntegral();
            }
        } //if go koniec

        ///toto neodporucam na nejake komplikovane struktury.signal slot robi kopiu dat. radsej vtedy posielajte
        /// prazdny signal a slot bude vykreslovat strukturu (vtedy ju musite mat samozrejme ako member premmennu v mainwindow.ak u niekoho najdem globalnu premennu,tak bude cistit bludisko zubnou kefkou.. kefku dodam)
        /// vtedy ale odporucam pouzit mutex, aby sa vam nestalo ze budete pocas vypisovania prepisovat niekde inde

    }
    datacounter++;


    return 0;

}

///toto je calback na data z lidaru, ktory ste podhodili robotu vo funkcii on_pushButton_left_clicked
/// vola sa ked dojdu nove data z lidaru
int MainWindow::processThisLidar(LaserMeasurement laserData)
{


    memcpy( &copyOfLaserData,&laserData,sizeof(LaserMeasurement));
    //tu mozete robit s datami z lidaru.. napriklad najst prekazky, zapisat do mapy. naplanovat ako sa prekazke vyhnut.
    // ale nic vypoctovo narocne - to iste vlakno ktore cita data z lidaru
    updateLaserPicture=1;
    update();//tento prikaz prinuti prekreslit obrazovku.. zavola sa paintEvent funkcia


    return 0;

}

void MainWindow::detectBall(cv::Mat src){

    // src = cv::imread(cv::samples::findFile("C:\\Users\\HP Pavilion\\Desktop\\ball.png"), cv::IMREAD_COLOR); //for debug purposes

    // Check if image is loaded fine
    if (src.empty()) {
        // printf("Error no data\n");
        return;
    }
    //100 //55
    //ok i guess
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(gray, gray, 5);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
                     gray.rows / 16, // change this value to detect circles with different distances to each other
                     100, 45, 50, 0 // change the last two parameters
                     // (min_radius & max_radius) to detect larger circles
                     );
    if (!circles.empty()){
        if (!found_ball){
            for (size_t i = 0; i < circles.size(); i++) {
                cv::Vec3i c = circles[i];
                cv::Point center = cv::Point(c[0], c[1]);
                // circle center
                cv::circle(src, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
                // circle outline
                int radius = c[2];
                cv::circle(src, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
            }
            QString currentDir = QDir::currentPath();
            QDir baseDir(currentDir);
            baseDir.cdUp(); // Navigate one level up

            QString subDir = baseDir.filePath("Pictures");

            // Construct the full path for the image to save
            QString filePath = subDir + "/ball";
            // Convert QString to std::string for cv::imwrite
            // cv::imwrite(filePath.toStdString()+std::to_string(ball_index)+".jpg", src);
            // cv::imshow("detected circles "+std::to_string(ball_index) , src);
            found_ball = true;
            ball_index++;
            start_time = std::chrono::high_resolution_clock::now();
        }
        else{
            auto time_now = std::chrono::high_resolution_clock::now();
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(time_now - start_time);
            if (elapsed_seconds.count() >= 5){
                found_ball = false;
            }
        }
    }
    else {
        found_ball = false;
    }
    return ;

}

///toto je calback na data z kamery, ktory ste podhodili robotu vo funkcii on_pushButton_left_clicked
/// vola sa ked dojdu nove data z kamery
int MainWindow::processThisCamera(cv::Mat cameraData)
{
    cameraData.copyTo(frame[(actIndex+1)%3]);//kopirujem do nasej strukury
    actIndex=(actIndex+1)%3;//aktualizujem kde je nova fotka
    updateLaserPicture=1;
    //TODO: nech sa passuju data z detekcie lopty do frameu

    cv::Mat ball_detection;
    cameraData.copyTo(ball_detection);

    // detectBall(ball_detection);

    update();
    return 0;
}

bool MainWindow::isFingerUp(float down, float mid_down, float mid_up, float up){
    return (down > mid_down && mid_down > mid_up && mid_up > up);
}

///toto je calback na data zo skeleton trackera, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa ked dojdu nove data z trackera
int MainWindow::processThisSkeleton(skeleton skeledata)
{

    memcpy(&skeleJoints,&skeledata,sizeof(skeleton));
    updateSkeletonPicture=1;
    if (gestures && !estop ){
        bool left_index_finger = isFingerUp(skeleJoints.joints[left_index_cmc].y,skeleJoints.joints[left_index_mcp].y,skeleJoints.joints[left_index_ip].y,skeleJoints.joints[left_index_tip].y);
        bool left_middle_finger = isFingerUp(skeleJoints.joints[left_middle_cmc].y,skeleJoints.joints[left_middle_mcp].y,skeleJoints.joints[left_middle_ip].y,skeleJoints.joints[left_middle_tip].y);
        bool left_ring_finger = isFingerUp(skeleJoints.joints[left_ring_cmc].y,skeleJoints.joints[left_ring_mcp].y,skeleJoints.joints[left_ring_ip].y,skeleJoints.joints[left_ringy_tip].y);
        bool left_pinky_finger = isFingerUp(skeleJoints.joints[left_pinky_cmc].y,skeleJoints.joints[left_pink_mcp].y,skeleJoints.joints[left_pink_ip].y,skeleJoints.joints[left_pink_tip].y);
        bool left_thumb_finger = isFingerUp(skeleJoints.joints[left_thumb_cmc].x,skeleJoints.joints[left_thumb_mcp].x,skeleJoints.joints[left_thumb_ip].x,skeleJoints.joints[left_thumb_tip].x);
        bool left_hand = left_index_finger && left_middle_finger && left_ring_finger && left_pinky_finger && left_thumb_finger;

        float right_hand_y = skeleJoints.joints[right_wrist].y;

        if (left_hand) {
            if (right_hand_y!=0.0){
                if (skeleton_rotation){
                    robot.setRotationSpeed((0.5-right_hand_y) * PI/2);
                }
                else {
                    if ((0.5-right_hand_y)*200*2 < 0){
                        backup_assistant = true;
                    }
                    else {
                        backup_assistant = false;
                    }
                    robot.setTranslationSpeed((0.5-right_hand_y)*200*2);
                }
            }
        }
        else if(left_thumb_finger && !left_pinky_finger && !left_index_finger && !left_middle_finger && !left_ring_finger) {
            robot.setRotationSpeed(-PI/4);
            skeleton_rotation = true;
        }
        else if(left_pinky_finger && !left_thumb_finger && !left_index_finger && !left_middle_finger && !left_ring_finger) {
            robot.setRotationSpeed(PI/4);
            skeleton_rotation = true;
        }
        else if(left_index_finger && left_middle_finger && !left_ring_finger && !left_pinky_finger && !left_thumb_finger) {
            robot.setTranslationSpeed(-200);
            skeleton_rotation = false;
            backup_assistant = true;
        }
        else if(left_index_finger && !left_middle_finger && !left_ring_finger && !left_pinky_finger && !left_thumb_finger) {
            robot.setTranslationSpeed(200);
            skeleton_rotation = false;
            backup_assistant = false;
        }
        else if (!left_index_finger && !left_middle_finger && !left_ring_finger && !left_pinky_finger && !left_thumb_finger) {
            if (skeleton_rotation){
                robot.setRotationSpeed(0);
            }
            else {
                robot.setTranslationSpeed(0);
            }
        }
    }

    return 0;
}

void MainWindow::on_pushButton_left_clicked()
{

}

void MainWindow::on_pushButton_mode_clicked() //this is load map i just didnt have the tiem to refactor it all....
{
    if (connected){
        QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::currentPath(), "Text Files (*.txt)");

        // Check if a file was selected
        if (!filePath.isEmpty()) {
            //TODO: zatial fixna
            ui->frame->loadMap(filePath);
            }
            else{
                std::cout << "Failed" << std::endl;
            }
    }
}

void MainWindow::on_pushButton_connect_clicked()
{

    if (!connected){
        //ziskanie joystickov
        instance = QJoysticks::getInstance();
        forwardspeed=0;
        rotationspeed=0;
        //tu sa nastartuju vlakna ktore citaju data z lidaru a robota
        // connect(this,SIGNAL(uiValuesChanged(double,double,double)),this,SLOT(setUiValues(double,double,double)));

        ///setovanie veci na komunikaciu s robotom/lidarom/kamerou.. su tam adresa porty a callback.. laser ma ze sa da dat callback aj ako lambda.
        /// lambdy su super, setria miesto a ak su rozumnej dlzky,tak aj prehladnost... ak ste o nich nic nepoculi poradte sa s vasim doktorom alebo lekarnikom...
        robot.setLaserParameters(ipaddress,52999,5299,/*[](LaserMeasurement dat)->int{std::cout<<"som z lambdy callback"<<std::endl;return 0;}*/std::bind(&MainWindow::processThisLidar,this,std::placeholders::_1));
        robot.setRobotParameters(ipaddress,53000,5300,std::bind(&MainWindow::processThisRobot,this,std::placeholders::_1));
        int port;
        if (ipaddress=="127.0.0.1"){
            port = 8889;
        }
        else {
            port = 8000;
        }
        std::cout<< "ipadd " << ipaddress << std::endl;
        std::cout<< "port " << port << std::endl;
        //---simulator ma port 8889, realny robot 8000 //TODO: ak to neni localhost dat port 8000
        robot.setCameraParameters("http://"+ipaddress+":"+std::to_string(port)+"/stream.mjpg",std::bind(&MainWindow::processThisCamera,this,std::placeholders::_1));
        robot.setSkeletonParameters("127.0.0.1",23432,23432,std::bind(&MainWindow::processThisSkeleton,this,std::placeholders::_1));
        ///ked je vsetko nasetovane tak to tento prikaz spusti (ak nieco nieje setnute,tak to normalne nenastavi.cize ak napr nechcete kameru,vklude vsetky info o nej vymazte)
        robot.robotStart();






        /// prepojenie joysticku s jeho callbackom... zas cez lambdu. neviem ci som to niekde spominal,ale lambdy su super. okrem toho mam este rad ternarne operatory a spolocneske hry ale to tiez nikoho nezaujima
        /// co vas vlastne zaujima? citanie komentov asi nie, inak by ste citali toto a ze tu je blbosti
        // connect(
        //     instance, &QJoysticks::axisChanged,
        //     [this]( const int js, const int axis, const qreal value) { if(/*js==0 &&*/ axis==1){forwardspeed=-value*300;}
        //         if(/*js==0 &&*/ axis==0){rotationspeed=-value*(3.14159/2.0);}}
        //     );
        connected = true;
        ui->label_led->setPixmap(green_circle);
        ui->pushButton_connect->setText("DISCONNECT");
        ui->lineEdit_ip->setReadOnly(true);
    }
    else {
        robot.robotStop();
        connected = false;
        ui->label_led->setPixmap(red_square);
        ui->pushButton_connect->setText("CONNECT");
        ui->lineEdit_ip->setReadOnly(false);
        update();
    }
}


void MainWindow::on_pushButton_estop_clicked()
{
    estop = !estop;
    if (estop) {
        ui->pushButton_estop->setIcon(estop_pixmap_clicked);
        robot.setTranslationSpeed(0);
        ui->label_warning->setText("ESTOP ACTIVATED");
    }
    else {
        ui->pushButton_estop->setIcon(estop_pixmap);
        ui->label_warning->setText("");
    }
    //TODO: logic
}

void MainWindow::getNewFrame()
{

}

void MainWindow::on_pushButton_estop_pressed()
{
    ui->pushButton_estop->setIcon(estop_pixmap_pressed);
}

void MainWindow::on_pushButton_estop_released() {
    if (estop) {
        ui->pushButton_estop->setIcon(estop_pixmap_clicked);
    }
    else {
        ui->pushButton_estop->setIcon(estop_pixmap);
    }
}

void MainWindow::on_pushButton_up_pressed()
{
    backup_assistant = false;
    if (theme == "Hello Kitty"){
        ui->pushButton_up->setIcon(purple_up_pressed);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_up->setIcon(red_up_pressed);
    }
    if(!estop && !gestures && connected){
        robot.setTranslationSpeed(250);
    }
}




void MainWindow::on_pushButton_up_released()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_up->setIcon(purple_up);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_up->setIcon(red_up);
    }
}


void MainWindow::on_pushButton_right_pressed()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_right->setIcon(purple_right_pressed);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_right->setIcon(red_right_pressed);
    }
    if(!estop && !gestures && connected){
        robot.setRotationSpeed(-3.14159/2);
    }
}


void MainWindow::on_pushButton_right_released()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_right->setIcon(purple_right);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_right->setIcon(red_right);
    }
}


void MainWindow::on_pushButton_left_pressed()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_left->setIcon(purple_left_pressed);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_left->setIcon(red_left_pressed);
    }
    if(!estop && !gestures && connected){
        robot.setRotationSpeed(3.14159/2);
    }
}


void MainWindow::on_pushButton_left_released()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_left->setIcon(purple_left);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_left->setIcon(red_left);
    }
}


void MainWindow::on_pushButton_down_pressed()
{
    backup_assistant = true;
    if (theme == "Hello Kitty"){
        ui->pushButton_down->setIcon(purple_down_pressed);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_down->setIcon(red_down_pressed);
    }
    if(!estop && !gestures && connected){
        robot.setTranslationSpeed(-250);
    }
}


void MainWindow::on_pushButton_down_released()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_down->setIcon(purple_down);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_down->setIcon(red_down);
    }
}


void MainWindow::on_pushButton_circle_pressed()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_circle->setIcon(purple_circle_pressed);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_circle->setIcon(red_circle_pressed);
    }
    if (!estop && !gestures && connected){
        robot.setTranslationSpeed(0);     //TODO: when clicked?
    }
}


void MainWindow::on_pushButton_circle_released()
{
    if (theme == "Hello Kitty"){
        ui->pushButton_circle->setIcon(purple_circle);
    }
    else if (theme == "Dark Souls") {
        ui->pushButton_circle->setIcon(red_circle);
    }
}


void MainWindow::on_actionHello_Kitty_triggered()
{
    if (theme != "Hello Kitty") {
        setTheme("Hello Kitty");
        theme = "Hello Kitty";
    }
}


void MainWindow::on_actionDark_Souls_triggered()
{
    if (theme != "Dark Souls") {
        setTheme("Dark Souls");
        theme = "Dark Souls";
    }
}

void MainWindow::setTheme(std::string theme) {
    if (theme == "Hello Kitty") {
        ui->centralWidget->setStyleSheet("background-color:rgba(245, 168, 213,255)"); //hello kitty
        ui->menuBar->setStyleSheet("QMenuBar{background-color:rgba(245, 168, 213,255) ;font-weight: bold; color:#d1007a ;};"
                                   "QMenuBar::item{background-color:transparent};"
                                   "QMenuBar::item:selected{background-color:transparent;};"
                                   "QMenuBar::item:pressed{background-color:transparent;}");

        ui->menuStyle->setStyleSheet("QMenu{background-color:#d1007a};"
                                     "QMenu::item{background-color:#d1007a};"
                                     "QMenu::item:selected{background-color:#d1007a}");

        ui->statusBar->setStyleSheet("background-color:rgba(245, 168, 213,255)");

        ui->pushButton_mode->setStyleSheet("background-color: #d1007a;"
                                           "font-weight: bold;"
                                           "color: white");
        ui->pushButton_connect->setStyleSheet("background-color: #d1007a;"
                                              "font-weight: bold;"
                                              "color: white");
        ui->pushButton_camera->setStyleSheet("background-color: #d1007a;"
                                           "font-weight: bold;"
                                           "color: white");
        ui->pushButton_point_type->setStyleSheet("background-color: #d1007a;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_removepoint->setStyleSheet("background-color: #d1007a;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_addpoint->setStyleSheet("background-color: #d1007a;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_reset->setStyleSheet("background-color: #d1007a;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_startmission->setStyleSheet("background-color: #d1007a;"
                                             "font-weight: bold;"
                                             "color: white");

        ui->label_ip->setStyleSheet("font-weight: bold;"
                                    "color: #d1007a");

        ui->label_camera->setStyleSheet("font-weight: bold;"
                                    "color: #d1007a");
        ui->label_point_type->setStyleSheet("font-weight: bold;"
                                        "color: #d1007a");

        ui->pushButton_up->setIcon(purple_up);
        ui->pushButton_right->setIcon(purple_right);
        ui->pushButton_down->setIcon(purple_down);
        ui->pushButton_left->setIcon(purple_left);
        ui->pushButton_circle->setIcon(purple_circle);
    }
    else if (theme == "Dark Souls") {
        ui->centralWidget->setStyleSheet("background-color:rgba(20, 0, 3,255)"); //dark souls
        ui->menuBar->setStyleSheet("QMenuBar{background-color:rgba(20, 0, 3,255); font-weight: bold; color:#770000};"
                                   "QMenuBar::item{background-color:transparent;};"
                                   "QMenuBar::item:selected{background-color:transparent;};"
                                   "QMenuBar::item:pressed{background-color:transparent;}");

        ui->menuStyle->setStyleSheet("QMenu{background-color:#770000};"
                                     "QMenu::item{background-color:#770000};"
                                     "QMenu::item:selected{background-color:#770000}");

        ui->statusBar->setStyleSheet("background-color:rgba(20, 0, 3,255)");

        ui->pushButton_mode->setStyleSheet("background-color: #770000;"
                                           "font-weight: bold;"
                                           "color: white");
        ui->pushButton_connect->setStyleSheet("background-color: #770000;"
                                              "font-weight: bold;"
                                              "color: white");
        ui->pushButton_camera->setStyleSheet("background-color: #770000;"
                                              "font-weight: bold;"
                                              "color: white");
        ui->pushButton_point_type->setStyleSheet("background-color: #770000;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_removepoint->setStyleSheet("background-color: #770000;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_reset->setStyleSheet("background-color: #770000;"
                                             "font-weight: bold;"
                                             "color: white");
        ui->pushButton_startmission->setStyleSheet("background-color: #770000;"
                                             "font-weight: bold;"
                                             "color: white");

        ui->pushButton_addpoint->setStyleSheet("background-color: #770000;"
                                             "font-weight: bold;"
                                             "color: white");

        ui->label_ip->setStyleSheet("font-weight: bold;"
                                    "color: #770000");

        ui->label_camera->setStyleSheet("font-weight: bold;"
                                    "color: #770000");
        ui->label_point_type->setStyleSheet("font-weight: bold;"
                                        "color: #770000");


        ui->pushButton_up->setIcon(red_up);
        ui->pushButton_right->setIcon(red_right);
        ui->pushButton_down->setIcon(red_down);
        ui->pushButton_left->setIcon(red_left);
        ui->pushButton_circle->setIcon(red_circle);
    }
}



void MainWindow::on_lineEdit_ip_textEdited(const QString &arg1)
{
    ipaddress = arg1.toStdString();
}

void MainWindow::on_pushButton_camera_clicked()
{
    if (useCamera1){
        useCamera1 = false;
        ui->pushButton_camera->setText("LIDAR");
    }
    else {
        useCamera1 = true;
        ui->pushButton_camera->setText("CAMERA");
    }
}


void MainWindow::on_pushButton_point_type_clicked()
{
    if(!operational){
        ui->pushButton_point_type->setText("OPERATIONAL");
        operational = true;
    }
    else{
        ui->pushButton_point_type->setText("CROSSING");
        operational = false;
    }
}


void MainWindow::on_pushButton_addpoint_clicked()
{
    if(!add_points){
        ui->pushButton_addpoint->setText("STOP ADDING");
        add_points = true;
    }
    else{
        ui->pushButton_addpoint->setText("ADD POINTS");
        add_points = false;
    }
}


void MainWindow::on_pushButton_startmission_clicked()
{
    if (!start_mission){
        ui->pushButton_startmission->setText("STOP MISSION");
        start_mission = true;
        go = true;
    }
    else {
        ui->pushButton_startmission->setText("START MISSION");
        start_mission = false;
        go = false;
    }
}


void MainWindow::on_pushButton_reset_clicked()
{
    if (!start_mission){
        points_vector.clear();
    }
}


void MainWindow::on_pushButton_removepoint_clicked()
{
    if (!start_mission && !points_vector.empty()){
        points_vector.pop_back();
    }
}

