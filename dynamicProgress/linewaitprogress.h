#ifndef LINEWAITPROGRESS_H
#define LINEWAITPROGRESS_H

#include <QWidget>

class LineWaitProgress : public QWidget
{
    Q_OBJECT
public:
    explicit LineWaitProgress(QWidget *parent = 0);

    void setColor (QColor& color);
    void setClockwiseRotate (bool clockwise); //是否是顺时针旋转
    void setRotateDelta (int delta); // 旋转步进角度

public slots:
    void Start_Stop ( bool nor = true, int msec = 100);
protected:
    void drawLineWait (QPainter& painter);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QColor m_color;
    bool m_clockwiseRotate; //顺时针旋转
    int m_rotateDelta; //旋转步进角度
    int m_rotateAngle; //旋转角度

    QTimer* m_timer;

};

#endif

