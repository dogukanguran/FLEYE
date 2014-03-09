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
