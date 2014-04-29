#include "database.h"
#include "mainwindow.h"
#include "login.h"
#include "xlsxdocument.h"

#include <QApplication>
#include <QDebug>

#include <QtSql>
#include <QtDebug>
#include <QtSql/QSqlDatabase>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Start with login screen.
    Login l;
    l.show();

    return a.exec();
}
