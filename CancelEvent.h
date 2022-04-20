#pragma once
#include "event.h"
class CancelEvent :
	public Event
{
public:
	CancelEvent(void);
	~CancelEvent(void);
};

