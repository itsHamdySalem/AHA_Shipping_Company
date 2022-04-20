#include "Time.h"

Time::Time()
{
	day = hour = 0;
}

void Time::setDay (int d)
{
	day = (d > 0)? d : 0;
}

void Time::setHour (int h)
{
	hour = (h > 0)? h : 0;
}

int Time::getDay ()
{
	return day;
}

int Time::getHour ()
{
	return hour;
}

int Time::CalcTime ()
{
	return day*24 + hour;
}

Time::~Time()
{
}




