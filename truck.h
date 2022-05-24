#pragma once
#ifndef TRUCK_H
#define TRUCK_H

#include "Types.h"

class truck
{
private:
	int TruckCapacity, CheckupTime, Speed, MaxJournies, NumberOfJournies, ReadyTime;	// TC: Truck Capacity, MT: Maintenance Time, DI: Delivey Interval, DJ: Delivery Journeys
	TruckType TYP;	// TYP: type of truck
    TruckStatus STATUS;
public:
	truck();
	truck(int tc, int mt, int speed, int MJ, TruckType type, TruckStatus);
	
	void setCapacity (int tc);
	void setCheckUpTime (int mt);
	void setSpeed (int speed);
	void setMaxJournies(int);
	void setReadyTime(int);
	void setType (TruckType type);
    void setStatus(TruckStatus);

	int getCapacity ();
	int getCheckUpTime ();
	int getSpeed ();
	int getMaxJournies();
	int getReadyTime();
	int getNumberOfJournies();
	TruckType getType ();

	~truck();
};

#endif