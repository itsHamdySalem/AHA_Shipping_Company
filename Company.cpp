#include "Company.h"

#include <iostream>
using namespace std;

Company::Company()
{
}
 
void Company::executeEvents()
{
	int eventsSize = events.size();
	
	for(int i=0;i<eventsSize;i++)
	{
		Event* event = events.at(i);
		event->Execute();
	}
}
 
void Company::simulate()
{
	for(int hour = 0;hour < 100;hour++)
		executeEvents();
}

Company::~Company()
{
}
