#include "smtp.h"


Smtp::Smtp(const QString &serverName, const QString &username, const QString &password, const QString &from, const QStringList &to, const QString &subject, const QString &body)
{
    server_ = serverName; //your server name
    user_ = username; //your SMTP username
    pass_ = password; //your SMTP password

    user_ = user_.toLocal8Bit().toBase64();
    pass_ = pass_.toLocal8Bit().toBase64();

    x_ = 1;
    int recipCount = 0;
    socket_ = new QTcpSocket(this);

    connect(socket_, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_, SIGNAL(connected()), this, SLOT(connected() ) );
    connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), this,
             SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket_, SIGNAL(stateChanged( QAbstractSocket::SocketState)), this,
             SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket_, SIGNAL(disconnected()), this,
            SLOT(disconnected()));

    qDebug() << "Signals created";

    for(recipCount = 0; recipCount < to.count(); recipCount++)
    {
        message_.append("To: " + to.at(recipCount) + "\n");
    }
    message_.append("From: " + from_ + "\n");
    message_.append("Subject: " + subject + "\n");
    message_.append("Mime-Version: 1.0;\n");
    message_.append("Content-Type: text/html; charset=\"utf8\";\n");
    message_.append("Content-Transfer-Encoding: 8bit;\n");
    message_.append("\n");
    qDebug() << "body is: " << body;
    message_.append(body);
    message_.replace(QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n"));
    message_.replace(QString::fromLatin1( "\r\n.\r\n" ), QString::fromLatin1( "\r\n..\r\n" ) );

    this->from_ = from;
    rcpt_ = to.at(0);
    recips_ = to;
    state_ = Init;
    socket_->connectToHost(server_, 587);
    if(socket_->waitForConnected(10000))
    {
        qDebug("connected");
    }

    t_ = new QTextStream( socket_ );
}
Smtp::~Smtp()
{
    qDebug() << "Destroying";
    finished();
    delete t_;
    delete socket_;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{

    qDebug() <<"stateChanged: " << socketState;

}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << " error:" <<socketError;

}

void Smtp::disconnected()
{
    //qDebug() << "Disconnected: "  << socket->errorString();
    qDebug() << "Disconnected from server.";
}

void Smtp::connected()
{
}

void Smtp::readyRead()
{
    QString rLine;
    do
    {
        rLine = socket_->readLine();
        response_ += rLine;
        qDebug() << "Response is: " << response_;
    }
    while (socket_->canReadLine() && rLine[3] != ' ');

    rLine.truncate(3);

    if (state_ == Init && rLine[0] == '2')
    {
        qDebug() << "HELO there";
        *t_ << "HELO there\r\n";
        t_->flush();

        state_ = Auth;
    }
    else if (state_ == Auth && rLine[0] == '2')
    {
        // Trying AUTH
        qDebug() << "Auth";
        *t_ << "AUTH LOGIN" << "\r\n";
        t_->flush();
        state_ = User;
    }
    else if (state_ == User && rLine[0] == '3')
    {
        //Trying User
        qDebug() << "Username";
        *t_ << user_ << "\r\n";
        t_->flush();

        state_ = Pass;
    }
    else if (state_ == Pass && rLine[0] == '3')
    {
        //Trying pass
        qDebug() << "Pass";
        *t_ << pass_ << "\r\n";
        t_->flush();

        state_ = Mail;
    }
    else if (state_ == Mail && rLine[0] == '2')
    {
        qDebug() << "Mail from";
        *t_ << "MAIL FROM: " << from_ << "\r\n";
        t_->flush();
        state_ = Rcpt;
    }
    else if (state_ == Rcpt && rLine[0] == '2')
    {

        qDebug() << "RCPT TO ";
        *t_ << "RCPT TO: " << rcpt_ << "\r\n";
        t_->flush();
        if(recips_.isEmpty() || x_ == recips_.count() )
        {
            state_ = Data;
        }
        else
        {
            if(x_ < recips_.count())
            {
                rcpt_ = recips_.at(x_);
                x_++;
                state_ = Rcpt;
            }
        }
    }
    else if (state_ == Data && rLine[0] == '2')
    {
        qDebug() << "Data";
        *t_ << "DATA\r\n";
        t_->flush();
        state_ = Body;
    }
    else if (state_ == Body && rLine[0] == '3')
    {
        qDebug() << "Body state";
        *t_ << message_ << "\r\n.\r\n";
        t_->flush();
        state_ = Quit;
    }
    else if (state_ == Quit && rLine[0] == '2')
    {
        qDebug() << "Quit";
        *t_ << "QUIT\r\n";
        t_->flush();
        // here, we just close.
        state_ = Close;
        emit status( tr( "Message sent" ) );
    }
    else if (state_ == Close)
    {
        qDebug() << "State == close";
        deleteLater();
        return;
    }
    else
    {
        //something has broken
        state_ = Close;
    }
    response_ = "";
}
