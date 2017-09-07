#include "taijiprogress.h"
#include <QPainter>
#include <QTimer>
TaiJiProgress::TaiJiProgress(QWidget *parent) :
    QWidget(parent),
    m_frontColor ( Qt::black),
    m_backgroundColor ( Qt::white),
    m_clockwiseRotate ( true),
    m_rotateAngle ( 0),  //旋转角度
    m_rotateDelta ( 36), //选装步进角度
    m_timer ( new QTimer)
{
    this->connect ( this->m_timer, &QTimer::timeout,
                    this, &TaiJiProgress::update);
}

void TaiJiProgress::setFrontColor(QColor color)
{
    if (color != this->m_frontColor) {
        this->m_frontColor = color;
        //this->update ();
    }
}

void TaiJiProgress::setBackgroundColor(QColor color)
{
    if (color != this->m_backgroundColor) {
        this->m_backgroundColor = color;
        //this->update ();
    }
}

void TaiJiProgress::setClockwiseRotate(bool clockwise)
{
    if (clockwise != this->m_clockwiseRotate) {
        this->m_clockwiseRotate = clockwise;
        //this->update ();
    }
}

void TaiJiProgress::setRotateDelta(int delta)
{
    if (delta != this->m_rotateDelta) {
        this->m_rotateDelta = delta;
        //this->update ();
    }
}

void TaiJiProgress::Start_Stop(bool nor)
{
    if (nor)
        this->m_timer->start ( 100);
    else
        this->m_timer->stop ();
}

void TaiJiProgress::drawTaiji(QPainter &painter)
{
    //按照100 * 100的大小进行画,在paintEvent进行缩放
    painter.save();
    painter.setPen( Qt::NoPen);
    painter.setBrush( QBrush( m_frontColor));
    painter.drawPie( -50, -50, 100, 100, 90*16, 180*16);
    painter.setBrush( QBrush( m_backgroundColor));
    painter.drawPie( -50, -50, 100, 100, 270*16, 180*16);
    painter.drawEllipse( -25, -50, 50, 50);
    painter.setBrush( QBrush( m_frontColor));
    painter.drawEllipse( -25, 0, 50, 50);
    painter.drawEllipse( -50/8 ,-50*5/8, 50/4, 50/4);
    painter.setBrush( QBrush( m_backColor));
    painter.drawEllipse( -50/8, 50*3/8, 50/4, 50/4);
    painter.restore();
    painter->restore ();
}

void TaiJiProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter( this);
    painter.setRenderHint ( QPainter::Antialiasing, true);
    //将坐标系的0点转换到当前的widget中心
    painter.translate ( this->width () / 2, this->height () / 2);
    int side = qMin ( this->width (), this->height ());
    painter.scale ( side/100.0, side/100.0);

    painter.rotate ( this->m_rotateAngle); //旋转坐标系
    this->drawTaiji ( &painter);
    this->m_rotateAngle += m_clockwiseRotate ? this->m_rotateDelta : -this->m_rotateDelta;
    this->m_rotateAngle %= 360;
}
