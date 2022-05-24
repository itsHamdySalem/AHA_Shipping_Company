#include "cargo.h"

cargo::cargo(int rt, int lt, int id, int dist, int cost, CargoType type, CargoStatus status)
{
	setReadyTime(rt);
	setLoadingTime(lt);
	setID (id);
	setDistance(dist);
	setCost (cost);
	setType(type);
	setStatus(status);
	DeliveredTime = -1;
}

void cargo::setReadyTime(int rt)
{
	ReadyTime = (rt > 0)? rt : -1;
}
void cargo::setLoadingTime(int lt)
{
	LoadingTime = (lt > 0)? lt : -1;
}
void cargo::setID (int id)
{
	ID = (id > 0)? id : -1;
}
void cargo::setDistance(int dist)
{
	Dist = (dist > 0)? dist : -1;
}
void cargo::setDeliveredTime(int t)
{
	DeliveredTime = t;
}
void cargo::setCost (int cost)
{
	Cost = (cost > 0)? cost : -1;
}
void cargo::setType(CargoType type)
{
	TYP = type;
}
void cargo::setStatus(CargoStatus status)
{
	Status = status;
}

int cargo::getReadyTime() const
{
	return ReadyTime;
}
int cargo::getLoadingTime() const
{
	return LoadingTime;
}

int cargo::getID() const
{
	return ID;
}
int cargo::getDist() const
{
	return Dist;
}
int cargo::getCost() const
{
	return Cost;
}
int cargo::getDeliveredTime() const
{
	return DeliveredTime;
}
CargoType cargo::getType () const
{
	return TYP;
}
CargoStatus cargo::getStatus() const
{
	return Status;
}

cargo::~cargo()
{
}