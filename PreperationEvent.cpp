#include "PreperationEvent.h"


PreperationEvent::PreperationEvent(char CT, string et, int id, int dist,int lt, int cost)
{
	setType(CT);
	setTime(et);

}

void PreperationEvent::Execute ()
{

}
	
void PreperationEvent::setType (char ct)
{
	switch (ct)
	{
	case 'N':
		TYP = NORMAL_CARGO;
		break;
	case 'S':
		TYP = SPECIAL_CARGO;
		break;
	case 'V' :
		TYP = VIP_CARGO;
		break;
	}
}
void PreperationEvent::setTime (string et)
{
	
}

PreperationEvent::~PreperationEvent(void)
{
}
