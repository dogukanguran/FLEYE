#include "coordination.h"

Coordination::Coordination()
{
}

Coordination::Coordination(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Coordination::getX()
{
    return x;
}

void Coordination::setX(float x)
{
    this->x = x;
}

float Coordination::getY()
{
    return y;
}

void Coordination::setY(float y)
{
    this->y = y;
}
