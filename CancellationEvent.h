#pragma once
#include "Event.h"

class CancellationEvent :
    public Event
{
    int Time, ID;

public:
    CancellationEvent(string t, int id);

    void setTime(string t);

    int getTime() const;

    int getID() const;

    void Execute(Company*);
};

