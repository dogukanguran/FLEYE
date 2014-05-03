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

Coordination c;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Start with login screen.
    //Login l;
    //l.show();

    c.setX(23.44444);
    c.setY(12.12323);
    Server server;

    server.start("127.0.0.1", 8888);



    return a.exec();
}
