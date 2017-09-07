#include "linewaitprogress.h"
#include <QPainter>
#include <QTimer>
#include <QtMath>
LineWaitProgress::LineWaitProgress(QWidget *parent) :
    QWidget(parent),
    m_color ( Qt::black),
    m_clockwiseRotate ( true),
    m_rotateDelta ( 36),
    m_rotateAngle ( 0)
{
    this->m_timer = new QTimer;
    this->connect (this->m_timer, &QTimer::timeout,
                   this, this->update);
}

void LineWaitProgress::setColor(QColor &color)
{
    if ( color != this->m_color){
        this->m_color = color;
        this->update ();
    }
}

void LineWaitProgress::setClockwiseRotate(bool clockwise)
{
    if (clockwise != this->m_clockwiseRotate) {
        this->m_clockwiseRotate = clockwise;
        this->update ();
    }
}

void LineWaitProgress::setRotateDelta(int delta)
{
    if (delta != this->m_rotateDelta) {
        this->m_rotateDelta = delta;
        this->update ();
    }
}

void LineWaitProgress::Start_Stop(bool nor, int msec)
{
    if (nor)
        this->m_timer->start ( msec);
    else
        this->m_timer->stop ();
}

void LineWaitProgress::drawLineWait(QPainter &painter)
{
     //根据100*100的大小进行画,在paintEvent中进行过缩放
    painter.save ();

    QColor color = this->m_color;
    for (int i = 0; i <= 10; ++i)
    {
        color.setAlphaF ( 1.0*i / 10);
        painter.setBrush ( QBrush ( color));
        painter.drawRoundedRect ( 50*2/5, -3, 50*3/5, 6, 2, 2);
        painter.rotate ( 36);
    }

    painter.restore ();
}


void LineWaitProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter ( this);
    painter.setRenderHint ( QPainter::Antialiasing, true); //设置反锯齿
    painter.translate ( this->width () / 2, this->height () / 2); //将坐标轴的零点移动到widget的中心位置
    int side = qMin (this->width (), this->height ()); //取宽度 和 高度 两者的最小值
    painter.scale ( side / 100.0, side / 100.0); //缩放坐标系 到以100 * 100为标准

    painter.rotate ( this->m_rotateAngle);
    this->drawLineWait (painter);

    this->m_rotateAngle += this->m_clockwiseRotate ? this->m_rotateDelta : -this->m_rotateDelta;
    this->m_rotateAngle %= 360;

}
