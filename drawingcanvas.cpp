#include "drawingcanvas.h"
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <iostream>

DrawingCanvas::DrawingCanvas(QWidget *parent) {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints() {
    m_points.clear();
    update(); // Trigger repaint to clear the canvas
}

void DrawingCanvas::paintLines() {
    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection() {
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    const int windowSize = 15;
    const int halfWindow = windowSize / 2;
    const int threshold = 20;

    QPixmap resultPixmap = pixmap;
    QPainter painter(&resultPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(128, 0, 128, 80)));

    int totalSegments = 0;

    // Scan window per area 10x10
    for (int x = halfWindow; x < image.width() - halfWindow; x += windowSize) {
        for (int y = halfWindow; y < image.height() - halfWindow; y += windowSize) {
            int nonWhite = 0;

            for (int i = -halfWindow; i < halfWindow; i++) {
                for (int j = -halfWindow; j < halfWindow; j++) {
                    if (image.pixel(x + i, y + j) != 0xffffffff)
                        nonWhite++;
                }
            }

            if (nonWhite > threshold) {
                painter.drawRect(x - halfWindow, y - halfWindow, windowSize, windowSize);
                totalSegments++;
            }
        }
    }

    painter.end();

    QLabel *preview = new QLabel;
    preview->setPixmap(resultPixmap);
    preview->setWindowTitle(QString("Segment Detection Result — %1 segments").arg(totalSegments));
    preview->resize(image.size());
    preview->show();

    std::cout << "Total segments detected: " << totalSegments << std::endl;
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::blue, 3);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    for (const QPoint &point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if (isPaintLinesClicked) {
        std::cout << "paint lines block is called" << std::endl;
        pen.setColor(Qt::red);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        for (int i = 0; i < m_points.size() - 1; i += 2) {
            painter.drawLine(m_points[i], m_points[i + 1]);
        }

        isPaintLinesClicked = false;
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
    update();
}
