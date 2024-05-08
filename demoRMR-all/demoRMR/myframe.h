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
    //get circles
    std::vector<cv::Vec3i> getCircles();
    //set circles
    void setCircles(std::vector<cv::Vec3i> circles);

private:
    MainWindow *main_window;
    std::vector<cv::Vec3i> circles;
    QPixmap first_warning;
    QPixmap second_warning;
    QPixmap third_warning;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYFRAME_H
