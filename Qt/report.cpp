#include "report.h"

Report::Report()
{
}

//creates report by swimmer's SSN
bool Report::createReportSwimmer(int num)
{
    bool returnCode = false;
    qDebug() << "Create Report by Swimmer is executing..!";
    QSqlQuery query;
    query.prepare("SELECT * FROM swimmer WHERE SSN = :SSN");
    query.bindValue(":SSN",num);
    returnCode = query.exec();
    while(query.next()) {
        QString firstName = query.value(1).toString();
        QString secondName = query.value(2).toString();
        qDebug() << firstName << secondName;
        returnCode = true ;
    }
    return returnCode;
}

//creates reports by lifeguard's ID
bool Report::createReportLifeguard(int num)
{
    bool returnCode = false;
    qDebug() << "Create Report by Lifeguard is executing..!";
    QSqlQuery query;
    query.prepare("SELECT * FROM event WHERE Responsible_Lifeguard = :num");
    query.bindValue(":num",num);
    returnCode = query.exec();
    while(query.next()) {
        QString firstName = query.value(1).toString();
        QString secondName = query.value(2).toString();
        qDebug() << firstName << secondName;
        returnCode = true;
    }
    return returnCode;
}

//creates report by two dates entered by user and shows events that happened between two date
bool Report::createReportDate(QDate dateStart,QDate dateEnd)
{
    bool returnCode = false;
    QString dateStartSt,dateEndSt;
    dateStartSt = dateStart.toString("dd.MM.yyyy");
    dateEndSt = dateEnd.toString("dd.MM.yyyy");
    qDebug() << "Create Report by Date is executing..!";
    QSqlQuery query;
    query.prepare("SELECT * FROM event WHERE Event_Date BETWEEN :date1 AND :date2");
    query.bindValue(":date1",dateStart);
    query.bindValue(":date2",dateEnd);
    returnCode = query.exec();
    while(query.next()) {
        QString firstName = query.value(1).toString();
        QString secondName = query.value(2).toString();
        qDebug() << firstName << secondName;
        returnCode = true;
    }
    return returnCode;
}

