#pragma once
#ifndef TRUCK_H
#define TRUCK_H

#include <iostream>
using namespace std;

enum TruckType
{
	NORMAL_TRUCK,
	SPECIAL_TRUCK,
	VIP_TRUCK
};

class truck
{
private:
	int TC, MT, Speed, DI, DJ;
	TruckType TYP;
public:
	truck();
	truck(int tc, int mt, int speed, int di, TruckType type);
	
	void setCapacity (int tc);
	void setMaintenanceTime (int mt);
	void setSpeed (int speed);
	void setDeliveryInterval (int di);
	void setType (TruckType type);

	int getCapacity ();
	int getMaintenanceTime ();
	int getSpeed ();
	int getDeliveryInterval ();
	TruckType getType ();

	~truck();
};

#endif
