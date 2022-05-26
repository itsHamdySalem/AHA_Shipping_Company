#pragma once
#ifndef TRUCK_H
#define TRUCK_H

#include "Types.h"

class truck
{
private:
	int TruckCapacity, CheckupTime, Speed, MaxJournies, NumberOfJournies, ReadyTime, ID, totalCargos, MoveTime;	// TC: Truck Capacity, MT: Maintenance Time, DI: Delivey Interval, DJ: Delivery Journeys
	int activeTime;
    TruckType TYP;	// TYP: type of truck
    TruckStatus STATUS;
public:
	truck();
	truck(int tc, int mt, int speed, int MJ, TruckType type, TruckStatus, int ID);
	
	void setCapacity (int tc);
	void setCheckUpTime (int mt);
	void setSpeed (int speed);
	void setMaxJournies(int);
	void setReadyTime(int);
	void setType (TruckType type);
    void setStatus(TruckStatus);
    void setID(int);
    void setNumberOfJournies(int);
    void setTotalCargos(int);
    void setActiveTime(int);
    void setMoveTime(int);

	int getCapacity ();
	int getCheckUpTime ();
	int getSpeed ();
	int getMaxJournies();
	int getReadyTime();
	int getNumberOfJournies();
    int getID();
    int getTotalCargos();
    int getActiveTime();
    int getMoveTime();
	TruckType getType ();

	~truck();
};

#endif