#ifndef TAIJIPROGRESS_H
#define TAIJIPROGRESS_H

#include <QWidget>
/*****************************************************
**Copyright(C), 2017-2025, zl software.
**Version: 1.0
**Author: yangyu
**Date: 20170831
**Description:太极形状的旋转条
*****************************************************/
class TaiJiProgress : public QWidget
{
    Q_OBJECT
public:
    explicit TaiJiProgress(QWidget *parent = 0);

    void setFrontColor (QColor color);
    void setBackgroundColor (QColor color);
    void setClockwiseRotate (bool clockwise);
    void setRotateDelta (int delta);
signals:

public slots:
    void Start_Stop (bool nor = true);
protected:
    void drawTaiji (QPainter& painter);
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

#endif // TAIJIPROGRESS_H
