#include "fleye.h"

FLEYE::FLEYE()
{
}

FLEYE::FLEYE(int id,QDate lastMaintenance,double altitude,bool errorExistence,Coordination* fleyeCoordination,Coordination* targetCoordination)
{
    this->id = id;
    this->lastMaintenance = lastMaintenance;
    this->altitude = altitude;
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

double FLEYE::getAltitude()
{
    return altitude;
}

void FLEYE::setAltitude(double altitude)
{
    this->altitude = altitude;
}

bool FLEYE::getErrorExistence()
{
    return errorExistence;
}

void FLEYE::setErrorExistence(bool errorExistence)
{
    this->errorExistence = errorExistence;
}

Coordination* FLEYE::getFLEYECoordination()
{
    return fleyeCoordination;
}

void FLEYE::setFLEYECoordination(Coordination* fleyeCoordination)
{
    this->fleyeCoordination = fleyeCoordination;
}

Coordination* FLEYE::getTargetCoordination()
{
    return targetCoordination;
}

void FLEYE::setTargetCoordination(Coordination* targetCoordination)
{
    this->targetCoordination = targetCoordination;
}

