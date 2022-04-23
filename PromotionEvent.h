#pragma once
#include "Event.h"

using namespace std;

class PromotionEvent :
    public Event
{
    int Time, ID, ExtraCost;

public:
    PromotionEvent(string time, int id, int extra);

    void setTime(string);

    int getTime() const;

    void Execute();
};

