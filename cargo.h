#pragma once
#ifndef CARGO_H
#define CARGO_H

#include "Types.h"

class cargo
{
private:
	int ReadyTime, LoadingTime, ID, Dist, Cost;
	CargoType TYP;
    CargoStatus STATUS;
public:
	cargo(int RT, int LT, int id, int dist, int cost, CargoType type, CargoStatus);

	int getLoadingTime() const;
	int getID() const;
	int getDist() const;
	int getCost() const;

    CargoType getType () const;
};

#endif
