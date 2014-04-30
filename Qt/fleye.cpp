#include "fleye.h"

FLEYE::FLEYE()
{
}

//constructor for FLEYE class

FLEYE::FLEYE(int id,QDate lastMaintenance,double altitude,bool errorExistence,Coordination* fleyeCoordination,Coordination* targetCoordination)
{
    this->id_ = id;
    this->lastMaintenance_ = lastMaintenance;
    this->altitude_ = altitude;
    this->errorExistence_ = errorExistence;
    this->fleyeCoordination_ = fleyeCoordination;
    this->targetCoordination_ = targetCoordination;
}

//getter and setter functions for FLEYE class

int FLEYE::getId(){
    return id_;
}

QDate FLEYE::getLastMaintenance()
{
    return lastMaintenance_;
}

void FLEYE::setLastMaintenance(QDate lastMaintenance)
{
    this->lastMaintenance_ = lastMaintenance;
}

double FLEYE::getAltitude()
{
    return altitude_;
}

void FLEYE::setAltitude(double altitude)
{
    this->altitude_ = altitude;
}

bool FLEYE::getErrorExistence()
{
    return errorExistence_;
}

void FLEYE::setErrorExistence(bool errorExistence)
{
    this->errorExistence_ = errorExistence;
}

Coordination* FLEYE::getFLEYECoordination()
{
    return fleyeCoordination_;
}

void FLEYE::setFLEYECoordination(Coordination* fleyeCoordination)
{
    this->fleyeCoordination_ = fleyeCoordination;
}

Coordination* FLEYE::getTargetCoordination()
{
    return targetCoordination_;
}

void FLEYE::setTargetCoordination(Coordination* targetCoordination)
{
    this->targetCoordination_ = targetCoordination;
}

