#-------------------------------------------------
#
# Project created by QtCreator 2017-07-22T22:41:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = customItem_Qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    switchcontrol\switchcontrol.cpp \
    zwidget.cpp \
    DynamicProgress/circlewait.cpp \
    DynamicProgress/donutwait.cpp \
    DynamicProgress/linewait.cpp \
    DynamicProgress/piewait.cpp \
    DynamicProgress/taichiwait.cpp \
    DynamicProgress/zoomcirclewait.cpp

HEADERS  += \
    switchcontrol\switchcontrol.h \
    zwidget.h \
    DynamicProgress/circlewait.h \
    DynamicProgress/donutwait.h \
    DynamicProgress/linewait.h \
    DynamicProgress/piewait.h \
    DynamicProgress/taichiwait.h \
    DynamicProgress/zoomcirclewait.h
