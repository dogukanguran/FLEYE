#include "server.h"
#include <QHostAddress>
#include <QCoreApplication>
#include <QDebug>
#include <sstream>
#include "coordination.h"

extern Coordination c;

Server::Server(QObject* parent): QObject(parent)
{
    connect(&server_, SIGNAL(connected()),
            this, SLOT(sendLocationToLifeguard()));
}

Server::~Server()
{
    server_.close();
}

void Server::start(QString address, quint16 port)
{
    qDebug() << "Connection started";
    QHostAddress addr(address);
    server_.connectToHost(addr, port);

}

std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

void Server::sendLocationToLifeguard()
{
    qDebug() << "Sending GPS data to server\n";

    char f1Val[32],f2Val[32];
    float f1 = 232.42424;
    float f2 = 123.34333;
    //float f1;
    //float f2;

    //f1 = co.getX();
    //f2 = co.getY();

    qDebug() << c.getX();
    qDebug() << c.getY();

    sprintf(f1Val,"%f",c.getX());
    sprintf(f2Val,"%f",c.getY());

    char* newArray = new char[std::strlen(f1Val)+std::strlen(f2Val)+1];
    std::strcpy(newArray,f1Val);
    std::strcat(newArray,":");
    std::strcat(newArray,f2Val);

    server_.write(newArray,64);
    server_.flush();
    delete [] newArray;
    qDebug() <<"GPS data has been sent.\n";
}

void Server::disconnect()
{
    server_.close();
}
