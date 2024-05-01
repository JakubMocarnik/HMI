#ifndef MYFRAME_H
#define MYFRAME_H
#include <QFrame>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

class MainWindow;

class MyFrame : public QFrame {
    Q_OBJECT
public:
    MyFrame(QWidget *parent = nullptr);
    ~MyFrame();    
    void setMainWindow(MainWindow *main_window);
    void printStuff();
    void MyFrame::readPointsFromFile(const QString &filename, QList<QPolygonF> &mapPolygons);
    void drawRobot(QPainter &painter);
    QPointF scaleAndTranslatePoint(const QPointF &point);

private:
    MainWindow *main_window;

    QPixmap first_warning;
    QPixmap second_warning;
    QPixmap third_warning;
    double robotX_draw;
    double robotY_draw;
    double robotFi_draw;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYFRAME_H
