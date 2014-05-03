#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include<QString>
#include <string>
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
    //std::string data;
private slots:
  void acceptConnection();
  void startRead();



private:
  QTcpServer server;
  QTcpSocket* client;
  Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
