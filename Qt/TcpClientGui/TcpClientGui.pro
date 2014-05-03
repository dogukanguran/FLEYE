#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T16:19:29
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += webkit webkitwidgets
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpClientGui
TEMPLATE = app


SOURCES += main.cpp\
        clientwindow.cpp

HEADERS  += clientwindow.h

FORMS    += clientwindow.ui
