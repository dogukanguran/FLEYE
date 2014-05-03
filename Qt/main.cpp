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



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Start with login screen.
    //Login l;
    //l.show();

    Coordination co;
    co.setX(23.44444);
    co.setY(12.12323);
    Server server;

    server.start("192.168.2.9", 8888);



    return a.exec();
}
