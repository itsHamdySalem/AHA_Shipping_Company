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

public:
	cargo(int RT, int LT, int id, int dist, int cost);

	int getLoadingTime() const;
	int getID() const;
	int getDist() const;
	int getCost() const;

};
