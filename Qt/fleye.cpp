#include "fleye.h"

FLEYE::FLEYE()
{
}

FLEYE::FLEYE(int id,QDate lastMaintenance,double batteryPercentage,bool errorExistence,Coordination* fleyeCoordination,Coordination* targetCoordination)
{
    this->id = id;
    this->lastMaintenance = lastMaintenance;
    this->batteryPercentage = batteryPercentage;
    this->errorExistence = errorExistence;
    this->fleyeCoordination = fleyeCoordination;
    this->targetCoordination = targetCoordination;
}

int FLEYE::getId(){
    return id;
}

QDate FLEYE::getLastMaintenance()
{
    return lastMaintenance;
}

void FLEYE::setLastMaintenance(QDate lastMaintenance)
{
    this->lastMaintenance = lastMaintenance;
}

double FLEYE::getBatteryPercentage()
{
    return batteryPercentage;
}

void FLEYE::setBatteryPercentage(double batteryPercentage)
{
    this->batteryPercentage = batteryPercentage;
}

bool FLEYE::getErrorExistence()
{
    return errorExistence;
}

void FLEYE::setErrorExistence(bool errorExistence)
{
    this->errorExistence = errorExistence;
}

Coordination& FLEYE::getFLEYECoordination()
{
    return fleyeCoordination;
}

void FLEYE::setFLEYECoordination(Coordination* fleyeCoordination)
{
    this->fleyeCoordination = fleyeCoordination;
}

Coordination& FLEYE::getTargetCoordination()
{
    return targetCoordination;
}

void FLEYE::setTargetCoordination(Coordination* targetCoordination)
{
    this->targetCoordination = targetCoordination;
}
