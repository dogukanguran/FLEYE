
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
    ui->swimmerLocationTextEdit->setText("No GPS data has been received yet.\n");

    //QUrl urlHq;
    //urlHq.setUrl("https://blogs.commons.georgetown.edu/cctp-797-fall2013/files/2013/10/checkin.png");
    //ui->webView->setUrl(urlHq);

    //declaration of timer
    timer_ = new QTimer();

    //load image and set it to invisible
    QPixmap pix("/Users/Cem/Desktop/FLEYE/Qt/emergency-alert.jpg");
    ui->alertImageLabel->setPixmap(pix);
    ui->alertImageLabel->setVisible(false);

    label_ = ui->alertImageLabel;
    counter_ = 0;
}

//timer function for our alert image
void ClientWindow::timeout()
{
    if(counter_%2)
        ui->alertImageLabel->setVisible(false);
    else
        ui->alertImageLabel->setVisible(true);
    counter_++;
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
    float coordinates[2];
    while ((pos = dataCopy.find(delimiter)) != std::string::npos) {
        token =  dataCopy.substr(0, pos);
        std::cout << token << std::endl;

        coordinates[0] = ::atof(token.c_str());

        token = dataCopy.substr(pos+1,dataCopy.length());
        coordinates[1] = ::atof(token.c_str());


        dataCopy.erase(0, pos + delimiter.length());
    }
    std::cout <<  dataCopy << std::endl;

    //Then we are displaying the X and Y coordinates on the screen.

    QString strTax = QString::number(coordinates[0], 'f', 5);
    qDebug() << strTax;
    ui->swimmerLocationTextEdit->append("\nX : "+strTax);
    QString strTax1 = QString::number(coordinates[1], 'f', 5);
    ui->swimmerLocationTextEdit->append("Y : "+strTax1+"\n");

    //After we get the coordinates we are going to replace google maps image.
    QUrl url;
    QString urlString="";


    char coordination1[10],coordination2[10];

    sprintf(coordination1,"%f",coordinates[0]);
    sprintf(coordination2,"%f",coordinates[1]);

    //we concatanate our url string with our gps
    urlString.append("http://maps.googleapis.com/maps/api/staticmap?center=");
    urlString.append(coordination1);
    urlString.append(",");
    urlString.append(coordination2);
    urlString.append("&zoom=18&size=800x400&maptype=satellite&sensor=true");

    url.setUrl(urlString);
    ui->webView->setUrl(url);

    // our signal slot connector. It will enable us to call timeout function with timer
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeout()));

    timer_->start(1000);

    server_.close();
    client_->close();

}


void ClientWindow::on_pushButton_clicked()
{
    timer_->stop();
    ui->alertImageLabel->setVisible(false);
    ui->swimmerLocationTextEdit->setText("");
    QUrl urlBlank;
    //urlBlank.setUrl("https://blogs.commons.georgetown.edu/cctp-797-fall2013/files/2013/10/checkin.png");
    //ui->webView->setUrl(urlBlank);
}
