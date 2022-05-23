#pragma once
#ifndef TRUCK_H
#define TRUCK_H

#include "Types.h"
#include "list.h"
class truck
{
private:
	int TC, MT, Speed, DI, DJ;	// TC: Truck Capacity, MT: Maintenance Time, DI: Delivey Interval, DJ: Delivery Journeys
	TruckType TYP;	// TYP: type of truck
    TruckStatus STATUS;
	list<cargo*> cargosInside;

public:
	truck();
	truck(int tc, int mt, int speed, int dj, TruckType type, TruckStatus);
	
	void setCapacity (int tc);
	void setMaintenanceTime (int mt);
	void setSpeed (int speed);
	void setDeliveryInterval (int di);
	void setType (TruckType type);
    void setStatus(TruckStatus);
    void setNumberOfJournies(int);

	void addCargo(cargo*);

	int getCapacity ();
	int getMaintenanceTime ();
	int getSpeed ();
	int getDeliveryInterval ();
	TruckType getType ();

	~truck();
};

#endif