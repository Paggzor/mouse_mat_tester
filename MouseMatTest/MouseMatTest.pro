#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T14:36:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MouseMatTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mouseeventfilter.cpp

HEADERS  += mainwindow.h \
    mouseeventfilter.h

FORMS    += mainwindow.ui
