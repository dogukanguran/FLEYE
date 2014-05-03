
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

    connect(&server, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));

    server.listen(QHostAddress::Any, 8888);
    ui->swimmerLocationTextEdit->setText("Server Starts !...\n");
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::acceptConnection()
{
    client = server.nextPendingConnection();

    connect(client, SIGNAL(readyRead()),
            this, SLOT(startRead()));
}

void ClientWindow::startRead()
{

    char buffer[1024] = {0};
    //QString buffer;
    client->read(buffer, client->bytesAvailable());
    // ui->swimmerLocationTextEdit->setText(buffer);
    ui->swimmerLocationTextEdit->append(buffer);
    ui->swimmerLocationTextEdit->append("\n");


    cout << buffer << endl;
    data = buffer;
    ui->swimmerLocationTextEdit->setText("");
    std::string delimiter = ":";
    std::string dataCopy = data.toLocal8Bit().constData();

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




    QString strTax = QString::number(coordination[0], 'f', 6);
    qDebug() << strTax;
    ui->swimmerLocationTextEdit->append("\nX : "+strTax);
    QString strTax1 = QString::number(coordination[1], 'f', 6);
    ui->swimmerLocationTextEdit->append("Y : "+strTax1+"\n");


    server.close();
    client->close();

}

