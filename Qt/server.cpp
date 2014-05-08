#include "coordination.h"
#include "server.h"

#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>

#include <sstream>


extern Coordination coordination;

//When server object is created, it will automatically call sendLocationToLifeguard method
Server::Server(QObject* parent): QObject(parent)
{
    connect(&server_, SIGNAL(connected()),
            this, SLOT(sendLocationToLifeguard()));
}

Server::~Server()
{
    server_.close();
}

//Server communication gets address and port. Then, starts the service
void Server::start(QString address, quint16 port)
{
    qDebug() << "Connection started";
    QHostAddress addr(address);
    server_.connectToHost(addr, port);

}

//Here we are converting float number to string
std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

//Here we are checking coordination and send messages to the hospital and lifeguard.
void Server::sendLocationToLifeguard()
{
    qDebug() << "Sending GPS data to server\n";

    char f1Val[32],f2Val[32];

    // Here we used qDebug to see that our coordinations is true.
    //qDebug() << coordination.getX();
    //qDebug() << coordination.getY();

    //Converting float values to char array
    sprintf(f1Val,"%f",coordination.getX());
    sprintf(f2Val,"%f",coordination.getY());

    //We concatanate the coordinates and send them to the client. ( Lifeguard )
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
