#include "cargo.h"

cargo::cargo()
{
	RT = LUT = DD = Cost = -1;
	TYP = NORMAL;
}

cargo::cargo(int rt, int lut, int dd, int cost, CargoType type)
{
	setReadyTime (rt);
	setLUTime (lut);
	setDistance (dd);
	setCost (cost);
	setType (type);
}

void cargo::setReadyTime (int rt)
{
	RT = (rt > 0)? rt : 0;
}
void cargo::setLUTime (int lut)
{
	LUT = (lut > 0)? lut : 0;
}
void cargo::setDistance (int dd)
{
	DD = (dd > 0)? dd : 0;
}
void cargo::setCost (int cost)
{
	Cost = (cost > 0)? cost : 0;
}
void cargo::setType (CargoType type)
{
	TYP = type;
}

int cargo::getReadyTime ()
{
	return RT;
}
int cargo::getLUTime ()
{
	return LUT;
}
int cargo::getDistance ()
{
	return DD;
}
int cargo::getCost ()
{
	return Cost;
}
CargoType cargo::getType ()
{
	return TYP;
}

cargo::~cargo()
{
}


