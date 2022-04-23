#pragma once
#include "cargo.h"
#include <string>

using namespace std;

class Event
{
private:
	int ET, ID;	// ET: event time
	int Dist, LT, Cost;
	CargoType TYP;
public:
	Event();

	virtual void Execute () = 0;
    bool ifTimeCome(int);
	~Event();
};
