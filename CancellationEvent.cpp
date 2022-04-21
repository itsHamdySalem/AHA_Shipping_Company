#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(string t, int id)
{

}

void CancellationEvent::setTime(string t)
{
	int idx = 0;
	while (t[idx] != ':') idx++;
	Time = stoi(t.substr(0, idx)) * 24 + stoi(t.substr(idx + 1));
}

int CancellationEvent::getTime() const
{
	return Time;
}

int CancellationEvent::getID() const
{
	return ID;
}

void CancellationEvent::Excute()
{
	// if (VIPlist.remove(ID)) return;
	// if (NormalList.remove(ID)) return;
	// if (Speciallist.remove(ID)) return;
}
