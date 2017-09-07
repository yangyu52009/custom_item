#ifndef ZOOMCIRCLEWAITPROGRESS_H
#define ZOOMCIRCLEWAITPROGRESS_H

#include <QWidget>

class ZoomCircleWaitProgress : public QWidget
{
    Q_OBJECT
public:
    explicit ZoomCircleWaitProgress(QWidget *parent = 0);

    void setColor (QColor& color); //设置前景色
    void setZoomOut (bool zoomOut); //是否缩小
    void setZoomDelta (int delta); // 缩放半径
    void setMinRadious (int value); //最小半径
    void setRadious (int value); //当前半径
signals:

public slots:
    void Start_Stop( bool nor, int msec);
protected:
    void drawZoomCircleWait (QPainter& painter);
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void fixRaidous (int maxRadius = 50); //绘制的圆的半径的最大值,由于以100*100为范围绘制,半径最大为50
private:
    QColor m_color; //前景色
    bool m_zoomOut; //是否缩小
    int m_zoomDelta; //缩放步进
    int m_radius; //当前半径
    int m_minRadious; //最小半径

    QTimer* m_timer;
};

#endif // ZOOMCIRCLEWAITPROGRESS_H
