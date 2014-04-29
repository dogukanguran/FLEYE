/*
 * This class will help us to create Excel files from database.
 */

#ifndef REPORT_H
#define REPORT_H

#include "database.h"
#include "iostream"

using namespace std;

class Report
{
private:
    int reportId_;
    string reportType_;
    Database reportDatabase_;
public:
    Report();
    bool createReportSwimmer(int);
    bool createReportLifeguard(int);
    bool createReportDate(QDate,QDate);
};

#endif // REPORT_H
