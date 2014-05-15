#include "coordination.h"
#include "database.h"
#include "mainwindow.h"
#include "login.h"
#include "server.h"
#include "xlsxdocument.h"


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

    return a.exec();
}
