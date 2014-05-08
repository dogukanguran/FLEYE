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
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4):

include(xlsx/qtxlsx.pri)


TARGET = FLEYE

CONFIG += x86_64
CONFIG -= i386



INCLUDEPATH += /Users/Cem/Applications/Qt/5.2.0/clang_64/include


TEMPLATE = app

QTPLUGIN += QSQLMYSQL


LIBS += /Applications/MySQLWorkbench.app/Contents/Frameworks/libmysqlclient.18.dylib
LIBS += -L/usr/local/lib
LIBS += -L/Users/Cem/Applications/Qt/5.2.0/clang_64/lib

SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    server.cpp \
    signal.cpp \
    coordination.cpp \
    fleye.cpp \
    smtp.cpp \
    email.cpp \
    login.cpp \
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
    qtxb/remotecommandresponse.cpp
HEADERS  += mainwindow.h \
    database.h \
    server.h \
    signal.h \
    coordination.h \
    fleye.h \
    smtp.h \
    email.h \
    login.h \
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
    qtxb/remotecommandresponse.h


FORMS    += mainwindow.ui \
    login.ui
