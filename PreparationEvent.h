#pragma once
#include "Event.h"

using namespace std;

class PreparationEvent :
    public Event
{
    CargoType cargotype;
    int Time, ID, Dist, LoadingTime, Cost;

public:

    PreparationEvent(char type, string time, int id, int dist, int LT, int cost);

    void setCargoType(char);

    void setTime(string);

    int getTime() const;

    void Execute();

};

