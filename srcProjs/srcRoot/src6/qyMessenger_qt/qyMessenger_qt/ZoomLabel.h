#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTransform>
#include <QApplication>
#include <QPixmap>
#include <QMutex>
#include <qdebug.h>
 
class ZoomLabel : public QWidget {
    Q_OBJECT
public:
    ZoomLabel(const QString& pixmapPath, QWidget* parent = nullptr) : QWidget(parent), pixmap(pixmapPath) {
        scaleFactor = 1.0; 

        setAttribute(Qt::WA_OpaquePaintEvent);
    }

    void setPixmap(const QString& pixmapPath) {

        if (!pixmapPath.isEmpty())
            tmpPixmap.load(pixmapPath);
        else
            tmpPixmap = QPixmap(); 
        
        mutex.lock();
        pixmap = tmpPixmap;
        mutex.unlock();

        this->update();

    }

protected:
#if 0
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        QWidget::paintEvent(event);
        
        QPen pen(Qt::black, 1);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        painter.drawRect(rect().adjusted(1, 1, -1, -1)); 
        //painter.drawRect(rect());

        painter.setRenderHint(QPainter::SmoothPixmapTransform); 
        painter.translate(offsetX, offsetY); 
        painter.scale(scaleFactor, scaleFactor);
        mutex.lock();
        painter.drawPixmap(0, 0, pixmap);
        mutex.unlock();

        
    }

#endif

    void paintEvent(QPaintEvent* event) override
    {
        qDebug() << "---------------paintEvent------------";

        QPixmap buffer(size());
        buffer.fill(Qt::black);

        QPainter bufferPainter(&buffer);
        drawContents(&bufferPainter);


        QPainter widgetPainter(this);
        widgetPainter.drawPixmap(0, 0, buffer);
    }

    void drawContents(QPainter* painter)
    {
        
        drawBorder(painter);

        painter->setRenderHint(QPainter::SmoothPixmapTransform);
        painter->translate(offsetX, offsetY);
        painter->scale(scaleFactor, scaleFactor);
        mutex.lock();
        painter->drawPixmap(0, 0, pixmap);
        mutex.unlock();

       
    }

    void drawBorder(QPainter* painter)
    {        
        QPen oldPen = painter->pen();

        QPen borderPen(Qt::black, 1);
        borderPen.setStyle(Qt::SolidLine);
        painter->setPen(borderPen);

        painter->drawRect(rect().adjusted(1, 1, -1, -1));

        painter->setPen(oldPen);       
    }

    void resizeEvent(QResizeEvent* event) override
    {
        QWidget::resizeEvent(event);
        update(); 
    }

    void mousePressEvent(QMouseEvent* event) override {
        lastPos = event->pos(); 

        qDebug() << "---------------mousePressEvent------------";
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) { 
            offsetX += event->pos().x() - lastPos.x(); 
            offsetY += event->pos().y() - lastPos.y();
            lastPos = event->pos();
            update();
            qDebug() << "---------------mouseMoveEvent------------";
        }
    }

    void wheelEvent(QWheelEvent* event) override { 
        int numDegrees = event->angleDelta().y() / 8; 
        double numSteps = numDegrees / 15.0;
        scaleFactor += numSteps * 0.1; 
        scaleFactor = qMax(0.1, scaleFactor); 
        update(); 
    }

private:
    QPixmap tmpPixmap;
    QPixmap pixmap;
    double scaleFactor; 
    QPoint lastPos; 
    int offsetX = 0;
    int offsetY = 0;

    QMutex mutex;

};