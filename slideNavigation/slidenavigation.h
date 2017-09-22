#ifndef SLIDENAVIGATION_H
#define SLIDENAVIGATION_H

#include <QWidget>
#include <QStringList>
/*!
* @version 0.1
* @anchor zl
* @note 201709
* @def 滑动导航条
*       效果大概就是 导航项目按下的时候有切换移动的效果
* @warning 暂时没有测试是否可以正常使用
*/
class SlideNavigation : public QWidget
{
    Q_OBJECT
public:
    enum ItemLineStyle
    {
        None = 0, //不显示
        ItemTop, //上方
        ItemBottom,//下方
        ItemLeft, //左方
        ItemRight, //右方
        ItemRect //矩形
    };
    explicit SlideNavigation(QWidget *parent = 0);
    ~SlideNavigation ();
public:
    void addItem ( QString str); //使用给定的str 生成 item 添加到导航中  在构造函数之后调用
    void setBarStartColor ( const QColor& color);
    void setBarEndColor ( const QColor& color);
    void setItemStartColor ( const QColor& color);
    void setItemEndColor ( const QColor& color);
    void setItemTextColor ( const QColor& color);
    void setItemLineColor ( const QColor& color);
    void setBarRadious ( int radious );
    void setItemRadious ( int radious);
    void setSpace ( int space );
    void setItemLineWidth (int width);
    void setItemStyle ( ItemLineStyle style);
    void setOrientation ( Qt::Orientation orientation);

    QStringList getItems_Strs ();
    QString mapToItemStr ( int index);
    int mapToIndex ( const QString& str);
public slots:
    void setEnableKeyMouse ( bool enable = false);
    void moveFirst ();
    void moveLast ();
    void movePrevious ();
    void moveNext ();
    void moveTo ( int index);
    void moveTo ( QString str);
    void moveTo ( QPointF point);
signals:
    void currentItemChanged (int index);

protected:
    void drawBarBackground ( QPainter& painter);
    void drawItemBackground ( QPainter& painter);
    void drawItemLine ( QPainter& painter);
    void drawText ( QPainter& painter);

    QList<QTimer *> getTimers () const; //返回 内部使用的定时器

    // QWidget interface
protected:
    //处理鼠标事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //作为一个UI组件，操控所用的快捷键应该统一的进行管理，此函数没有任何的其他实现，只是调用父类的同名函数
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    void adjustItemSize (); //调整Item 的大小
private slots:
    void doSlide (); //滑动过程，由定时器  m_slideTimer 驱动
    void doShake (); //晃动（最后调整）过程 m_shakeTimer
private:
    //背景色
    QColor m_barStartColor ;
    QColor m_barEndColor ;
    //item 颜色
    QColor m_itemStartColor ;
    QColor m_itemEndColor ;
    QColor m_itemTextColor ;//Item文字颜色
    QColor m_itemLineColor ;//Item线条指示器颜色

    int m_barRadious;//导航条边框圆角
    int m_itemRadious;//Item圆角

    int m_space;//Item间隔
    int m_itemLineWidth;//Item线条宽度
    ItemLineStyle m_itemLineStyle;//Item线条类型
    Qt::Orientation m_orientation;//导航方向
    bool m_enableKeyMove;//是否支持按键移动

    QMap<int, QPair<QString, QRectF>> m_itemList;
    int m_totalTextWidth;//文字总长度,resize时重新计算每个Item的RectF
    int m_totalTextHeight;
    int m_currentItemIndex;//当前选中item
    QRectF m_startRect;//移动开始
    QRectF m_stopRect;//移动结束
    QTimer* m_slideTimer;//移动定时器
    QTimer* m_shakeTimer;//晃动定时器
    bool m_forward;//前进
};

#endif // SLIDENAVIGATION_H
