#pragma once
#ifndef PROMOTION_EVENT_H
#define PROMOTION_EVENT_H

#include "Event.h"

class PromotionEvent :
    public Event
{
private:
    int Time, ID, ExtraCost;
public:
    PromotionEvent(string time, int id, int extra);

    void setTime(string);

    int getTime() const;

    void Execute(Company*);

	~PromotionEvent();

};

#endif