// MyFrame.cpp
#include "myframe.h"
#include <QPainter>
#include "mainwindow.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QVector>
#include <QPolygonF>
#include <QRectF>
#define GREEN_DISTANCE 600
#define YELLOW_DISTANCE 400


MyFrame::MyFrame(QWidget *parent) : QFrame(parent) {
    // Additional setup if needed
    robotX_draw = 0;
    robotY_draw = 0;
    robotFi_draw = 0;
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

void MyFrame::readPointsFromFile(const QString &filename, QList<QPolygonF> &mapPolygons) {
        // Clear the existing map polygons list
        mapPolygons.clear();

        // Open the file
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file:" << filename;
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed(); // Trim leading and trailing whitespace

            // Remove comments indicated by double slashes
            int commentIndex = line.indexOf("//");
            if (commentIndex != -1) {
                line = line.left(commentIndex).trimmed(); // Remove comment and trim again
            }

            // Ignore empty lines
            if (line.isEmpty()) {
                continue;
            }

            // Split the line into parts
            QStringList parts = line.split(" ");

            // Extract points from the line
            QPolygonF polygon;
            for (int i = 1; i < parts.size(); ++i) {
                QString pointStr = parts[i];
                // Remove '[' and ']' characters
                pointStr.remove('[');
                pointStr.remove(']');

                // Extract x and y coordinates
                QStringList coordinates = pointStr.split(",");
                if (coordinates.size() != 2) {
                    qDebug() << "Invalid point format:" << parts[i];
                    polygon.clear(); // Clear the polygon
                    break; // Exit loop to discard this polygon
                }
                qreal x = coordinates[0].trimmed().toDouble();
                qreal y = coordinates[1].trimmed().toDouble();
                polygon << QPointF(x, y);
            }

            // Add the polygon to the map polygons list if it's valid
            if (!polygon.isEmpty()) {
                mapPolygons.append(polygon);
            }
        }

        file.close();
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
    rect = this->geometry();//ziskate porametre stvorca,do ktoreho chcete kreslit
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
                QList<QPolygonF> mapPolygons;

                // Read points from file and add polygons to the map
                readPointsFromFile(":/resources/priestor.txt", mapPolygons);

                // Define the maximum x and y coordinates of the map
                const qreal maxX = 602.0; // Maximum x-coordinate in the map
                const qreal maxY = 681.0; // Maximum y-coordinate in the map

                // Calculate the bounding box of the map
                QRectF boundingRect;
                for (const QPolygonF &polygon : mapPolygons) {
                    boundingRect = boundingRect.united(polygon.boundingRect());
                }

                // Calculate the scaling factors to fit the map into the geometry of the widget
                qreal scaleX = static_cast<qreal>(rect.width()) / maxX;
                qreal scaleY = static_cast<qreal>(rect.height()) / maxY;
                qreal scale = qMin(scaleX, scaleY);

                // Adjust scaling factors to maintain aspect ratio
                if (scaleX < scaleY) {
                    scaleY = scaleX;
                } else {
                    scaleX = scaleY;
                }

                // Calculate the translation values to center the map within the rectangle
                qreal translateX = (rect.width() - boundingRect.width() * scale) / 2 - boundingRect.left() * scale;
                qreal translateY = (rect.height() - boundingRect.height() * scale) / 2 - (boundingRect.top() - 360) * scale; // Adjust for the y-axis offset

                // Apply scaling and translation to polygons
                for (QPolygonF &polygon : mapPolygons) {
                    for (QPointF &point : polygon) {
                        // Invert the y-coordinate
                        point.setY(-point.y());

                        // Apply scaling
                        point.setX(point.x() * scaleX + translateX);
                        point.setY(point.y() * scaleY + translateY);
                    }
                }

                // Draw the map polygons
                painter.setPen(QPen(Qt::green, 3)); // Set the pen for drawing polygons
                foreach (const QPolygonF &polygon, mapPolygons) {
                    painter.drawPolygon(polygon);
                }

                robotX_draw = main_window->robotX.load(std::memory_order_relaxed);
                robotY_draw = main_window->robotY.load(std::memory_order_relaxed);

                // Draw the robot
                QPointF robotCenter(50, 50); // Initial position of the robot
                QPointF scaledRobotCenter(robotCenter.x() * scaleX, robotCenter.y() * scaleY); // Scale the robot position
                scaledRobotCenter.setY(-scaledRobotCenter.y()); // Mirror around the x-axis
                scaledRobotCenter += QPointF(translateX+robotX_draw*100.0, translateY-robotY_draw*100.0); // Translate the robot position

                std::cout << "robotX: " << main_window->robotX << " robotY: " << main_window->robotY << std::endl;
                std::cout << "scaledRobotCenter: " << scaledRobotCenter.x() << " " << scaledRobotCenter.y() << std::endl;

                // Draw the robot as a circle with a line pointing to the right
                painter.setPen(QPen(Qt::red, 3));
                painter.drawEllipse(scaledRobotCenter, 25, 25); // Draw a circle representing the robot
                //TODO: line aby sa kreslila podla uhlu
                double lineEndX = 25*cos(main_window->robotFi.load(std::memory_order_relaxed)*PI/180.0);
                double lineEndY = -25*sin(main_window->robotFi.load(std::memory_order_relaxed)*PI/180.0);
                QPointF lineEnd = scaledRobotCenter + QPointF(lineEndX, lineEndY);
                painter.drawLine(scaledRobotCenter, lineEnd); // Draw a line pointing to the right


            }

        }

    }
}

