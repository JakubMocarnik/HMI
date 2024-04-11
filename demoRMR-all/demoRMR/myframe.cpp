// MyFrame.cpp
#include "myframe.h"
#include <QPainter>
#include "mainwindow.h"
#include <QtMath>

#define GREEN_DISTANCE 600
#define YELLOW_DISTANCE 400

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
    rect.translate(10,10);
    painter.drawRect(rect);


    first_warning.load(":/resources/img/transparent_warning");
    second_warning.load(":/resources/img/yellow_warning");
    third_warning.load(":/resources/img/red_warning");

    // Define rectangles for each side
    int rectThickness = (rect.height())/20;

    //Define polygons for each side
    QPolygon topPolygon;
    topPolygon << QPoint(rect.topLeft().x(), rect.topLeft().y())
               << QPoint(rect.topRight().x(), rect.topRight().y())
               << QPoint(rect.right() - rectThickness, rect.top() + rectThickness)
               << QPoint(rect.left() + rectThickness, rect.top() + rectThickness);

    QPolygon bottomPolygon;
    bottomPolygon << QPoint(rect.left() + rectThickness, rect.bottom() - rectThickness)
                  << QPoint(rect.right() - rectThickness, rect.bottom() - rectThickness)
                  << QPoint(rect.bottomRight().x(), rect.bottomRight().y())
                  << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y());

    QPolygon leftPolygon;
    leftPolygon << QPoint(rect.left() + rectThickness, rect.top() + rectThickness)
                << QPoint(rect.topLeft().x(), rect.topLeft().y())
                << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y())
                << QPoint(rect.left() + rectThickness, rect.bottom() - rectThickness);

    QPolygon rightPolygon;
    rightPolygon << QPoint(rect.right() - rectThickness, rect.top() + rectThickness)
                 << QPoint(rect.topRight().x(), rect.topRight().y())
                 << QPoint(rect.bottomRight().x(), rect.bottomRight().y())
                 << QPoint(rect.right() - rectThickness, rect.bottom() - rectThickness);

    QPolygonF perimeterPolygon;
    perimeterPolygon << QPointF(0, 0) << QPointF(0, 468) << QPointF(58, 468)
                     << QPointF(58, 521) << QPointF(547, 521) << QPointF(547, 487)
                     << QPointF(602, 487) << QPointF(602, -105) << QPointF(238, -105)
                     << QPointF(238, -160) << QPointF(110, -160) << QPointF(110, 0);

    QList<QList<QPointF>> pointsList;
    pointsList << QList<QPointF>{QPointF(110, -2.5), QPointF(262.5, -2.5), QPointF(262.5, 0), QPointF(110, 0)} // 1
               << QList<QPointF>{QPointF(262.5, -2.5), QPointF(262.5, 152.5), QPointF(265, 152.5), QPointF(265, -2.5)} // 2
               << QList<QPointF>{QPointF(265, 152.5), QPointF(265, 155), QPointF(110, 155), QPointF(110, 152.5)} // 3
               << QList<QPointF>{QPointF(110, 155), QPointF(110, 310), QPointF(112.5, 310), QPointF(112.5, 155)} // 4
               << QList<QPointF>{QPointF(602, 338), QPointF(392, 338), QPointF(392, 335.5), QPointF(602, 335.5)} // 5
               << QList<QPointF>{QPointF(392, 338), QPointF(392, 392), QPointF(394.5, 392), QPointF(394.5, 338)} // 6
               << QList<QPointF>{QPointF(447, 335.5), QPointF(449.5, 335.5), QPointF(449.5, 180.5), QPointF(447, 180.5)} // 7
               << QList<QPointF>{QPointF(449.5, 180.5), QPointF(449.5, 183), QPointF(504.5, 183), QPointF(504.5, 180.5)} // 8
               << QList<QPointF>{QPointF(397, -105), QPointF(397, 50), QPointF(397.5, 50), QPointF(397.5, -105)} // 9
               << QList<QPointF>{QPointF(268, 280.5), QPointF(268, 335.5), QPointF(265.5, 335.5), QPointF(265.5, 280.5)} // 10
               << QList<QPointF>{QPointF(268, 338), QPointF(268, 335.5), QPointF(213, 335.5), QPointF(213, 338)} // 11
               << QList<QPointF>{QPointF(213, 335.5), QPointF(213, 280.5), QPointF(215.5, 280.5), QPointF(215.5, 335.5)}; // 12



    if (main_window->connected){
        if(main_window->useCamera1==true && main_window->actIndex>-1)/// ak zobrazujem data z kamery a aspon niektory frame vo vectore je naplneny
        {
            QImage image = QImage((uchar*)main_window->frame[main_window->actIndex].data, main_window->frame[main_window->actIndex].cols, main_window->frame[main_window->actIndex].rows, main_window->frame[main_window->actIndex].step, QImage::Format_RGB888  );//kopirovanie cvmat do qimage
            painter.drawImage(rect,image.rgbSwapped());
            update();

            if(main_window->useCamera1==true && main_window->actIndex>-1)
            {
                if(main_window->updateLaserPicture==1) ///ak mam nove data z lidaru
                {
                    main_window->updateLaserPicture=0;
                }

                QPainter painter(this);

                // Set the background color to black for the entire widget
                painter.fillRect(this->rect(), Qt::black);

                // Define the map points
                QVector<QPolygonF> mapPolygons;

                // Mirror the perimeter polygon around the x-axis
                for (int i = 0; i < perimeterPolygon.size(); ++i) {
                    QPointF mirroredPoint(perimeterPolygon[i].x(), -perimeterPolygon[i].y());
                    perimeterPolygon[i] = mirroredPoint;
                }

                // Calculate the scaling factors for the perimeter to fit into the geometry of the widget
                qreal scaleXPerimeter = static_cast<qreal>(this->width()) / 602.0; // 602 is the maximum x-coordinate in the perimeter
                qreal scaleYPerimeter = static_cast<qreal>(this->height()) / 681.0; // 681 is the maximum y-coordinate in the perimeter

                // Apply scaling to the perimeter points
                for (int i = 0; i < perimeterPolygon.size(); ++i) {
                    QPointF scaledPoint(perimeterPolygon[i].x() * scaleXPerimeter, perimeterPolygon[i].y() * scaleYPerimeter);
                    perimeterPolygon[i] = scaledPoint;
                }

                mapPolygons.append(perimeterPolygon);

                // Add other polygons
                // ...

                // Calculate the scaling factors to fit the map into the geometry of the widget
                qreal scaleX = static_cast<qreal>(this->width()) / 602.0; // 602 is the maximum x-coordinate in the map
                qreal scaleY = static_cast<qreal>(this->height()) / 681.0; // 681 is the maximum y-coordinate in the map

                foreach (const QList<QPointF> &points, pointsList) {
                    QPolygonF polygon;
                    for (const QPointF &point : points) {
                        // Scale the points to fit into the geometry of the widget
                        QPointF scaledPoint(point.x() * scaleX, point.y() * scaleY);
                        // Mirror the points around the x-axis
                        scaledPoint.setY(-scaledPoint.y());
                        polygon << scaledPoint;
                    }
                    mapPolygons.append(polygon);
                }

                // Calculate the bounding box of the map
                QRectF boundingRect;
                for (const QPolygonF &polygon : mapPolygons) {
                    boundingRect = boundingRect.united(polygon.boundingRect());
                }

                // Calculate the translation values to center the map within the rectangle
                qreal translateX = (this->width() - boundingRect.width()) / 2 - boundingRect.left();
                qreal translateY = (this->height() - boundingRect.height()) / 2 - boundingRect.top();

                // Translate all polygons by the calculated translation values
                for (QPolygonF &polygon : mapPolygons) {
                    for (QPointF &point : polygon) {
                        point += QPointF(translateX, translateY);
                    }
                }

                // Draw the map polygons and connect points with green lines
                painter.setPen(QPen(Qt::green, 10)); // Set the pen for drawing lines
                foreach (const QPolygonF &polygon, mapPolygons) {
                    painter.drawPolygon(polygon);

                    // Draw lines connecting the points of the polygon
                    for (int i = 0; i < polygon.size(); ++i) {
                        painter.drawLine(polygon[i], polygon[(i + 1) % polygon.size()]);
                    }
                }


                // Draw a circle with a line pointing to the right
                QPointF centerPoint(50, 50); // Coordinates on the unaltered map
                QPointF scaledCenterPoint(centerPoint.x() * scaleX, centerPoint.y() * scaleY);
                scaledCenterPoint.setY(-scaledCenterPoint.y()); // Mirror around the x-axis
                scaledCenterPoint += QPointF(translateX, translateY); // Translate

                painter.setPen(QPen(Qt::red, 3));
                painter.drawEllipse(scaledCenterPoint, 25, 25); // Draw a circle with a diameter of 50
                painter.drawLine(scaledCenterPoint, scaledCenterPoint + QPointF(25, 0)); // Draw a line to the right
            }

        //     if(main_window->useCamera1==true && main_window->actIndex>-1)
        //     {
        //         if(main_window->updateLaserPicture==1) ///ak mam nove data z lidaru
        //         {
        //             main_window->updateLaserPicture=0;
        //         }


        //     double minUpDistance = 100000;
        //     double minDownDistance = 100000;
        //     double minLeftDistance = 100000;
        //     double minRightDistance = 100000;
        //     int obstacleLeftX = 0;
        //     int obstacleLeftY = 0;
        //     int obstacleForwardX = 0;
        //     int obstacleForwardY = 0;
        //     int obstacleRightX = 0;
        //     int obstacleRightY = 0;

        //     for(int k=0; k < main_window->copyOfLaserData.numberOfScans/*360*/;k++){
        //             double dist = main_window->copyOfLaserData.Data[k].scanDistance;
        //             double uhol = 360.0-main_window->copyOfLaserData.Data[k].scanAngle;


        //             double bx = dist*cos(-uhol*3.14159/180.0);
        //             double by = dist*sin(-uhol*3.14159/180.0);

        //             int x = rect.width() / 2 - (681.743 * by) / (bx - 14.5);
        //             int y = rect.height() / 2 + ((681.743 * (-21 + 11.5)) / (bx - 14.5)) / 10;

        //             // Calculate the position of the obstacle relative to the frame's top-left corner
        //             x -= image.width() / 2; // Adjust for the image width
        //             y -= image.height() / 2; // Adjust for the image height


        //             if (dist!=0.0){
        //                 if(uhol < 45 || uhol > 315 ){
        //                     //top
        //                     if(dist < minUpDistance){
        //                         minUpDistance = dist;
        //                         obstacleForwardX = x;
        //                         obstacleForwardY = y;
        //                     }
        //                 }
        //                 if(uhol <= 135 && uhol >= 45){
        //                     //left
        //                     if(dist < minLeftDistance){
        //                         minLeftDistance = dist;
        //                         // obstacleLeftX = x;
        //                         // obstacleLeftY = y;
        //                     }
        //                 }
        //                 if(uhol < 225 && uhol > 135){
        //                     //bottom
        //                     if(dist < minDownDistance){
        //                         minDownDistance = dist;
        //                     }
        //                 }
        //                 if(uhol <= 315 && uhol >= 225){
        //                     //right
        //                     if(dist < minRightDistance){
        //                         minRightDistance = dist;
        //                         // obstacleRightX = x;
        //                         // obstacleRightY = y;
        //                     }
        //                 }
        //             }
        //         }

        //         //top

        //     if(minUpDistance < YELLOW_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::red);
        //         painter.drawPolygon(topPolygon);
        //         if(rect.contains(QPoint(obstacleForwardX,obstacleForwardY))){
        //             painter.drawPixmap(QRect(obstacleForwardX,obstacleForwardY,240,240),third_warning);
        //             update();
        //         }
        //     }
        //     else if(minUpDistance < GREEN_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::yellow);
        //         painter.drawPolygon(topPolygon);
        //         if(rect.contains(QPoint(obstacleForwardX,obstacleForwardY))){
        //             painter.drawPixmap(QRect(obstacleForwardX,obstacleForwardY,240,240),second_warning);
        //             update();
        //         }
        //     }
        //     else{
        //         QPainter painter(this);
        //         painter.setBrush(Qt::green);
        //         painter.drawPolygon(topPolygon);
        //         if(rect.contains(QPoint(obstacleForwardX,obstacleForwardY))){
        //             painter.drawPixmap(QRect(obstacleForwardX,obstacleForwardY,240,240),first_warning);
        //             update();
        //         }
        //     }

        //     //left

        //     if(minLeftDistance < YELLOW_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::red);
        //         painter.drawPolygon(leftPolygon);
        //         // if(rect.contains(QPoint(obstacleLeftX,obstacleLeftY))){
        //         //     painter.drawPixmap(QRect(obstacleLeftX,obstacleLeftY,240,240),third_warning);
        //         //     update();
        //         // }
        //     }
        //     else if(minLeftDistance < GREEN_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::yellow);
        //         painter.drawPolygon(leftPolygon);
        //         // if(rect.contains(QPoint(obstacleLeftX,obstacleLeftY))){
        //         //     painter.drawPixmap(QRect(obstacleLeftX,obstacleLeftY,240,240),second_warning);
        //         //     update();
        //         // }
        //     }
        //     else{
        //         QPainter painter(this);
        //         painter.setBrush(Qt::green);
        //         painter.drawPolygon(leftPolygon);
        //         // if(rect.contains(QPoint(obstacleLeftX,obstacleLeftY))){
        //         //     painter.drawPixmap(QRect(obstacleLeftX,obstacleLeftY,240,240),first_warning);
        //         //     update();
        //         // }
        //     }

        //     //bottom

        //     if(minDownDistance < YELLOW_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::red);
        //         painter.drawPolygon(bottomPolygon);
        //     }
        //     else if(minDownDistance < GREEN_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::yellow);
        //         painter.drawPolygon(bottomPolygon);
        //     }
        //     else{
        //         QPainter painter(this);
        //         painter.setBrush(Qt::green);
        //         painter.drawPolygon(bottomPolygon);
        //     }

        //     //right

        //     if(minRightDistance < YELLOW_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::red);
        //         painter.drawPolygon(rightPolygon);
        //         // if(rect.contains(QPoint(obstacleRightX,obstacleRightY))){
        //         //     painter.drawPixmap(QRect(obstacleRightX,obstacleRightY,240,240),third_warning);
        //         //     update();
        //         // }
        //     }
        //     else if(minRightDistance < GREEN_DISTANCE){
        //         QPainter painter(this);
        //         painter.setBrush(Qt::yellow);
        //         painter.drawPolygon(rightPolygon);
        //         // if(rect.contains(QPoint(obstacleRightX,obstacleRightY))){
        //         //     painter.drawPixmap(QRect(obstacleRightX,obstacleRightY,240,240),second_warning);
        //         //     update();
        //         // }
        //     }
        //     else{
        //         QPainter painter(this);
        //         painter.setBrush(Qt::green);
        //         painter.drawPolygon(rightPolygon);
        //         // if(rect.contains(QPoint(obstacleRightX,obstacleRightY))){
        //         //     painter.drawPixmap(QRect(obstacleRightX,obstacleRightY,240,240),first_warning);
        //         //     update();
        //         // }
        //     }

        //     if(main_window->backup_assistant==true){

        //         // Calculate the size of the backup assistant rectangle (one-third of the width and height of the frame)
        //         int assistantWidth = rect.width() / 3;
        //         int assistantHeight = rect.height() / 3;

        //         // Calculate the position of the backup assistant rectangle at the top in the middle of the frame
        //         int assistantX = rect.center().x() - assistantWidth / 2;
        //         int assistantY = rect.top();

        //         // Define the backup assistant rectangle
        //         QRect assistantRect(assistantX, assistantY, assistantWidth, assistantHeight);
        //         // assistantRect.translate(0, rect.top()+50);
        //         // Draw the backup assistant rectangle
        //         QPainter painter(this);
        //         painter.fillRect(assistantRect, Qt::black); // Fill the rectangle with blue color

        //         // Loop through the laser data and draw backup assistant points within the rectangle
        //         for (int k = 0; k < main_window->copyOfLaserData.numberOfScans; k++) {
        //             int dist = main_window->copyOfLaserData.Data[k].scanDistance; // Distance divided by 20 (adjust as needed)
        //             double angle = 360.0 - main_window->copyOfLaserData.Data[k].scanAngle;
        //             int xp = rect.width() - (rect.width() / 2 + dist/5 * 2 * sin(angle * M_PI / 180.0)) + rect.topLeft().x();
        //             int yp = rect.height() - (rect.height() / 2 + dist/5 * 2 * cos(angle * M_PI / 180.0)) + rect.topLeft().y();

        //             int assistantXp = assistantRect.x() + (xp - rect.x()) * assistantRect.width() / rect.width();
        //             int assistantYp = assistantRect.y() + (yp - rect.y()) * assistantRect.height() / rect.height();

        //             // Draw the rescaled backup assistant point
        //             if (assistantRect.contains(assistantXp, assistantYp)) {
        //                 if(dist > GREEN_DISTANCE){
        //                     painter.setPen(pero);
        //                     painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
        //                 }
        //                 else if(dist > YELLOW_DISTANCE){
        //                     painter.setPen(yellow_pen);
        //                     painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
        //                 }
        //                 else{
        //                     painter.setPen(red_pen);
        //                     painter.drawEllipse(QPoint(assistantXp, assistantYp),2,2);
        //                 }
        //             }
        //             int xs=assistantRect.width()-(assistantRect.width()/2+2*sin((360.0)*3.14159/180.0))+assistantRect.topLeft().x();
        //             int ys=assistantRect.height()-(assistantRect.height()/2+2*cos((360.0)*3.14159/180.0))+assistantRect.topLeft().y();
        //             painter.drawEllipse(QPoint(xs, ys),20,20);
        //             painter.drawEllipse(QPoint(xs, ys-12),4,4);

        //         }

        //     }

        // }
    }

}

}
