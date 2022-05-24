#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "cargo.h"
#include "Company.h"
#include <string>

using namespace std;

class Company;

class Event	// The base class of all events (cancellation, preparation, promotion)
{
private:
	int ET, ID;	// ET: event time
	int Dist, LT, Cost;	// LT: Loading Time
	CargoType TYP;
public:
	Event();

	virtual void Execute (Company*) = 0;
    bool ifTimeCome(int);
	virtual int getTime () const = 0;

	~Event();
};

#endif