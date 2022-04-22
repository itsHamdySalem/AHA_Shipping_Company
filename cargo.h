#pragma once

enum CargoType
{
	NORMAL,
	SPECIAL,
	VIP
};

class cargo
{
private:
	int ReadyTime, LoadingTime, ID, Dist, Cost;
	CargoType TYP;
public:
	cargo(int RT, int LT, int id, int dist, int cost, CargoType type);

	int getLoadingTime() const;
	int getID() const;
	int getDist() const;
	int getCost() const;
	int getType () const;
};
