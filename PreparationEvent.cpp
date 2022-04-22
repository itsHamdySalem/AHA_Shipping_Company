#include "PreparationEvent.h"

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
	if (t == 'V') cargotype = VIP;
	if (t == 'N') cargotype = NORMAL;
	if (t == 'S') cargotype = SPECIAL;
}

int PreparationEvent::getTime() const
{
	return Time;
}

void PreparationEvent::Excute()
{
	cargo* nw = new cargo(Time, LoadingTime, ID, Dist, Cost, cargotype);
	/*if (cargotype == VIP); // vipcargos.push(*nw);
	if (cargotype == NORMAL); // normalcargos.push(*nw); // !!!! these lines should be modified
	if (cargotype == SPECIAL); // specialcargos.push(*nw);*/
}

