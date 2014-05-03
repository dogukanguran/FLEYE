#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
private:
    QTcpSocket* socket_;
public:
    Client(QObject* parent);
    void connectToServer();
    void on_connected();
};

#endif // CLIENT_H
