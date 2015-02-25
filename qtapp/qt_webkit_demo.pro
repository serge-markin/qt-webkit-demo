#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T10:11:55
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_webkit_demo
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Host.cpp

HEADERS  += MainWindow.h \
    Host.h

FORMS    += MainWindow.ui

RESOURCES += \
    Resources.qrc

DISTFILES += \
    assets/js/test.js
