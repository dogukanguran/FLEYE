#-------------------------------------------------
#
# Project created by QtCreator 2014-02-28T16:20:10
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += webkit webkitwidgets
QT       += serialport

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
    email.cpp \
    qtxb.cpp \
    qtxb/digimeshpacket.cpp \
    qtxb/atcommandqueueparam.cpp \
    qtxb/atcommand.cpp \
    qtxb/txrequest.cpp \
    qtxb/txrequestexplicit.cpp \
    qtxb/atcommandremote.cpp \
    qtxb/atcommandresponse.cpp \
    qtxb/modemstatus.cpp \
    qtxb/transmitstatus.cpp \
    qtxb/rxindicator.cpp \
    qtxb/remotecommandrequest.cpp \
    qtxb/rxindicatorexplicit.cpp \
    qtxb/nodeidentificationindicator.cpp \
    qtxb/remotecommandresponse.cpp \
    login.cpp

HEADERS  += mainwindow.h \
    database.h \
    server.h \
    client.h \
    signal.h \
    coordination.h \
    fleye.h \
    report.h \
    smtp.h \
    email.h \
    qtxb.h \
    qtxb/digimeshpacket.h \
    qtxb/atcommandqueueparam.h \
    qtxb/atcommand.h \
    qtxb/txrequest.h \
    qtxb/txrequestexplicit.h \
    qtxb/atcommandremote.h \
    qtxb/atcommandresponse.h \
    qtxb/modemstatus.h \
    qtxb/transmitstatus.h \
    qtxb/rxindicator.h \
    qtxb/remotecommandrequest.h \
    qtxb/rxindicatorexplicit.h \
    qtxb/nodeidentificationindicator.h \
    qtxb/remotecommandresponse.h \
    login.h

FORMS    += mainwindow.ui \
    login.ui
