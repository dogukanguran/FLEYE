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
