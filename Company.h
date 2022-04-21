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
	list<Event*> events;
    list<cargo*> cargos;
    list<truck*> trucks;
	// we should add lists of waiting, loading, moving and delivered cargos
	// also lists of available, loading, moving, checkup trucks
	// lists for all types of cargos and trucks
public:
	Company();
	
	void executeEvents();
    void simulate();
	
	~Company();
};

#endif