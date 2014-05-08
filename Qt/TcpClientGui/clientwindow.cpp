
#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QChar>
#include <iostream>
#include <string>
using namespace std;


ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->swimmerLocationLabel->setStyleSheet("QLabel{background-color:green}");
    ui->mapLabel->setStyleSheet("QLabel{background-color:green}");

    //We are starting to accept connections
    connect(&server_, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));


    //We are starting to listen from any connection using 1235 port.
    server_.listen(QHostAddress::Any, 1235);
    ui->swimmerLocationTextEdit->setText("Server Starts !...\n");

    //After we get the coordinates we are going to replace google maps image.
    QUrl url;
    url.setUrl("http://maps.googleapis.com/maps/api/staticmap?center=39.8716863,32.7326193&zoom=16&size=800x400&maptype=satellite&sensor=false");
    ui->webView->setUrl(url);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::acceptConnection()
{

    //We are waiting a connection. After we get connection we are going to start reading
    client_ = server_.nextPendingConnection();

    connect(client_, SIGNAL(readyRead()),
            this, SLOT(startRead()));
}

void ClientWindow::startRead()
{

    char buffer[256] = {0};

    //We are getting bytes and turn them into string again.
    client_->read(buffer, client_->bytesAvailable());
    // ui->swimmerLocationTextEdit->setText(buffer);
    ui->swimmerLocationTextEdit->append(buffer);
    ui->swimmerLocationTextEdit->append("\n");


    cout << buffer << endl;
    data = buffer;
    ui->swimmerLocationTextEdit->setText("");
    std::string delimiter = ":";
    std::string dataCopy = data.toLocal8Bit().constData();

    //We split string by ":" character.
    size_t pos = 0;
    std::string token;
    float coordination[2];
    int i=0;
    while ((pos = dataCopy.find(delimiter)) != std::string::npos) {
        token =  dataCopy.substr(0, pos);
        std::cout << token << std::endl;

        coordination[i] = ::atof(token.c_str());


        dataCopy.erase(0, pos + delimiter.length());
        i++;
    }
    std::cout <<  dataCopy << std::endl;

    printf("\nX : %0.6f",coordination[0]);
    printf("\nY : %0.6f",coordination[1]);



    //Then we are displaying the X and Y coordinates on the screen.

    QString strTax = QString::number(coordination[0], 'f', 6);
    qDebug() << strTax;
    ui->swimmerLocationTextEdit->append("\nX : "+strTax);
    QString strTax1 = QString::number(coordination[1], 'f', 6);
    ui->swimmerLocationTextEdit->append("Y : "+strTax1+"\n");


    server_.close();
    client_->close();

}

