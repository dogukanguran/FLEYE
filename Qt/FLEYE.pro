#-------------------------------------------------
#
# Project created by QtCreator 2014-02-28T16:20:10
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = FLEYE

CONFIG += x86_64
CONFIG -= i386
TEMPLATE = app

QTPLUGIN += QSQLMYSQL


LIBS += /Applications/MySQLWorkbench.app/Contents/Frameworks/libmysqlclient.18.dylib
LIBS += -L/usr/local/lib

SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    server.cpp \
    client.cpp \
    signal.cpp \
    coordination.cpp \
    fleye.cpp \
    report.cpp \
    smtp.cpp \
    email.cpp

HEADERS  += mainwindow.h \
    database.h \
    server.h \
    client.h \
    signal.h \
    coordination.h \
    fleye.h \
    report.h \
    smtp.h \
    email.h

FORMS    += mainwindow.ui
