#ifndef EMAIL_H
#define EMAIL_H
#include "qstring.h"
#include <QTextStream>
#include "QTcpSocket"
class Email
{
private:
    QString sender;
    QString message;
    QString receiver;
    QString subject;
    QTcpSocket *socket;

public:
    Email(const QString&,const QString&,const QString&,const QString&);
    ~Email();
};

#endif // EMAIL_H
