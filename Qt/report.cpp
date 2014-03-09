#include "report.h"

Report::Report()
{
}

bool Report::createReportSwimmer(int num)
{
    bool returnCode = FALSE;
    qDebug() << "Create Report by Swimmer is executing..!";
    QSqlQuery query;
    query.exec("SELECT * FROM swimmer WHERE SSN ="+ num);
    while(query.next()) {
        QString firstName = query.value(1).toString();
        QString secondName = query.value(2).toString();
        qDebug() << firstName << secondName;
        returnCode = TRUE ;
    }
    return returnCode;
}

bool Report::createReportLifeguard(int num)
{
    bool returnCode = FALSE;
    qDebug() << "Create Report by Lifeguard is executing..!";
    QSqlQuery query;
    query.exec("SELECT * FROM event WHERE Responsible_Lifeguard ="+num);
    while(query.next()) {
        QString firstName = query.value(1).toString();
        QString secondName = query.value(2).toString();
        qDebug() << firstName << secondName;
        returnCode = TRUE;
    }
    return returnCode;
}

bool Report::createReportDate(QDate dateStart,QDate dateEnd)
{
    bool returnCode = FALSE;
    string dateStartSt,dateEndSt;
    dateStartSt = QVariant::toString(dateStart);
    dateEndSt = QVariant::toString(dateEnd);
    qDebug() << "Create Report by Date is executing..!";
    QSqlQuery query;
    query.exec("SELECT * FROM event WHERE Event_Date BETWEEN '"+dateStartst+"' AND '"+dateEndSt+"'");
    while(query.next()) {
        QString firstName = query.value(1).toString();
        QString secondName = query.value(2).toString();
        qDebug() << firstName << secondName;
        returnCode = TRUE;
    }
    return returnCode;
}
