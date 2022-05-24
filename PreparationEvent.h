#pragma once
#ifndef PREPARATION_EVENT_H
#define PREPARATION_EVENT_H

#include "Event.h"

class PreparationEvent :
    public Event
{
private:
    CargoType cargotype;
    int Time, ID, Dist, LoadingTime, Cost;
public:
    PreparationEvent(char type, string time, int id, int dist, int LT, int cost);

    void setCargoType(char);

    void setTime(string);

    int getTime() const;

    void Execute(Company*);

	~PreparationEvent ();
};


#endif