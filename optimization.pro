#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T19:05:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = optimization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polys.cpp

HEADERS  += mainwindow.h \
    polys.h \
    powell.h

FORMS    += mainwindow.ui
