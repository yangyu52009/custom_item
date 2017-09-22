#include "slidenavigation.h"

#include <QTimer>
#include <QMap>
#include <QPair>
#include <QRectF>
#include <QMouseEvent>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
SlideNavigation::SlideNavigation(QWidget *parent) :
    QWidget(parent),
    m_barStartColor ( QColor ( 121, 121, 121)),
    m_barEndColor ( QColor ( 78, 78, 78)),
    m_itemStartColor ( QColor ( 46, 132, 243)),
    m_itemEndColor ( QColor ( 39, 110, 203)),
    m_itemTextColor ( Qt::white),
    m_itemLineColor ( QColor ( 255, 107, 107)),
    m_barRadious ( 0),
    m_itemRadious ( 0),
    m_space ( 25),
    m_itemLineWidth ( 3),
    m_itemLineStyle ( ItemLineStyle::None),
    m_orientation ( Qt::Horizontal),
    m_totalTextWidth ( 0),
    m_totalTextWidth ( 0)
{
    this->setAttribute ( Qt::WA_TranslucentBackground);

    this->m_slideTimer = new QTimer ( this);
    this->m_slideTimer->setInterval ( 10);
    connect ( this->m_slideTimer, &QTimer::timeout,
              this, &SlideNavigation::doSlide);
    this->m_shakeTimer = new QTimer ( this);
    this->m_shakeTimer->setInterval ( 10);
    connect ( this->m_shakeTimer, &QTimer::timeout,
              this, &SlideNavigation::doShake);

    this->setFocusPolicy ( Qt::ClickFocus);
}
void SlideNavigation::~SlideNavigation ()
{

}

void SlideNavigation::addItem (QString str)
{
    if ( str.isEmpty ())
        return;
    QMap< int, QPair < QString, QRectF> >::iterator it = this->m_itemList.begin ();
    //下面迭代判断 是否已经添加同名的item，同名就返回
    while  (it != this->m_itemList.end ())
    {
        QPair< QString ,QRectF >& itemData = it.value ();
        if ( str == itemData.first)
            return;
        ++it;
    }
    QFont f = this->font ();
    QFontMetrics fm ( f); //计算字符串占用的大小
    int textWidth = fm.width ( str); //字符串str使用字体f时候所占用的宽度
    int textHeight = fm.height (); // 高度
    int itemCount = this->m_itemList.size ();//已有的item的数量
    if ( itemCount > 0 ) {
        QPointF topLeft, bottomRight;

        if ( this->m_orientation == Qt::Horizontal ) //水平方向
        {
            topLeft = QPointF ( this->m_totalTextWidth, 0); //左上角坐标
            this->m_totalTextWidth += textWidth + this->m_space;
            bottomRight = QPointF ( this->m_totalTextWidth, this->m_totalTextHeight);
        }else //竖直方向
        {
            topLeft = QPointF ( 0, this->m_totalTextHeight);
            this->m_totalTextHeight += textHeight + this->m_space;
            bottomRight = QPointF ( this->m_totalTextWidth, this->m_totalTextHeight);
        }
        QRectF textRect ( topLeft, bottomRight); //str 所在item在widget上的绘制位置
        this->m_itemList.insert ( itemCount, qMakePair ( str, textRect ));
    }
    else //当前没有item, 添加第一个item
    {
        this->m_totalTextWidth = textWidth + this->m_space; //“星期一”
        this->m_totalTextHeight = textHeight + this->m_space;
        QPointF topLeft ( 0.0, 0.0 ); //( 0.0, 0.0)
        QPointF bottomRight ( this->m_totalTextWidth,this->m_totalTextHeight);//( 73.0, 43.0)
        QRectF textRect ( topLeft, bottomRight);
        this->m_itemList.insert ( itemCount, qMakePair ( str, textRect));

        this->m_currentItemIndex = 0;
        this->m_startRect = textRect;
        this->m_stopRect = textRect;
    }
    this->setMinimumSize ( this->m_totalTextWidth, m_totalTextHeight);
    this->resize ( this->m_totalTextWidth, this->m_totalTextHeight);
}

