#include "database.h"
#include "mainwindow.h"
#include "login.h"
#include "server.h"
#include "xlsxdocument.h"
#include "coordination.h"

#include <QApplication>
#include <QDebug>

#include <QtSql>
#include <QtDebug>
#include <QtSql/QSqlDatabase>

Coordination coordination;
Server server;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Start with login screen.
    Login l;
    l.show();


    //coordination.setX(23.44444);
    //coordination.setY(12.12323);

    //Server server;

    //server.start("127.0.0.1", 1235);



    return a.exec();
}
