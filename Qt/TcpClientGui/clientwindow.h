#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include<QString>
#include <string>
#include "ui_clientwindow.h"
using namespace std;

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();
    QString data;

public slots:
    void timeout();

private slots:
  void acceptConnection();
  void startRead();

  void on_pushButton_clicked();

private:
  QTcpServer server_;
  QTcpSocket* client_;
  QTimer  *timer_;
  QLabel  *label_;
  int counter_;
  Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
