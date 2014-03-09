
#include "mainwindow.h"
#include "ui_mainwindow.h"


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
