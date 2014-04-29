/*
 * This class will include all basic open and close connection methods and also basic query methods in it.
 */

#ifndef DATABASE_H
#define DATABASE_H
#include "iostream"
#include "QDate"
#include <QtSql>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QDebug>

using namespace std;

class Database
{
private:
    QSqlDatabase db_ = QSqlDatabase::addDatabase("QMYSQL"); // DB Driver
    int SSN_;
    string name_;
    string surname_;
    int telNo_;
    QDate eventDate_;
    string eventLocation_;
    int SSNOfLifeguard_;
    string nameOfLifeguard_;
public:
    Database();
    void openDBConnection();
    void closeDBConnection();
    bool addSwimmer(int,QString,QString,int,QDate,QString,QString,int);
    bool updateSwimmer(int,QString,QString,int,QString,int);
    bool swimmerQuery(int);
    bool swimmerQuery(QDate,QDate);
    bool lifeguardQuery(int);
    int getSSNSwimmer();
    void setSSNSwimmer(int);
    string getName();
    void setName(string);
    string getSurname();
    void setSurname(string);
    int getTelNo();
    void setTelNo(int);
    QDate getEventDate();
    void setEventDate(QDate);
    string getEventLocation();
    void setEventLocation(string);
    int getSSNOfLifeguard();
    void setSSNOfLifeguard(int);
    string getNameOfLifeguard();
    void setNameOfLifeguard(string);

};

#endif // DATABASE_H