void SlideNavigation::setBarStartColor(const QColor &color)
{
    if ( color != this->m_barStartColor && color != nullptr) {
        this->m_barStartColor = color;
        this->update ();
    }
}

void SlideNavigation::setBarEndColor(const QColor &color)
{
    if ( color != this->m_barEndColor && color != nullptr) {
        this->m_barEndColor = color;
        this->update ();
    }
}

void SlideNavigation::setItemStartColor(const QColor &color)
{
    if ( color != this->m_itemStartColor && color != nullptr) {
        this->m_itemStartColor = color;
        this->update ();
    }
}

void SlideNavigation::setItemEndColor(const QColor &color)
{
    if ( color != this->m_itemEndColor && color != nullptr) {
        this->m_itemEndColor = color;
        this->update ();

    }
}

void SlideNavigation::setItemTextColor(const QColor &color)
{
    if ( color != this->m_itemTextColor && color != nullptr) {
        this->m_itemTextColor = color;
        this->update ();
    }
}

void SlideNavigation::setItemLineColor(const QColor &color)
{
    if ( color != this->m_itemLineColor && color != nullptr) {
        this->m_itemLineColor = color;
        this->update ();
    }
}

void SlideNavigation::setBarRadious (int radious)
{
    if ( radious >= 0 && radious != this->m_barRadious) {
        this->m_barRadious = radious;
        this->update ();
    }
}

void SlideNavigation::setSpace (int space)
{
    if ( space >= 0 && space != this->m_space) {
        this->m_space;
        this->update ();
    }
}

void SlideNavigation::setItemLineWidth (int width)
{
    if ( width >= 0 && width != this->m_itemLineWidth) {
        this->m_itemLineWidth = width;
        this->update ();
    }

}

void SlideNavigation::setItemStyle(SlideNavigation::ItemLineStyle style)
{
    if ( style >= 0 && style < 5 && style != this->m_itemLineStyle)
    {
        this->m_itemLineStyle = style;
        this->update ();
    }
}

void SlideNavigation::setOrientation (Qt::Orientation orientation)
{
    if ( orientation != this->m_orientation )
    {
        this->m_orientation = orientation;
        this->update ();
    }
}



void SlideNavigation::setEnableKeyMouse(bool enable)
{
    if ( enable != this->m_enableKeyMove) {
        this->m_enableKeyMove = enable;
    }
}


