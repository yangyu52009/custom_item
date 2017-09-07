#include "switchcontrol.h"

#include <QPainter>

#include <QMouseEvent>
#include <QRectF>

SwitchControl::SwitchControl(QWidget *parent)
    : QWidget(parent),
      m_nHeight(16),
      m_bChecked(false),
      m_radius(8.0),
      m_nMargin(3),
      m_checkedColor(0, 150, 136),
      m_thumbColor(Qt::white),
      m_disabledColor(190, 190, 190),
      m_background(Qt::black)
{
    this->setCursor( Qt::PointingHandCursor );
    // 鼠标滑过光标形状 - 手型

    this->connect( &m_timer, &QTimer::timeout,
                   this, &SwitchControl::onTimeout);
}

bool SwitchControl::isToggled() const
{
    return this->m_bChecked;
}

void SwitchControl::setTogggled(bool checked)
{
    this->m_bChecked = checked;
    this->m_timer.start (10);

}

void SwitchControl::setBackgroundColor(QColor color)
{
    this->m_background = color;
}

void SwitchControl::setCheckColor(QColor color)
{
    this->m_checkedColor = color;
}

void SwitchControl::setDisabledColor(QColor color)
{
    this->m_disabledColor = color;
}


QSize SwitchControl::sizeHint() const
{
    return minimumSizeHint();
}
//最小大小
QSize SwitchControl::minimumSizeHint() const
{
    return QSize(2 * (m_nHeight + m_nMargin), m_nHeight + 2 * m_nMargin );
}

//鼠标按下事件
void SwitchControl::mousePressEvent(QMouseEvent *event)
{
    if(this->isEnabled()) {
        if(event->button() & Qt::LeftButton){
            event->accept();
        }else{
            event->ignore();
        }
    }
}

// 鼠标释放事件 - 切换开关状态、发射toggled()信号
void SwitchControl::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->isEnabled()){
        if( event->type() == QMouseEvent::MouseButtonRelease &&
                (event->button() == Qt::LeftButton ))
        {
            event->accept();
            this->m_bChecked = !m_bChecked;
            emit this->toggled(m_bChecked);
            this->m_timer.start(10);
        }else{
            event->ignore();
        }
    }
}

// 绘制开关
void SwitchControl::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );
    QPainter painter(this);
    painter.setPen( Qt::NoPen );
    painter.setRenderHint( QPainter::Antialiasing );

    QPainterPath path;
    QColor background;
    QColor thumbColor;
    qreal dOpacity;

    if(this->isEnabled()){ //是否是可用的状态 , 可用状态

        if(this->m_bChecked) {//打开状态 , 打开状态
            background = this->m_background;
            thumbColor = this->m_checkedColor;
            dOpacity = 0.600;
        }
        else{
            background = m_background;
            thumbColor = this->m_disabledColor;
            dOpacity = 0.800;
            }
    }else{//不可用的状态
        background = this->m_background;
        thumbColor = this->m_disabledColor;
        dOpacity = 0.260;
    }

//    painter.setBrush (Qt::white);
//    painter.drawRect (QRectF(QPointF(0.0,0.0),this->sizeHint ()));
// //画出背景

    painter.setBrush( background );
    painter.setOpacity( dOpacity );
    path.addRoundedRect(QRectF(m_nMargin, m_nMargin,
                               width() - 2 * m_nMargin, height() - 2 * m_nMargin)
                        , m_radius, m_radius);
    painter.drawPath (path);
    //绘制圆角矩形

    painter.setBrush( thumbColor );
    painter.setOpacity( 1.0 );
    painter.drawEllipse(QRectF(m_nX - (m_nHeight / 2),
                               m_nY - (m_nHeight / 2),
                               height(), height()));
    //绘制小椭圆
}

//大小改变事件
void SwitchControl::resizeEvent(QResizeEvent *event)
{
    this->m_nX = this->m_nHeight / 2;
    this->m_nY = this->m_nHeight / 2;
    QWidget::resizeEvent(event);
}

//滑动时候触发
void SwitchControl::onTimeout()
{
    if(this->m_bChecked){
        this->m_nX += 1;
        if(m_nX >= width () - m_nHeight)
            m_timer.stop ();
    }else{
        m_nX -= 1;
        if(m_nX <= m_nHeight / 2)
            m_timer.stop ();
    }
    this->update ();
}
