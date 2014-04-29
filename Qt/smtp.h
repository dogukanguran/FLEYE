/*
 * This class is for SMTP operations. We will use this class to send an e-mail to the FLEYE.
 */
#ifndef SMTP_H
#define SMTP_H

#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

class Smtp : public QObject
{
    Q_OBJECT


public:
    //Smtp( const QString &from, const QStringList &to,
      //  const QString &subject, const QString &body );
    Smtp(const QString &serverName, const QString &username, const QString &password, const QString &from, const QStringList &to, const QString &subject, const QString &body);
    ~Smtp();
    void initalise();

signals:
        void status( const QString &);
        void finished();

private slots:
        void stateChanged(QAbstractSocket::SocketState );
        void errorReceived(QAbstractSocket::SocketError );
        void disconnected();
        void connected();
        void readyRead();

private:
        QString message_;
        QTextStream *t_;
        QTcpSocket *socket_;
        QString from_;
        QString rcpt_;
        QString response_;
        QStringList recips_;
        QString server_;
        QString user_;
        QString pass_;
        int x_;
        enum states{Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};
        int state_;
};

#endif
