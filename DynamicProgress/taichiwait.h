#ifndef TAICHIWAIT_H
#define TAICHIWAIT_H

#include <QWidget>
//太极图
class TaiChiWait : public QWidget
{
    Q_OBJECT
public:
    explicit TaiChiWait(QWidget *parent = 0);

    void setFrontColor(QColor color); //前景色
    void setBackColor(QColor color); //背景色
    void setClockwiseRotate(bool clockwise); //是否是顺时针旋转
    void setRotateDelta(int delta);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void drawTaiChiWait(QPainter& p);//太极

private:
    QColor m_frontColor;//前景色
    QColor m_backColor;//背景色
    bool m_clockwiseRotate;//顺时针旋转
    int m_rotateDelta;//旋转步进角度
    int m_rotateAngle;//旋转角度

    QTimer* m_timer;
};

#endif // TAICHIWAIT_H
