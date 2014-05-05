/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

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
            ClientWindow->setObjectName(QStringLiteral("ClientWindow"));
        ClientWindow->resize(625, 337);
        centralWidget = new QWidget(ClientWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        swimmerLocationLabel = new QLabel(centralWidget);
        swimmerLocationLabel->setObjectName(QStringLiteral("swimmerLocationLabel"));
        swimmerLocationLabel->setGeometry(QRect(20, 30, 101, 20));
        swimmerLocationTextEdit = new QTextEdit(centralWidget);
        swimmerLocationTextEdit->setObjectName(QStringLiteral("swimmerLocationTextEdit"));
        swimmerLocationTextEdit->setGeometry(QRect(20, 60, 181, 81));
        mapLabel = new QLabel(centralWidget);
        mapLabel->setObjectName(QStringLiteral("mapLabel"));
        mapLabel->setGeometry(QRect(260, 30, 181, 16));
        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(290, 60, 321, 200));
        webView->setUrl(QUrl(QStringLiteral("http://maps.googleapis.com/maps/api/staticmap?center=39.867136,32.749911&zoom=15&size=800x400&sensor=false")));
        ClientWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 625, 21));
        ClientWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ClientWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ClientWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ClientWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ClientWindow->setStatusBar(statusBar);

        retranslateUi(ClientWindow);

        QMetaObject::connectSlotsByName(ClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientWindow)
    {
        ClientWindow->setWindowTitle(QApplication::translate("ClientWindow", "ClientWindow", 0));
        swimmerLocationLabel->setText(QApplication::translate("ClientWindow", "Location of Swimmer", 0));
        mapLabel->setText(QApplication::translate("ClientWindow", "Location of Swimmer in the Map", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
