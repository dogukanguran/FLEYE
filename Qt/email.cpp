#include "email.h"
#include "smtp.h"

#include <QDateTime>
#include <QEventLoop>

//function to send an e-mail. Function will call itself automatically.
Email::Email(const QString& sender,const QString& receiver,const QString& subject,const QString& message)
{
    //this function gets needed inputs and prepares mail to be sent.
    QEventLoop loop;
    QStringList list;
    list.append(receiver);
    Smtp *newMail  = new Smtp("asmtp.bilkent.edu.tr","c_ertug@ug.bilkent.edu.tr","03cem1991",sender,list,subject,message);
    QObject::connect(newMail, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

}

