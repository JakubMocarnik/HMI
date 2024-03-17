// MyFrame.cpp
#include "myframe.h"
#include <QPainter>
#include "mainwindow.h"
#include <QtMath>

MyFrame::MyFrame(QWidget *parent) : QFrame(parent) {
    // Additional setup if needed
}

MyFrame::~MyFrame() {
    // Cleanup if needed
}

void MyFrame::setMainWindow(MainWindow *main_window){
    this->main_window = main_window;
}

void MyFrame::printStuff() {
    std::cout << "camera: " << main_window->useCamera1 << std::endl;
    std::cout << "robot FI: " << main_window->robotFi << std::endl;
}


void MyFrame::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::black);//cierna farba pozadia(pouziva sa ako fill pre napriklad funkciu drawRect)

    //pen pre Lidar pohlad
    QPen pero;
    pero.setStyle(Qt::SolidLine);//styl pera - plna ciara
    pero.setWidth(3);//hrubka pera -3pixely
    pero.setColor(Qt::green);//farba je zelena
    QPen red_pen;
    red_pen.setStyle(Qt::SolidLine);//styl pera - plna ciara
    red_pen.setWidth(3);//hrubka pera -3pixely
    red_pen.setColor(Qt::red);//farba je zelena
    QPen yellow_pen;
    yellow_pen.setStyle(Qt::SolidLine);//styl pera - plna ciara
    yellow_pen.setWidth(3);//hrubka pera -3pixely
    yellow_pen.setColor(Qt::yellow);//farba je zelena

    //rectangle pre frame vykreslovania v MainWindow
    QRect rect;
    rect= this->geometry();//ziskate porametre stvorca,do ktoreho chcete kreslit
    rect.translate(5,10);
    painter.drawRect(rect);


    first_warning.load(":/resources/img/transparent_warning");
    second_warning.load(":/resources/img/yellow_warning");
    third_warning.load(":/resources/img/red_warning");

    //rectangles pre jednotlive varovania
    // int rectThickness = rect.height()/20;
    // QRect topRect;
    // topRect.setX(rect.x());
    // topRect.setY(rect.y());
    // topRect.setWidth(rect.width());
    // topRect.setHeight(rectThickness);
    // QRect bottomRect;
    // bottomRect.setX(rect.x());
    // bottomRect.setY(rect.height() - rectThickness);
    // bottomRect.setWidth(rect.width());
    // bottomRect.setHeight(rectThickness);
    // QRect leftRect;
    // leftRect.setX(rect.x());
    // leftRect.setY(rectThickness);
    // leftRect.setWidth(rectThickness);
    // leftRect.setHeight(rect.height() - 2*rectThickness);
    // QRect rightRect;
    // rightRect.setX(rect.width() - rectThickness);
    // rightRect.setY(rectThickness);
    // rightRect.setWidth(rectThickness);
    // rightRect.setHeight(rect.height() - 2*rectThickness);

    // Define rectangles for each side
    int rectThickness = rect.height()/20;

    QRect topRect(rect.x(), rect.y(), rect.width(), rectThickness);
    QRect bottomRect(rect.x(), rect.height() - rectThickness, rect.width(), rectThickness);
    QRect leftRect(rect.x(), rectThickness, rectThickness, rect.height() - 2 * rectThickness);
    QRect rightRect(rect.width() - rectThickness, rectThickness, rectThickness, rect.height() - 2 * rectThickness);

    // Define polygons for each side
    QPolygon topPolygon;
    topPolygon << rect.topLeft()
               << rect.topRight()
               << QPoint(rect.right() - rectThickness, rect.top() + rectThickness)
               << QPoint(rect.left() + rectThickness, rect.top() + rectThickness);

    QPolygon bottomPolygon;
    bottomPolygon << QPoint(rect.left() + rectThickness, rect.bottom() - rectThickness)
                  << QPoint(rect.right() - rectThickness, rect.bottom() - rectThickness)
                  << rect.bottomRight()
                  << rect.bottomLeft();

    QPolygon leftPolygon;
    leftPolygon << QPoint(rect.left() + rectThickness, rect.top() + rectThickness)
                << rect.topLeft()
                << rect.bottomLeft()
                << QPoint(rect.left() + rectThickness, rect.bottom() - rectThickness);

    QPolygon rightPolygon;
    rightPolygon << QPoint(rect.right() - rectThickness, rect.top() + rectThickness)
                 << rect.topRight()
                 << rect.bottomRight()
                 << QPoint(rect.right() - rectThickness, rect.bottom() - rectThickness);



    if (main_window->connected){
        if(main_window->useCamera1==true && main_window->actIndex>-1)/// ak zobrazujem data z kamery a aspon niektory frame vo vectore je naplneny
        {
            QImage image = QImage((uchar*)main_window->frame[main_window->actIndex].data, main_window->frame[main_window->actIndex].cols, main_window->frame[main_window->actIndex].rows, main_window->frame[main_window->actIndex].step, QImage::Format_RGB888  );//kopirovanie cvmat do qimage
            painter.drawImage(rect,image.rgbSwapped());

            if(main_window->useCamera1==true && main_window->actIndex>-1)
            {
                if(main_window->updateLaserPicture==1) ///ak mam nove data z lidaru
                {
                    main_window->updateLaserPicture=0;

                    //painter.setPen(pero);
                    //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
                    //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
                    // for(int k=0;k<main_window->copyOfLaserData.numberOfScans/*360*/;k++)
                    // {
                    //     int dist=main_window->copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                    //     int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky
                    //     int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky
                    //     if(rect.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    //         painter.drawEllipse(QPoint(xp, yp),2,2);
                    // }
                }
            }


            for(int k=0; k < main_window->copyOfLaserData.numberOfScans/*360*/;k++)
            {
                int dist=main_window->copyOfLaserData.Data[k].scanDistance/20;
                double uhol = 360.0-main_window->copyOfLaserData.Data[k].scanAngle;

                // // Convert the angle to radians
                // double angleRad = qDegreesToRadians(uhol);

                // // Calculate the x and y coordinates based on distance and angle
                // int xp = static_cast<int>(dist * qCos(angleRad)); // x coordinate
                // int yp = static_cast<int>(dist * qSin(angleRad)); // y coordinate

                // // Calculate the position of the image based on the LIDAR data coordinates and frame dimensions
                // int x = rect.center().x() + xp; // x position relative to the frame center
                // int y = rect.center().y() + yp; // y position relative to the frame center

                // // Ensure that the image stays within the bounds of the frame
                // x = qBound(rect.left(), x, rect.right() - 240);
                // y = qBound(rect.top(), y, rect.bottom() - 240);


                if(uhol < 45 || uhol >315 ){

                    double bx = dist*cos(uhol*3.14159/180.0);
                    double by = dist*sin(uhol*3.14159/180.0);

                    //int x = rect.width()/2  - ( (681.743*by) / (bx-14.5) );
                    //int y = rect.height()/2 + ( (681.743*(-21+11.5)) / (bx-14.5)  )/10;
                    //painter.drawEllipse(QPoint(x, y),2,2);

                    int x = rect.width() / 2 - (681.743 * by) / (bx - 14.5);
                    int y = rect.height() / 2 + ((681.743 * (-21 + 11.5)) / (bx - 14.5)) / 10;

                    // Calculate the position of the obstacle relative to the frame's top-left corner
                    x -= image.width() / 2; // Adjust for the image width
                    y -= image.height() / 2; // Adjust for the image height

                    if(rect.contains(x,y))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    {
                        if(dist < 30){
                            QPainter painter(this);
                            painter.setBrush(Qt::red);
                            //painter.drawRect(topRect);
                            painter.drawPolygon(topPolygon);
                            painter.drawPixmap(QRect(x,y,240,240),third_warning);
                        }
                        else if(dist >30 && dist < 60){
                            QPainter painter(this);
                            painter.setBrush(Qt::yellow);
                            //painter.drawRect(topRect);
                            painter.drawPolygon(topPolygon);
                            painter.drawPixmap(QRect(x,y,240,240),second_warning);
                        }
                        else if(dist > 60){
                            //painter.drawImage(QRect(x,y,50,50),first_warning);
                            QPainter painter(this);
                            painter.setBrush(Qt::green);
                            //painter.drawRect(topRect);
                            painter.drawPolygon(topPolygon);
                            //painter.drawPixmap(QRect(x,y,240,240),first_warning);
                        }

                    }
                }

                if(uhol < 135 && uhol > 45){

                    if(dist < 30){
                        QPainter painter(this);
                        painter.setBrush(Qt::red);
                        //painter.drawRect(leftRect);
                        painter.drawPolygon(leftPolygon);

                    }
                    else if(dist >30 && dist < 60){
                        QPainter painter(this);
                        painter.setBrush(Qt::yellow);
                        //painter.drawRect(leftRect);
                        painter.drawPolygon(leftPolygon);

                    }
                    else if(dist > 60){
                        QPainter painter(this);
                        painter.setBrush(Qt::green);
                        //painter.drawRect(leftRect);
                        painter.drawPolygon(leftPolygon);

                    }
                }

                if(uhol < 225 && uhol > 135){

                    if(dist < 30){
                        QPainter painter(this);
                        painter.setBrush(Qt::red);
                        //painter.drawRect(bottomRect);
                        painter.drawPolygon(bottomPolygon);

                    }
                    else if(dist >30 && dist < 60){
                        QPainter painter(this);
                        painter.setBrush(Qt::yellow);
                        //painter.drawRect(bottomRect);
                        painter.drawPolygon(bottomPolygon);
                    }
                    else if(dist > 60){
                        QPainter painter(this);
                        painter.setBrush(Qt::green);
                        //painter.drawRect(bottomRect);
                        painter.drawPolygon(bottomPolygon);
                    }


                }


                if(uhol < 315 && uhol > 225){
                    if(dist < 30){
                        QPainter painter(this);
                        painter.setBrush(Qt::red);
                        //painter.drawRect(rightRect);
                        painter.drawPolygon(rightPolygon);
                    }
                    else if(dist >30 && dist < 60){
                        QPainter painter(this);
                        painter.setBrush(Qt::yellow);
                        //painter.drawRect(rightRect);
                        painter.drawPolygon(rightPolygon);
                    }
                    else if(dist > 60){
                        QPainter painter(this);
                        painter.setBrush(Qt::green);
                        //painter.drawRect(rightRect);
                        painter.drawPolygon(rightPolygon);
                    }
                }

            }

            }
        }
            //   // this->setStyleSheet("background-color: rgb(105, 105, 105)");
            // if(main_window->useCamera1==true && main_window->backup_assistant==true) ///ak mam nove data z lidaru
            // {
            //     main_window->updateLaserPicture=0;

            //     //painter.setPen(pero);
            //     //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
            //     //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
            //     for(int k=0;k<main_window->copyOfLaserData.numberOfScans/*360*/;k++)
            //     {
            //         // Calculate the position of the backup assistant rectangle
            //         int rectX = rect.center().x() - rect.width() / 2; // X coordinate to place the rectangle in the middle
            //         int rectY = rect.top() + 10; // Y coordinate to place the rectangle at the top
            //         QPainter painter(this);
            //         painter.setBrush(Qt::black); // Set the brush color
            //         // Define the backup assistant rectangle
            //         QRect backupAssistantRect(rectX, rectY, rect.width(), rect.height());

            //         int dist=main_window->copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
            //         int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky
            //         int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky
            //         double uhol = 360.0-main_window->copyOfLaserData.Data[k].scanAngle;

            //        if(rect.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
            //         {

            //             if(dist > 60){
            //                 painter.setPen(pero);
            //                 painter.drawEllipse(QPoint(xp, yp),2,2);
            //             }
            //             else if(dist > 40){
            //                 painter.setPen(yellow_pen);
            //                 painter.drawEllipse(QPoint(xp, yp),2,2);
            //             }
            //             else if(dist > 20){
            //                 painter.setPen(red_pen);
            //                 painter.drawEllipse(QPoint(xp, yp),2,2);
            //             }
            //             else{
            //                 painter.setPen(red_pen);
            //                 painter.drawEllipse(QPoint(xp, yp),2,2);
            //             }


            //         }


            //     }


            // }

        // else
        // {
        //     // this->setStyleSheet("background-color: rgb(105, 105, 105)");
        //     if(main_window->updateLaserPicture==1) ///ak mam nove data z lidaru
        //     {
        //         main_window->updateLaserPicture=0;

        //         //painter.setPen(pero);
        //         //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
        //         //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
        //         for(int k=0;k<main_window->copyOfLaserData.numberOfScans/*360*/;k++)
        //         {
        //             int dist=main_window->copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
        //             int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky
        //             int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky
        //             double uhol = 360.0-main_window->copyOfLaserData.Data[k].scanAngle;

        //             if(rect.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
        //             {
        //                 if(dist > 60){
        //                     painter.setPen(pero);
        //                     painter.drawEllipse(QPoint(xp, yp),2,2);
        //                 }
        //                 else if(dist > 40){
        //                     painter.setPen(yellow_pen);
        //                     painter.drawEllipse(QPoint(xp, yp),2,2);
        //                 }
        //                 else if(dist > 20){
        //                     painter.setPen(red_pen);
        //                     painter.drawEllipse(QPoint(xp, yp),2,2);
        //                 }
        //                 else{
        //                     painter.setPen(red_pen);
        //                     painter.drawEllipse(QPoint(xp, yp),2,2);
        //                 }


        //             }
        //             int xs=rect.width()-(rect.width()/2+2*sin((360.0)*3.14159/180.0))+rect.topLeft().x();
        //             int ys=rect.height()-(rect.height()/2+2*cos((360.0)*3.14159/180.0))+rect.topLeft().y();
        //             painter.drawEllipse(QPoint(xs, ys),20,20);
        //             painter.drawEllipse(QPoint(xs, ys-12),4,4);


        //         }


        //     }
        // }
        if(main_window->backup_assistant==true){
            //main_window->updateLaserPicture=0;
            // QPainter painter(this);
            // painter.setBrush(Qt::black); // Set the brush color

            // // Define the rectangle for the frame
            // QRect rect = this->geometry().adjusted(5, 10, -5, -10);
            // painter.drawRect(rect);

            // Calculate the size of the backup assistant rectangle (one-third of the width and height of the frame)
            int assistantWidth = rect.width() / 2;
            int assistantHeight = rect.height() / 2;

            // Calculate the position of the backup assistant rectangle at the top in the middle of the frame
            int assistantX = rect.center().x() - assistantWidth / 2;
            int assistantY = rect.top()+50 - assistantHeight /2;

            // Define the backup assistant rectangle
            QRect assistantRect(assistantX, assistantY, assistantWidth, assistantHeight);

            // Draw the backup assistant rectangle
            QPainter painter(this);
            painter.fillRect(assistantRect, Qt::black); // Fill the rectangle with blue color

            // Loop through the laser data and draw backup assistant points within the rectangle
            for (int k = 0; k < main_window->copyOfLaserData.numberOfScans; k++) {
                int dist = main_window->copyOfLaserData.Data[k].scanDistance / 20; // Distance divided by 20 (adjust as needed)
                double angle = 360.0 - main_window->copyOfLaserData.Data[k].scanAngle;
                int xp = rect.width() - (rect.width() / 2 + dist * 2 * sin(angle * M_PI / 180.0)) + rect.topLeft().x();
                int yp = rect.height() - (rect.height() / 2 + dist * 2 * cos(angle * M_PI / 180.0)) + rect.topLeft().y();

                // // Rescale the coordinates to fit within the backup assistant rectangle
                // int assistantXp = assistantRect.x() + (xp - rect.x()) * assistantRect.width() / rect.width();
                // int assistantYp = assistantRect.y() + (yp - rect.y()) * assistantRect.height() / rect.height();

                // Calculate the position of the point relative to the center of the frame
                // int relativeX = xp - rect.center().x();
                // int relativeY = yp - rect.center().y();

                // // Calculate the position of the rescaled point relative to the center of the backup assistant rectangle
                // int assistantXp = assistantRect.center().x() + relativeX * assistantRect.width() / (2 * rect.width());
                // int assistantYp = assistantRect.center().y() + relativeY * assistantRect.height() / (2 * rect.height());

                // Rescale the coordinates to fit within the assistant frame
                int assistantXp = assistantRect.x() + (xp - rect.x()) * assistantRect.width() / rect.width();
                int assistantYp = assistantRect.y() + (yp - rect.y()) * assistantRect.height() / rect.height();

                // Draw the rescaled backup assistant point
                if (assistantRect.contains(assistantXp, assistantYp)) {
                    if(dist > 60){
                        painter.setPen(pero);
                        painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
                    }
                    else if(dist > 40){
                        painter.setPen(yellow_pen);
                        painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
                    }
                    else if(dist > 20){
                        painter.setPen(red_pen);
                        painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
                    }
                    else{
                        painter.setPen(red_pen);
                        painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
                    }
                }
                int xs=assistantRect.width()-(assistantRect.width()/2+2*sin((360.0)*3.14159/180.0))+assistantRect.topLeft().x();
                int ys=assistantRect.height()-(assistantRect.height()/2+2*cos((360.0)*3.14159/180.0))+assistantRect.topLeft().y();
                painter.drawEllipse(QPoint(xs, ys),8,8);
                painter.drawEllipse(QPoint(xs, ys-3),1,1);

            }
        }

}


