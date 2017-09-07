#include "imageviewer.h"
#include <QPainter>
PageNum::PageNum (QWidget* parent):
    QWidget(parent),
    m_value (-1),
    m_max (0),
    m_backgroundColor ( QColor( Qt::transparent)),
    m_textColor ( QColor ( Qt::white))
{
    this->strFormate = QString ( tr ("第 %1 张 / 共 %2 张"));
    this->setMinimumWidth (150);
    this->setAutoFillBackground ( true);

}

void PageNum::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event)
    QPainter painter (this);
    painter.setRenderHint (QPainter::Antialiasing, true); //设置为反锯齿渲染
    this->drawBackground ( &painter);
    this->drawText ( &painter);

}
void PageNum::drawBackground (QPainter *painter)
{
    painter->sava ();

    painter->setPen (Qt::NoPen);
    painter->setBrush ( this->m_backgroundColor); //设置笔刷为  m_backgroundColor
    painter->drawRect ( this->rect ()); //画背景

    painter->restore ();
}
void PageNum::drawText (QPainter *painter)
{
    painter->sava ();

    QString text = this->strFormate.arg (this->Value ()+1).arg (this->m_max);
    QFont font = this->font ();
    font.setBold ( true);
    painter->setFont ( font);
    painter->drawText ( this->rect (), Qt::AlignCenter, text);

    painter->restore ();
}
/*class ImageViewer*/

ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),

{

}


