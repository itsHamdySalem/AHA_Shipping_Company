#pragma once
#include "Event.h"
class CancellationEvent :
    public Event
{
    int Time, ID;

public:
    CancellationEvent(string, int);

    void setTime(string);

    int getTime() const;

    int getID() const;

    void Excute();
};

