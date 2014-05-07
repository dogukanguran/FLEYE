#include "signal.h"
#include <QtCore>
#include <QSqlQuery>
#include "login.h"
#include "email.h"
#include "server.h"
#include "smtp.h"

extern Coordination coordination;

Signal::Signal()
{
}

Signal::~Signal(){

}

bool Signal::checkSignal(QString gpsData)
{
    float x,y;
    QString hqCity = "Ankara";
    QStringList list = gpsData.split(QRegExp(";"));
    x = list[0].toFloat();
    y = list[1].toFloat();


    QSqlQuery query;
    query.prepare("SELECT * FROM headquarter WHERE hqCity = :city ");
    query.bindValue(":city",hqCity);
    query.exec();


    if(query.next())
    {
        float hqX = query.value(3).toFloat();
        float hqY = query.value(4).toFloat();

        if( hqX-x < -0.005 || hqX-x > 0.005 || hqY-y < -0.005 || hqY-y > 0.005 )
        {
            qDebug() << "Chance of incorrect data!" ;
        }
        else
        {
            qDebug() << "Correct data!";

            char buffer [150];
            QString str = query.value(8).toString();
            QByteArray ba = str.toLocal8Bit();
            const char *c_str2 = ba.data();
            sprintf (buffer, "We need an ambulance over %s !! Coordinates: \nX: %f Y: %f",c_str2  ,hqX,hqY);
           // Email *sendEmail = new Email("c_ertug@ug.bilkent.edu.tr","turkishsoldier51@gmail.com",
            //                             "EMERGENCY!!",buffer);

            coordination.setX(x);
            coordination.setY(y);

            Server server;
            server.start("127.0.0.1", 1234);
            server.disconnect();
        }
    }

    return true;
}
