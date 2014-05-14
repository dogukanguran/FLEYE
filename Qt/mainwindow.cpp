#include "coordination.h"
#include "database.h"
#include "login.h"
#include "mainwindow.h"
#include "math.h"
#include "server.h"
#include "signal.h"
#include "xlsxdocument.h"
#include "ui_mainwindow.h"

#define d2r 0.0174532925199433

Login *login;
extern Coordination coordination;

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

    /*
     * This part of code for the Series 2 Xbee modules. However, we have got Series 1 Xbee. Coder of the API says that 'this API should work with almost every Xbee. However, we could not get it working.
     *
    QSerialPort *serial = new QSerialPort();
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
        //xb->broadcast(data);
        xb->readData();
        QTime dieTime= QTime::currentTime().addMSecs(500);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }*/


    // Since I am not able to get Xbee data, I am creating my Signal for demonstration.
    // And I manually give a coordinate
    Signal s;
    QString coordinationString;
    coordinationString = "39.87130;32.76402";

    //When we detect a coordination, we will check to validate the signal is for us
    //forever {
    if(s.checkSignal(coordinationString)==true)
    {
        ui->OnOff->setStyleSheet("QLabel { background-color: red } ");
        ui->OnOff->setText("DANGER!");

        //first we split that coordinate into two part
        QStringList coordinates = coordinationString.split(";");

        // then we get the location of headquarter from database
        QSqlQuery query;
        QString hqCity = "Ankara";
        query.prepare("SELECT * FROM headquarter WHERE hqCity = :city ");
        query.bindValue(":city",hqCity);
        query.exec();
        query.next();
        float hqX = query.value(3).toFloat();
        float hqY = query.value(4).toFloat();

        // then using haversine_km function we are calculating the distance between two gps coordinates in kilometers.
        // same formula applies for finding swimmer's distance from headquarter.
        char distance[32];
        double fleyeDistanceKm = haversine_km(coordinates[0].toDouble(),coordinates[1].toDouble(),hqX,hqY);

        //converting kilometers to meters
        sprintf(distance,"%.2f",fleyeDistanceKm*1000);
        QString fleyeDistanceText;
        fleyeDistanceText.append(distance);
        fleyeDistanceText.append(" m.");
        //then display it on the UI
        ui->FLEYEDistanceText->setText(fleyeDistanceText);

        //if distance is greater than 100 meters then paint it with red else use green
        if(fleyeDistanceKm * 1000 > 100)
        {
            ui->FLEYEDistanceText->setStyleSheet("QLabel { background-color: red } ");
        }
        else
        {
            ui->FLEYEDistanceText->setStyleSheet("QLabel { background-color: green } ");
        }
    }
    else
    {

    }
    //}


    /*
    QSqlQuery queryIntro;
    queryIntro.prepare("SELECT * from login WHERE username = :username");
    queryIntro.bindValue(":username",username);
    while(queryIntro.exec())
    {
        ui->IntroText->setText("Hi, "+queryIntro.value(1).toString());
    }*/

    //this piece of code fills combobox of lifeguard
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

    //this piece of code fills swimmer's combobox
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

    QUrl url;
    QString urlString="";

    QSqlQuery queryHq;
    queryHq.prepare("SELECT * FROM headquarter");
    queryHq.exec();
    urlString.append("http://maps.googleapis.com/maps/api/staticmap?center=");

    url.setUrl(urlString);
    ui->webView->setUrl(url);
    while(queryHq.next()) {
        QString hqCountry = "Country: ";
        hqCountry.append(queryHq.value(1).toString());
        QString hqCity = queryHq.value(2).toString();
        QString hqDirectionX = queryHq.value(5).toString();
        QString hqDirectionY = queryHq.value(6).toString();
        QString hqX = queryHq.value(3).toString();
        QString hqY = queryHq.value(4).toString();
        QString altitude = queryHq.value(7).toString();
        QString hqName = queryHq.value(8).toString();
        hqCountry.append("\nHeadquarter Name: "+hqName+"\nHeadquarter City: "+hqCity+"\nCoordinates:\nX: "+hqDirectionX+hqX+"\nY: "+hqDirectionY+hqY+"\nAltitude: "+altitude+" meters.");
        ui->HqTextEdit->setText(hqCountry);
        urlString.append(hqX);
        urlString.append(",");
        urlString.append(hqY);
    }

    urlString.append("&zoom=18&size=800x400&maptype=satellite&sensor=true");
    ui->webView->setUrl(urlString);

}





