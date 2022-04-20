#pragma once
#include "event.h"
#include <string>
class PreperationEvent :
	public Event
{
public:
	PreperationEvent(char CT, string et, int id, int dist,int lt, int cost);

	void Execute ();
	
	void setType (char ct);
	void setTime (string et);

	~PreperationEvent();
};

