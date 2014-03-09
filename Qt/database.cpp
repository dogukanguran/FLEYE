#include "database.h"

Database::Database()
{

}

void Database::openDBConnection(){


    db.setHostName("localhost");
    db.setDatabaseName("FLEYE");
    db.setPort (3306);
    db.setUserName("root");
    db.setPassword("root");

    // opens connection
    if(db.open())
    {
        qDebug() << "Database connection established!";
        QSqlQuery query;
        query.exec("SELECT * FROM swimmer WHERE SSN = 1");
        while(query.next()) {
            QString firstName = query.value(1).toString();
            QString secondName = query.value(2).toString();
            qDebug() << firstName << secondName;
        }
    }
    else
    {
      qDebug() << "Error = " << db.lastError().text();
    }
}

void Database::closeDBConnection()
{
    db.close();
    qDebug() << "Database connection closed.";
}
