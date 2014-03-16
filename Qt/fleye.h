#ifndef FLEYE_H
#define FLEYE_H
#include "QDate"
#include "coordination.h"
class FLEYE
{
private:
    int id;
    QDate lastMaintenance;
    double batteryPercentage;
    bool errorExistence;
    Coordination *fleyeCoordination;
    Coordination *targetCoordination;

public:
    FLEYE();
    FLEYE(int,QDate,double,bool,Coordination*,Coordination*);
    int getId();
    QDate getLastMaintenance();
    void setLastMaintenance(QDate);
    double getBatteryPercentage();
    void setBatteryPercentage(double);
    bool getErrorExistence();
    void setErrorExistence(bool);
    Coordination* getFLEYECoordination();
    void setFLEYECoordination(Coordination*);
    Coordination* getTargetCoordination();
    void setTargetCoordination(Coordination*);
};

#endif // FLEYE_H
