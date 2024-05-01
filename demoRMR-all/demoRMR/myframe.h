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
    void loadMap(const QString &filename);
    void MyFrame::readPointsFromFile(const QString &filename);
    void drawRobot(QPainter &painter);
    QPointF scaleAndTranslatePoint(const QPointF &point);

private:
    MainWindow *main_window;
    bool map_loaded;
    QPixmap first_warning;
    QPixmap second_warning;
    QPixmap third_warning;
    double robotX_draw;
    double robotY_draw;
    double robotFi_draw;
    QList<QPolygonF> mapPolygons;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYFRAME_H
