#pragma once
#ifndef CARGO_H
#define CARGO_H

#include "Types.h"

class cargo
{
private:
	int ReadyTime, LoadingTime, ID, Dist, Cost, DeliveredTime;
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

	int getReadyTime() const;
	int getLoadingTime() const;
	int getID() const;
	int getDist() const;
	int getCost() const;
    CargoType getType () const;
	CargoStatus getStatus () const;
	int getDeliveredTime() const;

	~cargo();
};

#endif