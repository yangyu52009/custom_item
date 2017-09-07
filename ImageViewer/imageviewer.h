#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H
#include <QWidget>

/*****************************************************
**Copyright(C), 2017-2025, zl software.
**Version: 1.0
**Author: yangyu
**Date: 20170831
**Description:
**      尝试开发一个通用的图片显示组件
*****************************************************/
//图片数量统计控件
class QPainter ;

class PageNum : public QWidget
{
    Q_OBJECT
public:
    explicit PageNum (QWidget* parent);
    ~PageNum () {}

    void setBackgroundColor (); //设置这个组件显示的时候的背景颜色
    void setTextColor (); //设置这个控件显示时候的文字颜色
public slots:
    void setMaxValue (); //设置统计图片的最大值
    int maxValue () const { return this->m_max; }

    void setValue ();
    int Value () const { return this->m_value; }

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual drawBackground (QPainter* painter);
    virtual drawText (QPainter* painter);
private:
    int m_value;
    int m_max;
    QColor m_backgroundColor;
    QColor m_textColor;

    QString strFormate;

};
//图片的显示显示组件
class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    enum ImageSizeType
    {
        OriginalSize = 0, //原始大小
        SuitableSize, //适合大小
        FillSize //填充大小
    }
    Q_ENUM (ImageSizeType)

    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer ();

    void loadImage (QString path);

signals:
    void imageNumberChanged (int number);
    void imageIndexChanged (int index);

public slots:
    void moveTo (int index);
    void moveToNext ();
    void moveToPrevious ();
    void moveToFirst ();
    void moveToLast ();
    void setSizeType (ImageSizeType type);
    void setFadeEnable (bool enable = true);
    void setKeyMoveEnable (bool enable);
    void clear ();
    void loadImages ();
public slots:
private:
    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;
    int m_pageBtnLeftMargin;
    int m_pageNumBottommMargin;
    QSize m_pageBtnSize;
    ImageSizeType m_sizetype;
    bool m_fadeEnable;

};

#endif // IMAGEVIEWER_H
