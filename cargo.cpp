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
	DeliveredTime = 2e9;
    waitTime = -1;
}

void cargo::setReadyTime(int rt)
{
	ReadyTime = rt;
}
void cargo::setLoadingTime(int lt)
{
	LoadingTime = lt;
}
void cargo::setID (int id)
{
	ID = id;
}
void cargo::setDistance(int dist)
{
	Dist = dist;
}
void cargo::setDeliveredTime(int t)
{
	DeliveredTime = t;
}
void cargo::setCost (int cost)
{
	Cost = cost;
}
void cargo::setType(CargoType type)
{
	TYP = type;
}
void cargo::setStatus(CargoStatus status)
{
	Status = status;
}

void cargo::setWaitTime(int t) {
    waitTime = t;
}

void cargo::setTruckDelivered(truck* t) {
    truckDeliveredID = t;
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

int cargo::getWaitTime() const {
    return waitTime;
}

truck* cargo::getTruckDelivered() const {
    return truckDeliveredID;
}

cargo::~cargo()
{
}