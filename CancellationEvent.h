#pragma once
#ifndef	CANCELLATION_EVENT_H
#define	CANCELLATION_EVENT_H

#include "Event.h"

class CancellationEvent :
    public Event
{
private:
    int Time, ID;
public:
    CancellationEvent(string t, int id);

    void setTime(string t);

    int getTime() const;

    int getID() const;

    void Execute(Company*);
};


#endif