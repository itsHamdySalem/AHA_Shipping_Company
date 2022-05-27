#pragma once
#ifndef CARGO_H
#define CARGO_H
#include "truck.h"
#include "Types.h"

class truck;

class cargo
{
private:
	int ReadyTime, LoadingTime, ID, Dist, Cost, DeliveredTime, waitTime;
    truck* truckDeliveredID;
	CargoType TYP;
	CargoStatus Status;
public:
	cargo(int RT, int LT, int id, int dist, int cost, CargoType type, CargoStatus status);

	void setReadyTime (int);
	void setLoadingTime(int);
	void setID (int);
	void setDistance(int);
	void setCost (int);
	void setType(CargoType);
	void setStatus(CargoStatus);
	void setDeliveredTime(int t);
    void setWaitTime(int t);
    void setTruckDelivered(truck*);

	int getReadyTime() const;
	int getLoadingTime() const;
	int getID() const;
	int getDist() const;
	int getCost() const;
    CargoType getType () const;
	CargoStatus getStatus () const;
	int getDeliveredTime() const;
    int getWaitTime() const;
    truck* getTruckDelivered() const;

	~cargo();
};

#endif