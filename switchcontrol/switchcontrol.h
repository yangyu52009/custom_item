#ifndef SWITCHCONTROL_H
#define SWITCHCONTROL_H

#include <QWidget>
#include <QTimer>

class SwitchControl : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchControl(QWidget *parent = 0);

public:
    bool isToggled() const;
    void setTogggled(bool checked);
    //开关状态
    void setBackgroundColor(QColor color);
    //设置背景颜色
    void setCheckColor(QColor color);
    //设置选中颜色
    void setDisabledColor(QColor color);
    //设置不可用时候颜色

public:
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
    //缺省大小
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标按下和释放事件,切换开关的状态发送toggled()信号
    virtual void paintEvent(QPaintEvent *event) override;
    //绘图事件
    virtual void resizeEvent(QResizeEvent *event) override;
    //大小改变事件
signals:
    void toggled(bool checked);
    //状态改变时候发送信号
private slots:
    void onTimeout();
    //状态改变时,用于滑动效果
private:
    bool m_bChecked; //是否选中
    QColor m_background; //背景颜色
    QColor m_checkedColor;//选中颜色
    QColor m_disabledColor;//不可用状态的颜色
    QColor m_thumbColor; //拇指颜色
    qreal m_radius; //圆角
    qreal m_nX;//x点的坐标
    qreal m_nY;//y点的坐标
    qint16 m_nHeight;//高度
    qint16 m_nMargin; //外边距

    QTimer m_timer;
};

#endif // SWITCHCONTROL_H
