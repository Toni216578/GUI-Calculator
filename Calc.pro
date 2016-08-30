#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T14:56:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zeileneingabe.cpp \
    winkel.cpp

HEADERS  += mainwindow.h \
    zeileneingabe.h \
    winkel.h

FORMS    += mainwindow.ui \
    zeileneingabe.ui \
    winkel.ui

RESOURCES += \
    res.qrc

DISTFILES +=
