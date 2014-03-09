#include "mainwindow.h"
#include "database.h"
#include <QApplication>
#include <QtSql>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // DB Driver

    db.setHostName("localhost");
    db.setDatabaseName("FLEYE");
    db.setPort (3306);
    db.setUserName("root");
    db.setPassword("root");

    // opens connection
    if(db.open())
    {
        qDebug() << "Opened!";
        qDebug() << "Closing...";
        db.close();
    }
    else
    {
      qDebug() << "Error = " << db.lastError().text();
    }*/

    Database *ddd = new Database();
    ddd->openDBConnection();
    ddd->closeDBConnection();



    return a.exec();
}
