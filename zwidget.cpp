#include "zwidget.h"
#include "switchcontrol/switchcontrol.h"

#include <QEvent>
zWidget::zWidget(QWidget *parent) : QWidget(parent)
{
    this->resize (600,600);
    /*！！*/
    this->setAttribute (Qt::WA_TranslucentBackground);//没有重绘的地方使用透明填充
    this->setWindowFlags(Qt::FramelessWindowHint | //没有边框的窗口
                         Qt::WindowSystemMenuHint | //显示系统菜单
                         Qt::WindowMinimizeButtonHint); //显示最小化按钮
    this->installEventFilter ( this); //安装该窗口的事件过滤器集中的处理事件
    /*上面的代码与透明背景相关*/

    SwitchControl *pSwitchControl = new SwitchControl(this);
        pSwitchControl->setBackgroundColor(Qt::black);
        pSwitchControl->setCheckColor (Qt::blue);
        pSwitchControl->setDisabledColor (Qt::red);
  //  SwitchControl *pGreenSwitchControl = new SwitchControl(this);
   // SwitchControl *pDisabledSwitchControl = new SwitchControl(this);
}

/*!
*   @note 这是绘制透明阴影窗口的事件处理函数
*/
bool zWidget::eventFilter(QObject *watched, QEvent *event)
{
    static int index = 1;
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();

            if (index == 4) {
                index = 1;
            } else {
                index++;
            }

           ui->widget->setStyleSheet(QString("background-image: url(:/%1.png);").arg(index));
           //有多张的背景图片进行演示
           // this->update (); //可以使用在paintevent中drawpixmap来设置背景
            return true;
        } else {
            exit(0);
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    } else if (event->type() == QEvent::WindowStateChange){
        if (isMinimized ()) {
            // 处理Minimized鍵
            setWindowFlags(Qt::FramelessWindowHint | this->windowFlags ());
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);

}
