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
        /*qDebug() << "Database connection established!";
        QSqlQuery query;
        query.exec("SELECT * FROM swimmer WHERE SSN = 1");
        while(query.next()) {
            QString firstName = query.value(1).toString();
            QString secondName = query.value(2).toString();
            qDebug() << firstName << secondName;
        }*/
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

bool Database::addSwimmer(int SSN, string name, string surname, int telNo, QDate eventDate, string eventLocation, string nameOfLifeguard, int SSNOfLifeguard)
{
    bool result=FALSE;
    QSqlQuery query;
    if(query.exec("INSERT INTO swimmer VALUES('"+SSN+"','"+name+"','"+surname+"','"+telNo+"','"+eventDate+"','"+eventLocation+"','"+nameOfLifeguard+"','"+SSNOfLifeguard+"')"))
    {
        result = TRUE;
    }

    return result;
}

bool Database::updateSwimmer(int SSN, string name, string surname, int telNo, string eventLocation, int SSNOfLifeguard)
{
    bool result = FALSE;
    QSqlQuery query;
    if(query.exec("UPDATE swimmer SET Name='"+name+"',Surname='"+surname+"',telNo='"+telNo+"',eventLocation='"+eventLocation+"',SSNOfLifeguard='"+SSNOfLifeguard+"' WHERE SSN='"+SSN+"'"))
    {
        result = TRUE;
    }

    return result;
}

bool Database::swimmerQuery(int SSN)
{
    bool result = FALSE;
    QSQLQuery query;
    if(query.exec("SELECT * FROM swimmer WHERE SSN='"+SSN+"'"))
    {
        result = TRUE;
    }

    return result;
}

bool Database::swimmerQuery(QDate date1, QDate date2)
{
    bool result = FALSE;
    QSQLQuery query;
    if(query.exec("SELECT * FROM swimmer WHERE eventDate BETWEEN '"+date1+"' and '"+date2+"'"))
    {
        result = TRUE;
    }

    return result;
}

bool Database::lifeguardQuery(int SSN)
{
    bool result = FALSE;
    QSQLQuery query;
    if(query.exec("SELECT * FROM swimmer WHERE SSNOfLifeguard='"+SSN+"'"))
    {
        result = TRUE;
    }

    return result;
}

int Database::getSSNSwimmer()
{
    return SSN;
}

void Database::setSSNSwimmer(int SSN)
{
    this->SSN = SSN;
}

string Database::getName()
{
    return name;
}

void Database::setName(string name)
{
    this->name = name;
}

string Database::getSurname()
{
    return surname;
}

void Database::setName(string surname)
{
    this->surname = surname;
}

void Database::getTelNo()
{
    return telNo;
}

int Database::setTelNo(int telNo)
{
    this->telNo = telNo;
}

QDate Database::getEventDate()
{
    return eventDate;
}

void Database::setEventDate(QDate eventDate)
{
    this->eventDate = eventDate;
}

string Database::getEventLocation()
{
    return eventLocation;
}

void Database::setEventLocation(string eventLocation)
{
    this->eventLocation = eventLocation;
}

int Database::getSSNOfLifeguard()
{
    return SSNOfLifeguard;
}

void Database::setSSNOfLifeguard(int SSNOfLifeguard)
{
    this->SSNOfLifeguard = SSNOfLifeguard;
}

string Database::getNameOfLifeguard()
{
    return nameOfLifeguard;
}

void Database::setNameOfLifeguard(string nameOfLifeguard)
{
    this->nameOfLifeguard = nameOfLifeguard;
}
