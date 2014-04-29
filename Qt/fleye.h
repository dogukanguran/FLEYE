/*
 * With this class we will reach the important datas coming from FLEYE and we will use them on the GUI.
 */

#ifndef FLEYE_H
#define FLEYE_H
#include "QDate"
#include "coordination.h"
class FLEYE
{
private:
    int id_;
    QDate lastMaintenance_;
    double altitude_;
    bool errorExistence_;
    Coordination *fleyeCoordination_;
    Coordination *targetCoordination_;

public:
    FLEYE();
    FLEYE(int,QDate,double,bool,Coordination*,Coordination*);
    int getId();
    QDate getLastMaintenance();
    void setLastMaintenance(QDate);
    double getAltitude();
    void setAltitude(double);
    bool getErrorExistence();
    void setErrorExistence(bool);
    Coordination* getFLEYECoordination();
    void setFLEYECoordination(Coordination*);
    Coordination* getTargetCoordination();
    void setTargetCoordination(Coordination*);
};

#endif // FLEYE_H
