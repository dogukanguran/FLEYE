/*
 * This class will help us to create Excel files from database.
 */

#ifndef REPORT_H
#define REPORT_H
#include "iostream"
#include "database.h"
using namespace std;

class Report
{
private:
    int reportId;
    string reportType;
    Database reportDatabase;
public:
    Report();
    bool createReportSwimmer(int);
    bool createReportLifeguard(int);
    bool createReportDate(QDate,QDate);
};

#endif // REPORT_H
