#include <QApplication>
#include <zwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    zWidget widget;
    widget.show();

    return a.exec();
}
