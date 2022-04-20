#pragma once
#ifndef CARGO_H
#define CARGO_H

#include <iostream>
#include "Time.h"
using namespace std;

enum CargoType
{
	NORMAL_CARGO,
	SPECIAL_CARGO,
	VIP_CARGO
};

class cargo
{
private:
	int RT, LUT, DD, Cost;
	CargoType TYP;
public:
	cargo();
	cargo(int rt, int lut, int dd, int cost, CargoType type);

	void setReadyTime (int rt);
	void setLUTime (int lut);
	void setDistance (int dd);
	void setCost (int cost);
	void setType (CargoType type);

	int getReadyTime ();
	int getLUTime ();
	int getDistance ();
	int getCost ();
	CargoType getType ();

	~cargo();
};

#endif