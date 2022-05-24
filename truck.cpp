#include "truck.h"


truck::truck()
{
	NumberOfJournies = ReadyTime = 0;
    STATUS = AVAILABLE_TRUCK;
}

truck::truck(int tc, int mt, int speed, int MJ, TruckType type, TruckStatus status)
{
	setCapacity (tc);
	setCheckUpTime (mt);
	setSpeed (speed);
	setMaxJournies(MJ);
	setType (type);
    setStatus(status);
}

void truck::setCapacity (int tc)
{
	TruckCapacity = (tc > 0)? tc : 0;
}
void truck::setCheckUpTime (int mt)
{
	CheckupTime = (mt > 0)? mt : 0;
}
void truck::setSpeed (int speed)
{
	Speed = (speed > 0)? speed : 0;
}
void truck::setMaxJournies(int MJ)
{
	MaxJournies = MJ;
}
void truck::setReadyTime(int t)
{
	ReadyTime = t;
}
void truck::setType (TruckType type)
{
	TYP = type;
}

void truck::setStatus(TruckStatus status){
    STATUS = status;
}

int truck::getCapacity ()
{
	return TruckCapacity;
}
int truck::getCheckUpTime ()
{
	return CheckupTime;
}
int truck::getSpeed ()
{
	return Speed;
}
int truck::getReadyTime()
{
	return ReadyTime;
}

int truck::getMaxJournies()
{
	return MaxJournies;
}

int truck::getNumberOfJournies()
{
	return NumberOfJournies;
}
TruckType truck::getType ()
{
	return TYP;
}

truck::~truck()
{
}


