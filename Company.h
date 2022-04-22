#pragma once
#ifndef COMPANY_H
#define COMPANY_H
 
#include "Event.h"
#include "list.h"
#include "cargo.h"
#include "truck.h"
#include "priority_queue.h"
#include "queue.h"
 
class Company
{
private:
	list<Event*> Events;
    list<cargo*>VIP_Cargos, Special_Cargos, Normal_Cargos;
    list<truck*> Trucks;
    priority_queue<truck*> Assigned_Trucks;
 
    void cancelCargo(int, list<cargo*>*);
public:
	Company();
 
	void executeEvents();
    void simulate();
 
    void promoteCargo(int cargoID);
    void addCargo(cargo*);
    void addTruck(truck*);
    void cancelCargo(int);
 
	~Company();
};
 
#endif
 
 
