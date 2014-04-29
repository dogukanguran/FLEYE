#ifndef SERVER_H
#define SERVER_H
#include "coordination.h"
#include <QString>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

class Server
{
private:
    int gpsId_;
    Coordination coordinationOfSwimmer_;
    Coordination coordinationOfFLEYE_;
    Coordination coordinationOfHQ_;
    QTcpSocket *socket_;
    QTcpServer *server_;
public:
    bool connectToFLEYE();
    Server();
    bool sendLocationToLifeguard();
    void listen();
    void on_newConnection();
    void on_readyRead();
    void on_disconnected();

};

#endif // SERVER_H
