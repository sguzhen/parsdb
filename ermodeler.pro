#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T00:02:50
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ermodeler
TEMPLATE = app


QMAKE_LFLAGS += -static -static-libgcc


SOURCES += main.cpp\
        mainwindow.cpp \
    atrparam.cpp \
    setsvyaz.cpp \
    login.cpp \
    suzhparam.cpp

HEADERS  += mainwindow.h \
    suzhnost.h \
    textinbox.h \
    textinell.h \
    atrparam.h \
    atribut.h \
    lines.h \
    setsvyaz.h \
    svyaz.h \
    login.h \
    paramsuzh.h \
    paramatr.h \
    suzhparam.h

FORMS    += mainwindow.ui \
    atrparam.ui \
    setsvyaz.ui \
    login.ui \
    suzhparam.ui

DISTFILES += \
    atr.ico \
    suzh.ico
