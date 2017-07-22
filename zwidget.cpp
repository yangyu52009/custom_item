#include "zwidget.h"
#include "switchcontrol.h"
zWidget::zWidget(QWidget *parent) : QWidget(parent)
{
    this->resize (600,600);

    SwitchControl *pSwitchControl = new SwitchControl(this);
        pSwitchControl->setBackgroundColor(Qt::black);
        pSwitchControl->setCheckColor (Qt::blue);
        pSwitchControl->setDisabledColor (Qt::red);
  //  SwitchControl *pGreenSwitchControl = new SwitchControl(this);
   // SwitchControl *pDisabledSwitchControl = new SwitchControl(this);
}
