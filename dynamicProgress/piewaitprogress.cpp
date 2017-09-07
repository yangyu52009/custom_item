#include "piewaitprogress.h"
#include <QTimer>
#include <QPainter>
#include <QtMath>
PieWaitProgress::PieWaitProgress(QWidget *parent) :
    QWidget(parent),
    m_frontColor ( Qt::black),
    m_backgroundColor ( Qt::white),
    m_clockwiseRotate ( true),
    m_rotateDelta ( 36),
    m_rotateAngle ( 0)
{
    this->m_timer = new QTimer;
    this->connect ( this->m_timer, &QTimer::timeout,
                    this, &PieWaitProgress::update);

}

void PieWaitProgress::setFrontColor(QColor &color)
{
    if ( color != this->m_frontColor) {
        this->m_frontColor = color;
        this->update ();
    }
}

void PieWaitProgress::setBackgroundColor(QColor &color)
{
    if ( color != this->m_backgroundColor) {
        this->m_backgroundColor = color;
        this->update ();
    }
}

void PieWaitProgress::setClockwiseRotate(bool clockwise)
{
    if ( clockwise != this->m_clockwiseRotate) {
        this->m_clockwiseRotate = clockwise;
        this->update ();
    }
}

void PieWaitProgress::setRotateDelta(int delta)
{
    if ( delta != this->m_rotateDelta) {
        this->m_rotateDelta = delta;
        this->update ();
    }
}

void PieWaitProgress::Start_Stop(bool nor, int msec)
{
    if ( nor)
        this->m_timer->start ( msec);
    else
        this->m_timer->stop ();
}

void PieWaitProgress::drawPiwWait(QPainter &painter)
{
    //根据100*100的大小进行画,在paintEvent中进行过缩放
    painter.save ();

    painter.setPen ( Qt::NoPen);
    painter.setBrush ( QBrush (this->m_backgroundColor));
    painter.drawEllipse ( -50,-50, 100, 100);
    painter.setBrush ( QBrush (this->m_frontColor));
    painter.drawPie ( -50, -50, 100, 100, 0 * 16, 60 * 16);

    painter.restore ();
}


void PieWaitProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter ( this);
    painter.setRenderHint ( QPainter::Antialiasing, true);
    painter.translate ( this->width () / 2, this->height () / 2);
    int side = qMin ( this->width (), this->height ());
    painter.scale ( side / 100.0, side / 100.0);

    painter.rotate ( this->m_rotateAngle);
    this->drawPiwWait ( painter);
    this->m_rotateAngle += this->m_clockwiseRotate? this->m_rotateDelta : -this->m_rotateDelta;
    this->m_rotateAngle %= 360;

}
