#ifndef SERVER_H
#define SERVER_H

#include "coordination.h"

#include <QDebug>
#include <QMessageBox>
#include <QString>

#include <QTcpSocket>
#include <QTcpServer>
#include <QTextStream>
#include <QHostAddress>
#include <QObject>
#include <QtNetwork>
#include <QtCore>



class Server : public QObject
{
Q_OBJECT
public slots:
    //bool sendLocationToLifeguard(float,float);
    void sendLocationToLifeguard();

public:
    Server(QObject* parent = 0);
    ~Server();
    void start(QString address, quint16 port);
    void disconnect();



private:
    int gpsId_;
    Coordination coordinationOfSwimmer_;
    Coordination coordinationOfFLEYE_;
    Coordination coordinationOfHQ_;
    QTcpSocket server_;

};

#endif // SERVER_H
