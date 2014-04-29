#include "email.h"
#include "smtp.h"

#include <QDateTime>
#include <QEventLoop>

Email::Email(const QString& sender,const QString& receiver,const QString& subject,const QString& message)
{
    //this function gets needed inputs and prepares mail to be sent.
    QEventLoop loop;
    QStringList list;
    list.append(receiver);
    Smtp *newMail  = new Smtp("asmtp.bilkent.edu.tr","c_ertug@ug.bilkent.edu.tr","****",sender,list,subject,message);
    QObject::connect(newMail, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

}

