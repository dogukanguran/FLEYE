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
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // DB Driver
    int SSN;
    string name;
    string surname;
    int telNo;
    QDate eventDate;
    string eventLocation;
    int SSNOfLifeguard;
    string nameOfLifeguard;
public:
    Database();
    void openDBConnection();
    void closeDBConnection();
    bool addSwimmer(int,string,string,int,QDate,string,string,int);
    bool updateSwimmer(int,string,string,int,string,int);
    bool swimmerQuery(int);
    bool swimmerQuery(QDate,QDate);
    bool lifeguardQuery(int);
    int getSSNSwimmer();
    void setSSNSwimmer();
    string getName();
    void setName(string);
    string getSurname();
    void setSurname(string);
    void getTelNo();
    int setTelNo(int);
    QDate getEventDate();
    void setEventDate(QDate);
    string getEventLocation();
    void setEventLocation(string);
    int getSSNOfLifeguard();
    void setSSNOfLifeguard(int);
    string getNameOfLifeguard();
    void setNameOfLifeguard();

};

#endif // DATABASE_H
