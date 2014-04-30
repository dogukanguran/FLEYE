#include "database.h"

Database::Database()
{

}

// opens database connection with given credentials
void Database::openDBConnection(){

    db_.setHostName("localhost");
    db_.setDatabaseName("FLEYE");
    db_.setPort (3306);
    db_.setUserName("root");
    db_.setPassword("root");

    // opens connection
    if(db_.open())
    {

    }
    else
    {
      qDebug() << "Error = " << db_.lastError().text();
    }
}

//closes database connection
void Database::closeDBConnection()
{
    db_.close();
    qDebug() << "Database connection closed.";
}

// add swimmer on to database and returns TRUE or FALSE to inform user
bool Database::addSwimmer(int SSN, QString name, QString surname, int telNo, QDate eventDate, QString eventLocation, QString nameOfLifeguard, int SSNOfLifeguard)
{
    // this function adds new swimmer to the database.
    bool result = false;
    QSqlQuery query;
    query.prepare("INSERT INTO swimmer VALUES(:ssn,:name,:surname,:telNo,:eventDate,:eventLocation,:nameOfLifeguard,:SSNOfLifeguard)");
    query.bindValue(":SSN",SSN);
    query.bindValue(":name",name);
    query.bindValue(":surname",surname);
    query.bindValue(":telNo",telNo);
    query.bindValue(":eventDate",eventDate);
    query.bindValue(":eventLocatio",eventLocation);
    query.bindValue(":nameOfLifeguard",nameOfLifeguard);
    query.bindValue(":SSNOfLifeguard",SSNOfLifeguard);
    result = query.exec();
    if(result)
    {
        result = true;
    }

    return result;
}

//function for updating swimmer
bool Database::updateSwimmer(int SSN, QString name, QString surname, int telNo, QString eventLocation, int SSNOfLifeguard)
{
    //this function updates existing swimmer.
    bool result = false;
    QSqlQuery query;
    query.prepare("UPDATE swimmer SET Name = :name, Surname = :surname, telNo = :telNo, eventLocation = :eventLocation, SSNOfLifeguard= :SSNOfLifeguard, SSN = :SSN");
    query.bindValue(":SSN",SSN);
    query.bindValue(":name",name);
    query.bindValue(":surname",surname);
    query.bindValue(":telNo",telNo);
    query.bindValue(":eventLocatio",eventLocation);
    query.bindValue(":SSNOfLifeguard",SSNOfLifeguard);
    result = query.exec();
    if(result)
    {
        result = true;
    }

    return result;
}

// queries swimmer by his/her SSN

bool Database::swimmerQuery(int SSN)
{
    //this function queries swimmer by its SSN
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM swimmer WHERE SSN = :SSN");
    query.bindValue(":SSN",SSN);
    result = query.exec();
    if(result)
    {
        result = true;
    }

    return result;
}

//queries swimmer by his/her rescue date

bool Database::swimmerQuery(QDate date1, QDate date2)
{
    //This function queries swimmer by rescuing date
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM swimmer WHERE eventDate BETWEEN :date1 and :date2");
    query.bindValue(":date1",date1);
    query.bindValue(":date2",date2);
    result = query.exec();
    if(result)
    {
        result = true;
    }

    return result;
}

//queries lifeguards by his/her SSN

bool Database::lifeguardQuery(int SSN)
{
    //This function queries by lifeguard's SSN
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM swimmer WHERE SSNOfLifeguard=:SSN");
    query.bindValue(":SSN",SSN);
    result = query.exec();
    if(result)
    {
        result = true;
    }

    return result;
}


// getter and setter functions for members.

int Database::getSSNSwimmer()
{
    return SSN_;
}

void Database::setSSNSwimmer(int SSN)
{
    this->SSN_ = SSN;
}

string Database::getName()
{
    return name_;
}

void Database::setName(string name)
{
    this->name_ = name;
}

string Database::getSurname()
{
    return surname_;
}

void Database::setSurname(string surname)
{
    this->surname_ = surname;
}

int Database::getTelNo()
{
    return telNo_;
}

void Database::setTelNo(int telNo)
{
    this->telNo_ = telNo;
}

QDate Database::getEventDate()
{
    return eventDate_;
}

void Database::setEventDate(QDate eventDate)
{
    this->eventDate_ = eventDate;
}

string Database::getEventLocation()
{
    return eventLocation_;
}

void Database::setEventLocation(string eventLocation)
{
    this->eventLocation_ = eventLocation;
}

int Database::getSSNOfLifeguard()
{
    return SSNOfLifeguard_;
}

void Database::setSSNOfLifeguard(int SSNOfLifeguard)
{
    this->SSNOfLifeguard_ = SSNOfLifeguard;
}

string Database::getNameOfLifeguard()
{
    return nameOfLifeguard_;
}

void Database::setNameOfLifeguard(string nameOfLifeguard)
{
    this->nameOfLifeguard_ = nameOfLifeguard;
}
