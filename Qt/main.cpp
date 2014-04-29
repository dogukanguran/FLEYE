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
    // Start with login screen.
    Login l;
    l.show();

    return a.exec();
}
