#include "truck.h"


truck::truck()
{
	TC = MT = Speed = DI = 0;
	TYP = NORMAL_TRUCK;
}

truck::truck(int tc, int mt, int speed, int di, TruckType type)
{
	setCapacity (tc);
	setMaintenanceTime (mt);
	setSpeed (speed);
	setDeliveryInterval (di);
	setType (type);
}

void truck::setCapacity (int tc)
{
	TC = (tc > 0)? tc : 0;
}
void truck::setMaintenanceTime (int mt)
{
	MT = (mt > 0)? mt : 0;
}
void truck::setSpeed (int speed)
{
	Speed = (speed > 0)? speed : 0;
}
void truck::setDeliveryInterval (int di)
{
	DI = (di > 0)? di : 0;
}
void truck::setType (TruckType type)
{
	TYP = type;
}

int truck::getCapacity ()
{
	return TC;
}
int truck::getMaintenanceTime ()
{
	return MT;
}
int truck::getSpeed ()
{
	return Speed;
}
int truck::getDeliveryInterval ()
{
	return DI;
}
TruckType truck::getType ()
{
	return TYP;
}

truck::~truck()
{
}

