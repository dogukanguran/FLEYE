
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtxb.h"
#include <QtSerialPort/QSerialPort>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->OnOff->setStyleSheet("QLabel { background-color: green } ");
    ui->FLEYEConditionText->setStyleSheet("QLabel { background-color: green } ");
    ui->HospitalMailText->setStyleSheet("QLabel { background-color: green } ");
    ui->CoordinationToLifeGuardText->setStyleSheet("QLabel { background-color: green } ");
    ui->SwimmerDistanceText->setStyleSheet("QLabel { background-color: red } ");

    /*QSerialPort *serial = new QSerialPort();
    serial->setPortName("/dev/tty.usbserial-AM01P46A");

    QTXB *xb = new QTXB(serial);
    QObject::connect(xb, SIGNAL(receivedATCommandResponse(ATCommandResponse*)), xb, SLOT(displayATCommandResponse(ATCommandResponse*)));
    QObject::connect(xb, SIGNAL(receivedModemStatus(ModemStatus*)), xb, SLOT(displayModemStatus(ModemStatus*)));
    QObject::connect(xb, SIGNAL(receivedTransmitStatus(TransmitStatus*)), xb, SLOT(displayTransmitStatus(TransmitStatus*)));
    QObject::connect(xb, SIGNAL(receivedRXIndicator(RXIndicator*)), xb, SLOT(displayRXIndicator(RXIndicator*)));
    QObject::connect(xb, SIGNAL(receivedRXIndicatorExplicit(RXIndicatorExplicit*)), xb, SLOT(displayRXIndicatorExplicit(RXIndicatorExplicit*)));
    QObject::connect(xb, SIGNAL(receivedNodeIdentificationIndicator(NodeIdentificationIndicator*)), xb, SLOT(displayNodeIdentificationIndicator(NodeIdentificationIndicator*)));
    QObject::connect(xb, SIGNAL(receivedRemoteCommandResponse(RemoteCommandResponse*)), xb, SLOT(displayRemoteCommandResponse(RemoteCommandResponse*)));

    QByteArray address = QByteArray::fromHex("0013a20040a53581");
    QString data = "Hello World";
    forever{
        xb->broadcast(data);
        //xb->readData();
        QTime dieTime= QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
    }*/

    /* E-MAIL GONDERIM KODU
     *
     * QEventLoop loop;
    QStringList list;
    list.append("turkishsoldier51@gmail.com");
    Smtp *newMail  = new Smtp("asmtp.bilkent.edu.tr","c_ertug@ug.bilkent.edu.tr","****","c_ertug@ug.bilkent.edu.tr",list,"EMERGENCY!!","We need to have an ambulance in C building, Bilkent University East Campus, ANKARA");
    //Smtp *smtp = new Smtp(serverName, username, password, from, to, subject, body);
    QObject::connect(newMail, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //delete newMail;

    ui->TA->append("E-mail was sent to the hospital.");
    ui->TA->setTextColor("#00FF00");
    ui->TA->append("✓ \n");
    ui->TA->setTextColor("#000000");

    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
