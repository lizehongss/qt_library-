#-------------------------------------------------
#
# Project created by QtCreator 2018-03-17T22:35:24
#
#-------------------------------------------------

QT       += core gui
QT   +=sql
QT +=xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_library
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    connection.h

FORMS    += widget.ui
