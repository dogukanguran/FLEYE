#include "mainwindow.h"
#include "login.h"
#include "database.h"
#include <QApplication>
#include <QtSql>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include "xlsxdocument.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Login l;
    l.show();

    /* Excel'de dokuman oluşturup kaydetme kodu
     *
     * QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!");
    xlsx.saveAs("/Users/Cem/Desktop/Test.xlsx");*/

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

    /*Database *ddd = new Database();
    ddd->openDBConnection();
    ddd->closeDBConnection();*/



    return a.exec();
}
