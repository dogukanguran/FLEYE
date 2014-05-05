#include "coordination.h"

Coordination::Coordination()
{
}

Coordination::Coordination(float x, float y)
{
    this->x_ = x;
    this->y_ = y;
}

float Coordination::getX()
{
    return x_;
}

void Coordination::setX(float x)
{
    this->x_ = x;
}

float Coordination::getY()
{
    return y_;
}

void Coordination::setY(float y)
{
    this->y_ = y;
}

QString Coordination::getCity()
{
    return hqCity_;
}

void Coordination::setCity(QString hqCity)
{
    hqCity_ = hqCity;
}
