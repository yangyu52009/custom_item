#ifndef ZWIDGET_H
#define ZWIDGET_H

#include <QWidget>

class zWidget : public QWidget
{
    Q_OBJECT
public:
    explicit zWidget(QWidget *parent = 0);



    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // ZWIDGET_H
