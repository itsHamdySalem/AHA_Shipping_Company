#pragma once
#include "cargo.h"
#include "Company.h"
#include <string>

using namespace std;

class Company;

class Event
{
private:
	int ET, ID;	// ET: event time
	int Dist, LT, Cost;
	CargoType TYP;
public:
	Event();

	virtual void Execute (Company*) = 0;
    bool ifTimeCome(int);
	~Event();
};
