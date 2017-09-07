#ifndef CIRCLEPROGRESS_H
#define CIRCLEPROGRESS_H

#include <QWidget>
#include <QPainter>
//圆形点状
class CircleProgress : public QWidget
{
    Q_OBJECT
public:
    explicit CircleProgress(QWidget *parent = 0);

    void setColor (QColor& color);
    void setClockwiseRotate (bool clockwise); //是否是顺时针旋转
    void setRotateDelta (int delta); //旋转步进角度
public slots:
    void Start_Stop (bool nor = true, int msec = 100);
protected:
    void drawCircleProgress (QPainter* painter);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QColor m_color; //绘制颜色
    bool m_clockwiseRotate; //顺时针旋转
    int m_rotateDelta; //旋转步进角度
    int m_rotateAngle; //初始旋转角度

    QTimer* m_timer;
};

#endif // CIRCLEPROGRESS_H
