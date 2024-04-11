#include <QApplication>
#include <QMainWindow>
#include <QPainter>

class MapDrawer : public QMainWindow {
public:
    MapDrawer(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Map Drawer");
        resize(800, 600);
    }

    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        drawMap(painter);
    }

private:
    void drawMap(QPainter &painter) {
        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);

        // Draw lines
        for (auto line : lines) {
            for (int i = 0; i < line.size() - 1; ++i) {
                painter.drawLine(scaleCoordinates(line[i]), scaleCoordinates(line[i + 1]));
            }
        }
    }

    QPointF scaleCoordinates(QPointF coord) {
        qreal scale = 12.0;
        qreal x = coord.x() * scale;
        qreal y = (521.0 - coord.y()) * scale; // Reversing y-axis since Qt's origin is top-left
        return QPointF(x, y);
    }

    QVector<QPointF> coordinates {
        QPointF(0, 0),
        QPointF(0, 468),
        QPointF(58, 468),
        QPointF(58, 521),
        QPointF(547, 521),
        QPointF(547, 487),
        QPointF(602, 487),
        QPointF(602, -105),
        QPointF(238, -105),
        QPointF(238, -160),
        QPointF(110, -160),
        QPointF(110, 0)
    };

    QVector<QVector<QPointF>> lines {
        {QPointF(110, -2.5), QPointF(262.5, -2.5), QPointF(262.5, 0), QPointF(110, 0)},
        {QPointF(262.5, -2.5), QPointF(262.5, 152.5), QPointF(265, 152.5), QPointF(265, -2.5)},
        {QPointF(265, 152.5), QPointF(265, 155), QPointF(110, 155), QPointF(110, 152.5)},
        {QPointF(110, 155), QPointF(110, 310), QPointF(112.5, 310), QPointF(112.5, 155)},
        {QPointF(602, 338), QPointF(392, 338), QPointF(392, 335.5), QPointF(602, 335.5)},
        {QPointF(392, 338), QPointF(392, 392), QPointF(394.5, 392), QPointF(394.5, 338)},
        {QPointF(447, 335.5), QPointF(449.5, 335.5), QPointF(449.5, 180.5), QPointF(447, 180.5)},
        {QPointF(449.5, 180.5), QPointF(449.5, 183), QPointF(504.5, 183), QPointF(504.5, 180.5)},
        {QPointF(397, -105), QPointF(397, 50), QPointF(397.5, 50), QPointF(397.5, -105)},
        {QPointF(268, 280.5), QPointF(268, 335.5), QPointF(265.5, 335.5), QPointF(265.5, 280.5)},
        {QPointF(268, 338), QPointF(268, 335.5), QPointF(213, 335.5), QPointF(213, 338)},
        {QPointF(213, 335.5), QPointF(213, 280.5), QPointF(215.5, 280.5), QPointF(215.5, 335.5)}
    };
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MapDrawer window;
    window.show();
    return app.exec();
}
