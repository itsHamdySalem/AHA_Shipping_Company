#pragma once
#ifndef TRUCK_H
#define TRUCK_H
#include "Types.h"

class truck
{
private:
	int TC, MT, Speed, DI, DJ;
    int numberOfJournies;
	TruckType TYP;
    TruckStatus STATUS;
public:
	truck();
	truck(int tc, int mt, int speed, int numberOfJournies, TruckType type, TruckStatus);
	
	void setCapacity (int tc);
	void setMaintenanceTime (int mt);
	void setSpeed (int speed);
	void setDeliveryInterval (int di);
	void setType (TruckType type);
    void setStatus(TruckStatus);
    void setNumberOfJournies(int);
	int getCapacity ();
	int getMaintenanceTime ();
	int getSpeed ();
	int getDeliveryInterval ();
	TruckType getType ();

	~truck();
};

#endif
