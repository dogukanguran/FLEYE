/*
 * This class will help us to send an e-mail to the hospital.
 */

#ifndef EMAIL_H
#define EMAIL_H

#include "qstring.h"

#include "QTcpSocket"
#include <QTextStream>

class Email
{
private:
    QString sender_;
    QString message_;
    QString receiver_;
    QString subject_;
    QTcpSocket* socket_;

public:
    Email(const QString&,const QString&,const QString&,const QString&);
    ~Email();
};

#endif // EMAIL_H
