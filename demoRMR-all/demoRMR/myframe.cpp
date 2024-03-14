// MyFrame.cpp
#include "myframe.h"
#include <QPainter>
#include "mainwindow.h"

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
    //pen pre warningy
    QPen warning;
    pero.setStyle(Qt::SolidLine);//styl pera - plna ciara
    //pero.setWidth(3);//hrubka pera -3pixely
    pero.setColor(Qt::red);//farba je zelena

    //rectangle pre frame vykreslovania v MainWindow
    QRect rect;
    rect= this->geometry();//ziskate porametre stvorca,do ktoreho chcete kreslit
    rect.translate(5,10);
    painter.drawRect(rect);

    //rectangles pre jednotlive varovania
    QRect topRect;
    topRect.setX(rect.x());
    topRect.setY(rect.y());
    topRect.setWidth(rect.width());
    topRect.setHeight(rect.height()/20);
    QRect bottomRect;
    bottomRect.setX(rect.x());
    bottomRect.setY(rect.y());
    bottomRect.setWidth(rect.width());
    bottomRect.setHeight(rect.height()/20);
    QRect leftRect;
    leftRect.setX(rect.x());
    leftRect.setY(rect.y());
    leftRect.setWidth(rect.width()/20);
    leftRect.setHeight(rect.height());
    QRect rightRect;
    rightRect.setX(rect.x());
    rightRect.setY(rect.y());
    rightRect.setWidth(rect.width()/20);
    rightRect.setHeight(rect.height());


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

                    painter.setPen(pero);
                    //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
                    //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
                    for(int k=0;k<main_window->copyOfLaserData.numberOfScans/*360*/;k++)
                    {
                        int dist=main_window->copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                        int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky
                        int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky
                        if(rect.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                            painter.drawEllipse(QPoint(xp, yp),2,2);
                    }
                }
            }


            for(int k=0; k < main_window->copyOfLaserData.numberOfScans/*360*/;k++)
            {


                int dist=main_window->copyOfLaserData.Data[k].scanDistance/20;
                double uhol = 360.0-main_window->copyOfLaserData.Data[k].scanAngle;

                // 25 305
                if(uhol < 45 || uhol >315 ){

                    double bx = dist*cos(uhol*3.14159/180.0);
                    double by = dist*sin(uhol*3.14159/180.0);

                    int x = rect.width()/2  - ( (681.743*by) / (bx-14.5) );
                    int y = rect.height()/2 + ( (681.743*(-21+11.5)) / (bx-14.5)  )/10;
                    //painter.drawEllipse(QPoint(x, y),2,2);

                    if(rect.contains(x,y))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    {
                        if(dist <= 40){
                            painter.setPen(pencil);

                        }
                        else if(dist >40 && dist < 60){
                            // painter.setPen(sharpie);
                            // QRect rectWarning(x, y, 20, 20);
                            // painter.drawRect(rectWarning);
                            painter.drawImage(QRect(x,y,35,35),warning);
                        }

                    }

                    //lavy
                }
                else if(uhol >45 && uhol < 145){
                    if(dist < 20){
                        main_window->pushButton_12->setStyleSheet("background-color:red");
                    }
                    else if(dist >20 && dist < 40){
                        main_window->pushButton_12->setStyleSheet("background-color:orange");
                    }
                    else{
                        main_window->pushButton_12->setStyleSheet("background-color:white");

                    }

                }
                //stred
                else if(uhol >145 && uhol < 215){
                    if(dist < 20){
                        main_window->->pushButton_7->setStyleSheet("background-color:red");
                    }
                    else if(dist >20 && dist < 40){
                        main_window->pushButton_7->setStyleSheet("background-color:orange");
                    }
                    else{
                        main_window->pushButton_7->setStyleSheet("background-color:white");

                    }

                }
                //pravy
                else if(uhol >215 && uhol < 315){
                    if(dist < 20){
                        main_window->pushButton_11->setStyleSheet("background-color:red");
                    }
                    else if(dist >20 && dist < 40){
                        main_window->pushButton_11->setStyleSheet("background-color:orange");
                    }
                    else{
                        main_window->pushButton_11->setStyleSheet("background-color:white");

                    }

                }



            }

        }
        else
        {
            // this->setStyleSheet("background-color: rgb(105, 105, 105)");
            if(main_window->updateLaserPicture==1) ///ak mam nove data z lidaru
            {
                main_window->updateLaserPicture=0;

                //painter.setPen(pero);
                //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
                //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
                for(int k=0;k<main_window->copyOfLaserData.numberOfScans/*360*/;k++)
                {
                    int dist=main_window->copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                    int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky
                    int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-main_window->copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky
                    double uhol = 360.0-main_window->copyOfLaserData.Data[k].scanAngle;

                    if(rect.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    {

                        if(dist > 60){
                            painter.setPen(pero);
                            painter.drawEllipse(QPoint(xp, yp),2,2);
                        }
                        else if(dist > 40){
                            painter.setPen(sharpie);
                            painter.drawEllipse(QPoint(xp, yp),2,2);
                        }
                        else if(dist > 20){
                            painter.setPen(pencil);
                            painter.drawEllipse(QPoint(xp, yp),2,2);
                        }
                        else{
                            painter.setPen(pencil);
                            painter.drawEllipse(QPoint(xp, yp),2,2);
                        }


                    }


                }


            }
        }

    }
}
