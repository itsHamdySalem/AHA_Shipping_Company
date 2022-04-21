#pragma once
#ifndef COMPANY_H
#define COMPANY_H

#include "Event.h"
#include "list.h"
#include "cargo.h"
#include "truck.h"

class Company
{
private:
	list<Event*>events;
    list<cargo*>cargos;
    list<truck*>trucks;
public:
	Company();
	
	void executeEvents();
    void simulate();
	
	~Company();
};

#endif