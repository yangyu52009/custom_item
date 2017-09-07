#ifndef PIEWAITPROGRESS_H
#define PIEWAITPROGRESS_H

#include <QWidget>

class PieWaitProgress : public QWidget
{
    Q_OBJECT
public:
    explicit PieWaitProgress(QWidget *parent = 0);

    void setFrontColor (QColor& color);
    void setBackgroundColor (QColor& color);
    void setClockwiseRotate (bool clockwise);
    void setRotateDelta (int delta);
signals:

public slots:
    void Start_Stop ( bool nor = true, int msec = 100);
protected:
    void drawPiwWait (QPainter& painter);
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QColor m_frontColor; //前景色
    QColor m_backgroundColor; //背景色
    bool m_clockwiseRotate; //顺时针旋转
    int m_rotateDelta; //旋转步进角度
    int m_rotateAngle; //旋转角度

    QTimer* m_timer;
};

#endif // PIEWAITPROGRESS_H
