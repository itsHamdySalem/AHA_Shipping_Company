#pragma once

#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;

class Time
{
private:
	int day, hour;
public:
	Time();

	void setDay (int d);
	void setHour (int h);

	int getDay ();
	int getHour ();

	int CalcTime ();

	~Time();
};




#endif