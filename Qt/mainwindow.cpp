
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtxb.h"
#include <QtSerialPort/QSerialPort>
#include "database.h"
#include "xlsxdocument.h"


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


    QSqlQuery query;
    query.prepare("SELECT name,surname FROM lifeguard");
    query.exec();
    ui->comboBoxLifeGuard->addItem("Select a lifeguard");
    while(query.next()) {
        QString name = query.value(0).toString();
        QString surname = query.value(1).toString();
        name.append(" "+surname);
        ui->comboBoxLifeGuard->addItem(name);
    }

    QSqlQuery query2;
    query2.prepare("SELECT name,surname FROM swimmer");
    query2.exec();
    ui->comboBoxSwimmer->addItem("Select a lifeguard");
    while(query2.next()) {
        QString name = query2.value(0).toString();
        QString surname = query2.value(1).toString();
        name.append(" "+surname);
        ui->comboBoxSwimmer->addItem(name);
    }

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

    QString data = "cem";
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

void MainWindow::on_TakeReportByLifeGuard_clicked()
{
    QString lifeGuardName="";
    lifeGuardName.append(ui->comboBoxLifeGuard->currentText());
    if( lifeGuardName.compare(lifeGuardName,"Select a lifeguard",Qt::CaseInsensitive) == 0 )
    {

    }
    else
    {
        QXlsx::Document xlsx;
        xlsx.write("A1", "SSN");
        xlsx.write("B1", "Lifeguard No");
        xlsx.write("C1", "Address");

        QStringList list = lifeGuardName.split(QRegExp("\\s"));
        QString name="",surname="";
        name.append(list[0]);
        surname.append(list[1]);

        QSqlQuery query;
        query.prepare("SELECT * FROM lifeguard WHERE name = :name AND surname = :surname");
        query.bindValue(":name",name);
        query.bindValue(":surname",surname);
        query.exec();

        while(query.next()) {
            xlsx.write("A2",query.value(0).toInt());
            xlsx.write("B2",query.value(2).toInt());
            xlsx.write("C2",query.value(4).toString());
        }

        xlsx.saveAs("/Users/Cem/Desktop/Lifeguard_Report.xlsx");
        ui->reportByLifeGuardText->setText("Saved on your desktop.");
    }
}

void MainWindow::on_TakeReportBySwimmer_clicked()
{
    QString swimmerName="";
    swimmerName.append(ui->comboBoxSwimmer->currentText());
    if( swimmerName.compare( swimmerName,"Select a lifeguard",Qt::CaseInsensitive) == 0 )
    {

    }
    else
    {
        QXlsx::Document xlsx;
        xlsx.write("A1", "SSN");
        xlsx.write("B1", "Name");
        xlsx.write("C1", "Surname");
        xlsx.write("D1", "Telephone No");
        xlsx.write("E1", "Address");

        QStringList list = swimmerName.split(QRegExp("\\s"));
        QString name="",surname="";
        name.append(list[0]);
        surname.append(list[1]);

        QSqlQuery query;
        query.prepare("SELECT * FROM swimmer WHERE name = :name AND surname = :surname");
        query.bindValue(":name",name);
        query.bindValue(":surname",surname);
        query.exec();

        while(query.next()) {
            xlsx.write("A2",query.value(0).toInt());
            xlsx.write("B2",query.value(1).toString());
            xlsx.write("C2",query.value(2).toString());
            xlsx.write("D2",query.value(3).toInt());
            xlsx.write("E2",query.value(4).toString());
        }

        xlsx.saveAs("/Users/Cem/Desktop/Swimmer_Report.xlsx");
        ui->reportBySwimmerText->setText("Saved on your desktop.");
    }
}

void MainWindow::on_TakeReportByDate_clicked()
{
    QXlsx::Document xlsx;
    xlsx.write("A1", "Event ID");
    xlsx.write("B1", "Swimmer SSN");
    xlsx.write("C1", "Event Date");
    xlsx.write("D1", "Event Location");
    xlsx.write("E1", "FLEYE ID");

    QString dateStartString,dateEndString;
    dateStartString = ui->ByDateStart->date().toString(Qt::ISODate);
    dateEndString = ui->ByDateEnd->date().toString(Qt::ISODate);


    QSqlQuery query;
    query.prepare("SELECT * FROM event WHERE eventDate BETWEEN :dateStart AND :dateEnd");
    query.bindValue(":dateStart",dateStartString);
    query.bindValue(":dateEnd",dateEndString);
    query.exec();

    while(query.next()) {
        for(int i = 0 ; i < query.size() ; i++)
        {
            QString cellA = "A";
            QString cellB = "B";
            QString cellC = "C";
            QString cellD = "D";
            QString cellE = "E";

            cellA.append(QString::number(i+2));
            cellB.append(QString::number(i+2));
            cellC.append(QString::number(i+2));
            cellD.append(QString::number(i+2));
            cellE.append(QString::number(i+2));

            xlsx.write(cellA,query.value(0).toInt());
            xlsx.write(cellB,query.value(1).toInt());
            xlsx.write(cellC,query.value(2).toString());
            xlsx.write(cellD,query.value(3).toString());
            xlsx.write(cellE,query.value(5).toInt());

            query.next();
        }
    }

    xlsx.saveAs("/Users/Cem/Desktop/ByDate_Report.xlsx");
    ui->reportByDateText->setText("Saved on your desktop.");

}
