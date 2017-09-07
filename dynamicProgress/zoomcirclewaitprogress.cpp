#include "zoomcirclewaitprogress.h"
#include <QTimer>
#include <QtMath>
#include <QPainter>
ZoomCircleWaitProgress::ZoomCircleWaitProgress(QWidget *parent) :
    QWidget(parent),
    m_color ( Qt::black),
    m_zoomOut ( false),
    m_zoomDelta ( 5),
    m_radius ( 0),
    m_minRadious ( 0)
{
    this->m_timer = new QTimer;
    this->connect ( this->m_timer, &QTimer::timeout,
                    this, &ZoomCircleWaitProgress::update);
}

void ZoomCircleWaitProgress::setColor(QColor &color)
{
    if (color != this->m_color) {
        this->m_color = color;
        this->update ();
    }
}

void ZoomCircleWaitProgress::setZoomOut(bool zoomOut)
{
    if (zoomOut != this->m_zoomOut) {
        this->m_zoomOut = zoomOut;
        this->update ();
    }
}

void ZoomCircleWaitProgress::setZoomDelta(int delta)
{
    if (delta != this->m_zoomDelta) {
        this->m_zoomDelta = delta;
        this->update ();
    }
}

void ZoomCircleWaitProgress::setMinRadious(int value)
{
    if (value != this->m_zoomDelta) {
        this->m_minRadious = value;
        this->update ();
    }
}

void ZoomCircleWaitProgress::setRadious(int value)
{
    if (value != this->m_radius) {
        this->m_radius = value;
        this->update ();
    }
}

void ZoomCircleWaitProgress::Start_Stop(bool nor, int msec)
{
    if ( nor)
        this->m_timer->start ( msec);
    else
        this->m_timer->stop ();
}




void ZoomCircleWaitProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter ( this);
    painter.setRenderHint ( QPainter::Antialiasing ,true);
    painter.translate ( this->width () / 2, this->height () / 2);
    side = qMin (this->width (), this->height ());
    painter.scale ( side / 100.0, side / 100.0);

    this->m_radius += this->m_zoomDelta;
    this->fixRaidous ( 50);
}
void ZoomCircleWaitProgress::drawZoomCircleWait(QPainter &painter)
{
    painter.save ();

    painter.setPen ( Qt::NoPen);
    painter.setBrush ( QBrush ( this->m_color));
    painter.drawEllipse ( this->m_radius, this->m_radius,
                          2 * this->m_radius, 2 * this->m_radius);

    painter.restore ();
}
void ZoomCircleWaitProgress::fixRaidous(int maxRadius)
{
    if (this->m_radius < this->m_minRadious) {
        this->m_radius = this->m_minRadious;
        this->m_zoomDelta = qAbs ( this->m_zoomDelta);
    }else if (this->m_radius > max) {
        //半径开始减小
        if (this->m_zoomOut) {
            this->m_radius = max;
            this->m_zoomDelta = -qAbs (this->m_zoomDelta);
        }else {
            this->m_radius = m_minRadious;
            this->m_zoomDelta = qAbs ( this->m_zoomDelta);
        }
    }
}
