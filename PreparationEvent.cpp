#include "PreparationEvent.h"
#include "Types.h"

PreparationEvent::PreparationEvent(char type, string time, int id, int dist, int LT, int cost)
{
	setCargoType(type);
	setTime(time);
	ID = id;
	Dist = dist;
	LoadingTime = LT;
	Cost = cost;
}

void PreparationEvent::setTime(string t)
{
	int idx = 0;
	while (t[idx] != ':') idx++;
	Time = stoi(t.substr(0, idx)) * 24 + stoi(t.substr(idx + 1));
}

void PreparationEvent::setCargoType(char t)
{
	if (t == 'V') cargotype = VIP_CARGO;
	if (t == 'N') cargotype = NORMAL_CARGO;
	if (t == 'S') cargotype = SPECIAL_CARGO;
}

int PreparationEvent::getTime() const
{
	return Time;
}

void PreparationEvent::Execute(Company* company){
	cargo* nw = new cargo(Time, LoadingTime, ID, Dist, Cost, cargotype, WAITING_CARGO);
	company->addCargo(nw);
}

