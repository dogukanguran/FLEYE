/*
 * This class will help us to get and set coordinates so that we can reach elements from any class.
 *
 */

#ifndef COORDINATION_H
#define COORDINATION_H

class Coordination
{
private:
    float x;
    float y;
public:
    Coordination();
    Coordination(float,float);
    float getX();
    void setX(float);
    float getY();
    void setY(float);
};

#endif // COORDINATION_H
