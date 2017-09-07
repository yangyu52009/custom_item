#include "circleprogress.h"
#include <QTimer>
#include <QtMath>
CircleProgress::CircleProgress(QWidget *parent) :
    QWidget(parent),
    m_color ( Qt::black),
    m_clockwiseRotate ( true),
    m_rotateAngle ( 0),
    m_rotateDelta ( 36)
{
    this->m_timer = new QTimer;
    this->connect ( this->m_timer, &QTimer::timeout,
                    this, &CircleProgress::update);
}

void CircleProgress::setColor(QColor &color)
{
    if ( color != this->m_color)
        this->m_color = color;

}

void CircleProgress::setClockwiseRotate(bool clockwise)
{
    if ( clockwise != this->m_clockwiseRotate)
        this->m_clockwiseRotate = clockwise;
}

void CircleProgress::setRotateDelta(int delta)
{
    if ( delta != this->m_rotateDelta)
        this->m_rotateDelta = delta;
}

void CircleProgress::Start_Stop( bool nor, int msec)
{
    if (nor)
        this->m_timer->start (msec);
    else
        this->m_timer->stop ();
}



void CircleProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter ( this);
    painter.setRenderHint ( QPainter::Antialiasing, true);
    painter.translate ( this->width () / 2, this->height () / 2 );
    int side = qMin ( this->width (), this->height ());
    painter.scale ( side / 100.0, side / 100.0);

    painter.rotate ( this->m_rotateAngle);
    this->drawCircleProgress ( &painter);
    this->m_rotateAngle += this->m_clockwiseRotate ? this->m_rotateDelta : -this->m_rotateDelta;
    this->m_rotateAngle %= 360;
}

void CircleProgress::drawCircleProgress(QPainter *painter)
{
    // 根据 100* 100 的大小进行绘图
    painter->save ();

    painter->setPen ( Qt::NoPen);
    QColor color = this->m_color;
    for (int i = 0; i <= 10; ++i) {
        color.setAlphaF ( 1.0*i / 10); //设置透明度
        painter->setBrush ( QBrush ( color));
        painter->drawEllipse ( 30, -10, 20, 20);
        painter->rotate ( 36); //将坐标轴旋转36度,绘制10个不同透明度的圆形
    }


    painter->restore ();
}

