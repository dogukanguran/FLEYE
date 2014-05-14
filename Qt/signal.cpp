#include "email.h"
#include "login.h"
#include "server.h"
#include "signal.h"
#include "smtp.h"

#include <QtCore>
#include <QSqlQuery>

extern Coordination coordination;
extern Server server;

Signal::Signal()
{
}

Signal::~Signal(){

}

//In this function we are checking the signal is for us or not.
bool Signal::checkSignal(QString gpsData)
{

    //Splitting our coordinates and converting them into float again.
    float x,y;
    QString hqCity = "Ankara";
    QStringList list = gpsData.split(QRegExp(";"));
    x = list[0].toFloat();
    y = list[1].toFloat();


    //We are getting the headquarter info from database
    QSqlQuery query;
    query.prepare("SELECT * FROM headquarter WHERE hqCity = :city ");
    query.bindValue(":city",hqCity);
    query.exec();


    if(query.next())
    {
        //hqX and hqY is headquarter's coordinate. We are getting them from database
        float hqX = query.value(3).toFloat();
        float hqY = query.value(4).toFloat();

        // 0.00250 means 100 meters distance from our headquarter coordinations. If Signal is coming from 100m. then process it.
        if( hqX-x < -0.00250 || hqX-x > 0.00250 || hqY-y < -0.00250 || hqY-y > 0.00250 )
        {
            qDebug() << "Chance of incorrect data!" ;
            return false;
        }
        else
        {
            qDebug() << "Correct data!";

            //If signal is for us then we are creating a char array and send an e-mail to hospital.
            char buffer [150];
            QString str = query.value(8).toString();
            QByteArray ba = str.toLocal8Bit();
            const char *c_str2 = ba.data();
            sprintf (buffer, "We need an ambulance over %s !! Coordinates: \nX: %f Y: %f",c_str2  ,hqX,hqY);
            Email *sendEmail = new Email("c_ertug@ug.bilkent.edu.tr","turkishsoldier51@gmail.com",
                                         "EMERGENCY!!",buffer);

            coordination.setX(x);
            coordination.setY(y);
            // And after sending e-mail we set our last target coordination to the swimmer's coordinates.


            // And we start the server to send swimmer's coordinates to the lifeguard's application.
            server.start("139.179.142.40", 8888);
            //server.disconnect();

        }
    }

    return true;
}