/*float MainWindow::processNewData(QByteArray &data)
{
    bool ok;
    int sign = 1;
    QByteArray array(_array.toHex());
    array = QByteArray::number(array.toLongLong(&ok,16),2); //convert hex to binary -you don't need this since your incoming data is binary
    if(array.length()==32)
    {
        if(array.at(0)=='1') sign =-1; // if bit 0 is 1 number is negative
        array.remove(0,1); // remove sign bit
    }
    QByteArray fraction =array.right(23); //get the fractional part
    double mantissa = 0;
    for(int i=0;i<fraction.length();i++) // iterate through the array to claculate the fraction as a decimal.
        if(fraction.at(i)=='1') mantissa += 1.0/(pow(2,i+1));
    int exponent = array.left(array.length()-23).toLongLong(&ok,2)-127; //claculate the exponent
    return (sign*pow(2,exponent)*(mantissa+1.0));
}*/

MainWindow::~MainWindow()
{
    delete ui;
}
//when take report by lifeguard button is clicked, execute the necessary SQLs and save the excel file to the desktop
void MainWindow::on_TakeReportByLifeGuard_clicked()
{
    QString lifeGuardName="";
    lifeGuardName.append(ui->comboBoxLifeGuard->currentText());
    if( lifeGuardName.compare(lifeGuardName,"Select a lifeguard",Qt::CaseInsensitive) == 0 )
    {
        ui->reportByLifeGuardText->setText("Please select a lifeguard.");
    }
    else
    {
        //when we call write function we supply the name of cell to write on and what will be written in that cell.
        QXlsx::Document xlsx;
        //first we will define the names of columns
        xlsx.write("A1", "SSN");
        xlsx.write("B1", "Lifeguard No");
        xlsx.write("C1", "Address");

        //we take the names from combobox that user selected a name and we split by name and surname
        QStringList list = lifeGuardName.split(QRegExp("\\s"));
        QString name="",surname="";
        name.append(list[0]);
        surname.append(list[1]);

        //we query that name and surname
        QSqlQuery query;
        query.prepare("SELECT * FROM lifeguard WHERE name = :name AND surname = :surname");
        query.bindValue(":name",name);
        query.bindValue(":surname",surname);
        query.exec();

        //if we have return row then we write it to the cell
        while(query.next()) {
            xlsx.write("A2",query.value(0).toInt());
            xlsx.write("B2",query.value(2).toInt());
            xlsx.write("C2",query.value(4).toString());
        }


        //we save that xlsx file on to desktop
        xlsx.saveAs("/Users/Cem/Desktop/Lifeguard_Report.xlsx");
        ui->reportByLifeGuardText->setText("Saved on your desktop.");
    }
}
//when take report by swimmer button is clicked, execute the necessary SQL's and save the excel file to the desktop
void MainWindow::on_TakeReportBySwimmer_clicked()
{
    QString swimmerName="";
    swimmerName.append(ui->comboBoxSwimmer->currentText());
    if( swimmerName.compare( swimmerName,"Select a Swimmer",Qt::CaseInsensitive) == 0 )
    {
        ui->reportBySwimmerText->setText("Please select a swimmer.");
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
//when take report by date button is clicked, execute the necessary SQL's and save the excel file to the desktop
void MainWindow::on_TakeReportByDate_clicked()
{
    QXlsx::Document xlsx;
    xlsx.write("A1", "Event ID");
    xlsx.write("B1", "Swimmer SSN");
    xlsx.write("C1", "Event Date");
    xlsx.write("D1", "Event Location");
    xlsx.write("E1", "FLEYE ID");

    //in that case we get the start and end date from user
    QString dateStartString,dateEndString;
    dateStartString = ui->ByDateStart->date().toString(Qt::ISODate);
    dateEndString = ui->ByDateEnd->date().toString(Qt::ISODate);


    QSqlQuery query;
    query.prepare("SELECT * FROM event WHERE eventDate BETWEEN :dateStart AND :dateEnd");
    query.bindValue(":dateStart",dateStartString);
    query.bindValue(":dateEnd",dateEndString);
    query.exec();

    //we use for loop because we may have more than one row in result set
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
//close the user's frame
void MainWindow::on_logoutButton_clicked()
{
    this->close();
    login = new Login(this);
    login->setPasswordEditBlank();
    login->setUsernameEditBlank();
    login->show();
    login->QWidget::setWindowTitle("Login");
}

double MainWindow::haversine_km(double lat1, double long1, double lat2, double long2)
{
    double dlong = (long2 - long1) * d2r;
    double dlat = (lat2 - lat1) * d2r;
    double a = pow(sin(dlat/2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong/2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6367 * c;

    return d;
}
