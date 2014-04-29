/*
 * With this class we will get Signal from xBee and check it is meaningful.
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include "coordination.h"

class Signal
{
public:
    virtual ~Signal();
    virtual bool checkSignal(Coordination);
    virtual void getSignal();
};

#endif // SIGNAL_H
