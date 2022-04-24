#include "Event.h"


Event::Event(void)
{
}

bool Event::ifTimeCome(int curHour){
    return this->ET <= curHour;
}


Event::~Event(void)
{
}