void SlideNavigation::moveFirst ()
{
    this->moveTo ( 0);
}
void SlideNavigation::moveLast ()
{
    this->moveTo ( this->m_itemList.size () - 1);
}
void SlideNavigation::movePrevious ()
{
    this->moveTo ( this->m_currentItemIndex - 1);
}
void SlideNavigation::moveNext ()
{
    this->moveTo ( this->m_currentItemIndex + 1);
}
/* 索引从 0 开始*/
void SlideNavigation::moveTo (int index)
{
    if ( index >= 0 &&
         index < this->m_itemList.size () &&
         index != this->m_currentItemIndex)
    {
        this->m_forward = index > this->m_currentItemIndex;
        this->m_currentItemIndex = index;
        this->m_stopRect = this->m_itemList[index].second;
        this->m_slideTimer->start ();
    }

    emit this->currentItemChanged ( index);
}
void SlideNavigation::moveTo (QString str)
{
    auto it = this->m_itemList.begin ();
    while ( it != this->m_itemList.end ()) {
        if ( str == it.value ().first )
        {
            int targetindex = it.key ();
            if ( targetindex == this->m_currentItemIndex )
                return ;
            this->moveTo ( targetindex);
            return ;
        }
        it ++;
    }
}
void SlideNavigation::moveTo (QPointF point)
{
    auto  it = this->m_itemList.begin ();
    for (; it != this->m_itemList.end (); ++it) {
        if ( it.value ().second.contains ( point)) {
            int targetindex = it.key ();
            if ( targetindex == this->m_currentItemIndex)
                return ;
            this->moveTo ( targetindex);
            return ;
        }
    }
}
void SlideNavigation::setItemRadious (int radious)
{
    if ( radious >= 0 && radious != this->m_itemRadious) {
        this->m_itemRadious = radious;
        this->update ();
    }
}
void SlideNavigation::mousePressEvent(QMouseEvent *event)
{
    //迭代 判断 鼠标位置在 哪个 item 之上
    QMap< int, QPair< QString, QRectF > >::iterator it = this->m_itemList.begin ();
    for (; it != this->m_itemList.end (); ++it) {
        if (it.value ().second.contains ( event->pos ()))
        {
            int targetIndex = it.key ();
            if ( targetIndex == this->m_currentItemIndex)
                return;

            this->m_forward = targetIndex > this->m_currentItemIndex; //是否从原来选中的item 到 当前为前进
            this->m_currentItemIndex = targetIndex; //设置点击的为当前选中的索引
            this->m_stopRect = it.value ().second;
            this->m_slideTimer->start (); //这个定时器循环调用槽函数 doSlide
            emit this->currentItemChanged ( targetIndex);
            break;
        }
    }
}
void SlideNavigation::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent ( event);
}
void SlideNavigation::doSlide ()
{
    /*
        使用定时器 延迟间隔的执行,移动startRect 矩形一段距离之后再重绘
    */
    if ( this->m_space <= 0)
        return ;

    qreal dx, dy;
    if ( this->m_orientation == Qt::Horizontal) {
        dx = this->m_space / 2.0;
        dy = 0;
    }else
    {
        dx = 0;
        dy = this->m_space / 2.0;
    }

    if ( this->m_forward) {

        this->m_startRect.adjust ( dx, dy, dx, dy);
        if ( ( m_orientation == Qt::Horizontal && m_startRect.topLeft ().x () >= m_stopRect.topLeft ().x ()) ||
             ( m_orientation == Qt::Vertical && m_startRect.topLeft ().y () >= m_stopRect.topLeft ().y ()) )
        {
            this->m_slideTimer->stop ();
            if ( this->m_startRect != this->m_stopRect) {
                this->m_shakeTimer->start ();
            }
        }
    }
    else
    {
        this->m_startRect.adjust ( -dx, -dy, -dx, -dy);
        if ( ( m_orientation == Qt::Horizontal && m_startRect.topLeft ().x () <= m_stopRect.topLeft ()) ||
             ( m_orientation == Qt::Vertical && m_startRect.topLeft ().y () <= m_stopRect.topLeft ().y ())) {
            this->m_slideTimer->stop ();
            if ( this->m_startRect != m_stopRect) {
                m_shakeTimer->start ();
            }
        }
    }
    this->update ();
}
void SlideNavigation::doShake ()
{
    qreal delta = 2.0;
    qreal dx1, dy1, dx2, dy2;
    dx1 = dy1 = dx2 = dy2 = 0.0;
    // startrect 可能其 左上角 不和 stoprect 重合，需要进行调整，
    //      x偏移 一般在水平方向移动产生
    if ( this->m_startRect.topLeft ().x () > this->m_stopRect.topLeft ().x ()) {
        dx1 = -delta;
    }
    else if ( this->m_startRect.topLeft ().x () < this->m_stopRect.topLeft ().x ()) {
        dx1 = delta;
    }
    //      y偏移 一般在垂直方向移动产生
    if ( this->m_startRect.topLeft ().y () > this->m_stopRect.topLeft ().y ()) {
        dy1 = -delta;
    }
    else if ( this->m_startRect.topLeft ().y () < this->m_stopRect.topLeft ().y ()) {
        dy1 = delta;
    }

    //startrect 可能其 右下角 不和 stoprect 重合，需要进行调整，
    //      x偏移 一般在水平方向移动产生
    if ( this->m_startRect.bottomRight ().x () < this->m_stopRect.bottomRight.x ()) {
        dx2 = -delta;
    }
    else if ( this->m_startRect.bottomRight ().x () > this->m_stopRect.bottomRight ().x ()){
        dx2 = delta;
    }
    //      y偏移 一般在垂直方向移动产生
    if ( this->m_startRect.bottomRight ().y () > this->m_stopRect.bottomRight ().y ()) {
        dy2 = -delta;
    }
    else if ( this->m_startRect.bottomRight ().y () < this->m_stopRect.bottomRight ().y () ) {
        dy2 = delta;
    }
    // 调整 startrect 位置。每次 以 delta 标准

    this->m_startRect.adjust ( dx1, dy1, dx2, dy2);
    //判断，多次的调整之后，任然无法完全重合，差的距离小于 delta 为标准（ 每次调整的量又不是 1）,直接设置为重合
    if ( qAbs ( this->m_startRect.topLeft ().x () - this->m_stopRect.x ()) <= delta)
        this->m_startRect.topLeft ().setX ( this->m_stopRect.topLeft ().x ());
    if ( qAbs ( this->m_startRect.topLeft ().y () - this->m_stopRect.topLeft ().y ()) <= delta)
        this->m_startRect.topLeft ().setY ( this->m_stopRect.topLeft ().y ());

    if ( qAbs ( this->m_startRect.bottomRight ().x () - this->m_stopRect.bottomRight ().x ()) <= delta)
        this->m_startRect.bottomRight ().setX ( this->m_stopRect.bottomRight ().x ());
    if ( qAbs ( this->m_startRect.bottomRight ().y () - this->m_stopRect.bottomRight ().y ()) <= delta)
        this->m_startRect.bottomRight ().setY ( this->m_stopRect.bottomRight ().y ());

    if ( this->m_startRect == this->m_stopRect)
        this->m_shakeTimer->stop ();

    this->update (); //每次进行调整之后重绘UI


}

