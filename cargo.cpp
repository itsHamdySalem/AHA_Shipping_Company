#include "cargo.h"

cargo::cargo(int RT, int LT, int id, int dist, int cost, CargoType type)
{
	ReadyTime = RT;
	LoadingTime = LT;
	ID = id;
	Dist = dist;
	Cost = cost;
	TYP = type;
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


int cargo::getType () const
{
	return TYP;
}