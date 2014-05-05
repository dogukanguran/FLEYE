/*
 * With this class we will get Signal from xBee and check it is meaningful.
 */

#ifndef SIGNAL_H
#define SIGNAL_H
#define NORTH N
#define EAST E
#define WEST W
#define SOUTH S

#include "coordination.h"
#include <QtCore>


class Signal
{
public:
    Signal();
    ~Signal();
    bool checkSignal(QString);
    void getSignal();
};

#endif // SIGNAL_H