void SlideNavigation::paintEvent(QPaintEvent *event)
{
    QPainter painter ( this);
    painter.setRenderHint ( QPainter::Antialiasing, true);

    this->drawBarBackground ( painter); //绘制导航条背景
    this->drawItemBackground ( painter); //绘制选中的item
    this->drawItemLine ( painter);
    this->drawText ( painter);
}
void SlideNavigation::drawBarBackground(QPainter &painter)
{
    painter.save ();
    painter.setPen ( Qt::NoPen);
    //使用线性渐变
    QLinearGradient linearGradient ( QPointF( 0, 0), QPointF ( 0, this->height ()) );
    linearGradient.setColorAt ( 0.0, this->m_barStartColor);
    linearGradient.setColorAt ( 1.0, this->m_barEndColor);

    painter.setBrush ( linearGradient);
    painter.drawRoundedRect ( this->rect (), this->m_barRadious, this->m_barRadious);

    painter.restore ();
}
void SlideNavigation::drawItemBackground (QPainter &painter)
{

    if (this->m_startRect.isNull ())
        return ;
    painter.save ();

    QLinearGradient linearGradient ( this->m_startRect.topLeft (), this->m_startRect.bottomRight ());
    linearGradient.setColorAt ( 0.0, this->m_itemStartColor);
    linearGradient.setColorAt ( 1.0, this->m_itemEndColor);
    painter.setPen ( Qt::NoPen);
    painter.setBrush ( linearGradient);
    painter.drawRoundedRect ( this->m_startRect, m_itemRadious, this->m_itemRadious);
    painter.restore ();
}
void SlideNavigation::drawItemLine (QPainter &painter)
{
    if ( this->m_startRect.isNull ())
        return ;
    QPointF p1, p2;
    switch ( this->m_itemLineStyle) {
    case None:
        return ;
        break;
    case ItemTop:
        p1 = this->m_startRect.topLeft ();
        p2 = this->m_startRect.topRight ();
        p2.setY ( p2.y () + this->m_itemLineWidth);
        break;
    case ItemRight:
        p1 = this->m_startRect.topRight ();
        p2 = this->m_startRect.bottomRight ();
        p2.setX ( p2.x () - this->m_itemLineWidth);
        break;
    case ItemBottom:
        p1 = this->m_startRect.bottomLeft ();
        p2 = this->m_startRect.bottomRight ();
        p1.setY ( p1.y () - this->m_itemLineWidth);
        break;
    case ItemLeft:
        p1 = this->m_startRect.topLeft ();
        p2 = this->m_startRect.bottomLeft ();
        p2.setX ( p2.x () + this->m_itemLineWidth);
        break;
    default:
        return;
        break;
    }
    painter.save ();

    QPen linepen;
    linepen.setColor ( this->m_itemLineColor);
    linepen.setWidth ( this->m_itemLineWidth);
    painter.setPen ( linepen);
    if ( this->m_itemLineStyle == ItemRect) {
        painter.drawRoundedRect ( QRectF ( p1, p2), this->m_itemRadious, this->m_itemRadious);
    }else
    {
        painter.drawLine ( p1, p2);
    }


    painter.restore ();
}

