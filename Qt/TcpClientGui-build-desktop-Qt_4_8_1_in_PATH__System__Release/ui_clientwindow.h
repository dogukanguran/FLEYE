/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created: Sat May 3 21:26:39 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_ClientWindow
{
public:
    QWidget *centralWidget;
    QLabel *swimmerLocationLabel;
    QTextEdit *swimmerLocationTextEdit;
    QLabel *mapLabel;
    QWebView *webView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientWindow)
    {
        if (ClientWindow->objectName().isEmpty())
            ClientWindow->setObjectName(QString::fromUtf8("ClientWindow"));
        ClientWindow->resize(625, 337);
        centralWidget = new QWidget(ClientWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        swimmerLocationLabel = new QLabel(centralWidget);
        swimmerLocationLabel->setObjectName(QString::fromUtf8("swimmerLocationLabel"));
        swimmerLocationLabel->setGeometry(QRect(20, 30, 101, 20));
        swimmerLocationTextEdit = new QTextEdit(centralWidget);
        swimmerLocationTextEdit->setObjectName(QString::fromUtf8("swimmerLocationTextEdit"));
        swimmerLocationTextEdit->setGeometry(QRect(20, 60, 181, 81));
        mapLabel = new QLabel(centralWidget);
        mapLabel->setObjectName(QString::fromUtf8("mapLabel"));
        mapLabel->setGeometry(QRect(260, 30, 181, 16));
        webView = new QWebView(centralWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(290, 60, 321, 200));
        webView->setUrl(QUrl(QString::fromUtf8("http://maps.googleapis.com/maps/api/staticmap?center=39.867136,32.749911&zoom=15&size=800x400&sensor=false")));
        ClientWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 625, 21));
        ClientWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ClientWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ClientWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ClientWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ClientWindow->setStatusBar(statusBar);

        retranslateUi(ClientWindow);

        QMetaObject::connectSlotsByName(ClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientWindow)
    {
        ClientWindow->setWindowTitle(QApplication::translate("ClientWindow", "ClientWindow", 0, QApplication::UnicodeUTF8));
        swimmerLocationLabel->setText(QApplication::translate("ClientWindow", "Location of Swimmer", 0, QApplication::UnicodeUTF8));
        mapLabel->setText(QApplication::translate("ClientWindow", "Location of Swimmer in the Map", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