void SlideNavigation::drawText(QPainter &painter)
{
    painter.save ();

    painter.setPen ( this->m_itemTextColor);
    QMap< int, QPair < QString, QRectF> >::iterator it = this->m_itemList;

    while ( it != this->m_itemList.end ()) {
        QPair < QString, QRectF >& itemdata = it.value ();
        painter.drawText ( itemdata.second, Qt::AlignCenter, itemdata.first);
        it++;
    }

    painter.restore ();
}


void SlideNavigation::resizeEvent(QResizeEvent *event)
{
    this->adjustSize ();
}

/*
    重新的计算每一个 item 所在的矩形，这可能是因为widget的大小发生了变化
*/
void SlideNavigation::adjustItemSize()
{
    qreal addWidth, addHeight;
    //计算每一个item 需要变换的值
    //水平导航条
    if ( this->m_orientation == Qt::Horizontal ) {
        addWidth = 1.0 * ( this->width () - m_totalTextWidth ) / this->m_itemList.size ();
        addHeight = 1.0 * ( this->height () - m_totalTextHeight ) ; //只有1行
    }//垂直导航条
    else
    {
        addWidth = 1.0 * ( this->width () - this->m_totalTextWidth); //只有1列
        addHeight = 1.0 * ( this->height () - this->m_totalTextHeight) / this->m_itemList.size ();
    }
    //不手动的改变widget的大小addWidth， addHeight都是 0

    if ( !addWidth && !addHeight )
        return ;


    int itemCount = this->m_itemList.size ();
    qreal dx = 0;
    qreal dy = 0;
    QPointF topLeft, bottomRight;

    for (int i = 0; i < itemCount; ++i) {
        QPair <QString, QRectF>& itemData = this->m_itemList[i]; //给定key，返回value
        QFont f = this->font ();
        QFontMetrics fm ( f);
        int textWidth = fm.width ( itemData.first);
        int textHeight = fm.height ();

        if ( this->m_orientation == Qt::Horizontal ) {
            topLeft = QPointF ( dx, 0);
            dx += textWidth + this->m_space + addWidth;
            dy = textHeight + this->m_space + addHeight;
        }
        else
        {
            topLeft = QPointF ( 0, dx);
            dx = textWidth + this->m_space + addWidth;
            dy += textHeight + this->m_space + addHeight;
        }
        bottomRight = QPointF ( dx, dy);
        QRectF textRect ( topLeft, bottomRight);
        itemData.second = textRect;

        if ( i == this->m_currentItemIndex) {
            this->m_startRect = textRect;
            this->m_stopRect = textRect;
        }
    } //迭代所有的item，重新的设置每个item 所在 的rect


}

QList<QTimer *> SlideNavigation::getTimers() const
{
    QList<QTimer*> list;
    list.append ( this->m_slideTimer);
    list.append ( this->m_shakeTimer);

    return list;
}

QStringList SlideNavigation::getItems_Strs()
{
    QStringList list;
    auto it = this->m_itemList.begin ();
    while ( it != this->m_itemList.end ()) {
        list.append ( it.value ().first);
        it++;
    }
    return list;
}
int SlideNavigation::mapToIndex (const QString &str)
{
    auto it = this->m_itemList.begin ();
    while ( it != this->m_itemList.end ()) {
        if ( str == it.value ().first )
        {
            return it.key ();
        }
        it ++;
    }
}
int SlideNavigation::mapToItemStr (int index)
{
    auto it = this->m_itemList.begin ();
    while ( it != this->m_itemList.end ()) {
        if ( index == it.key ())
        {
            return it.value ().first;
        }
        it ++;
    }
}
