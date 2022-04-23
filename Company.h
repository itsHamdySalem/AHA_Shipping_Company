#pragma once
#ifndef COMPANY_H
#define COMPANY_H
 
#include "Event.h"
#include "list.h"
#include "cargo.h"
#include "truck.h"
#include "priority_queue.h"
#include "queue.h"
#include "UI.h"

class UI;

class Company
{
private:

    list<cargo*> Normal_Cargos;
    queue<cargo*> Special_Cargos;
    priority_queue<cargo*> VIP_Cargos;

    list<truck*> VIP_Trucks, Special_Trucks, Normal_Trucks;
    priority_queue<truck*> Assigned_Trucks;

    list<cargo*> loadingCargos, waitingCargos, movingCargos, deliveredCargos;
    list<truck*> availableTrucks, loadingTrucks, movingTrucks, checkUpTrucks;

    priority_queue<Event*> Events;

    UI *ui;

    int currentTime, autoPromotionLimitHours, maxWHours;

    void cancelCargo(int, list<cargo*>*);
public:
	Company();
 
	void executeEvents();
    void simulate();

    void addEvent(Event*);
 
    void promoteCargo(int cargoID);
    void addCargo(cargo*);
    void addTruck(truck*);
    void cancelCargo(int);

    void setautoPromotionLimitHours(int);
    void setmaxWHours(int);

    int getCurrentTime();

    void getWaitingCargos(list<cargo*>&);
    void getMovingCargos(list<cargo*>&);

    void getLoadingTrucks(list<truck*>&);
    void getEmptyTrucks(list<truck*>&);
    void getCheckUpTrucks(list<truck*>&);
    void getDeliveredCargos(list<cargo*>&);

    void addTrucks(int N, TruckType typ, int speed, int capacity, int journies, int durationCheckup);

    void assignCargos();

	~Company(){}
};
 
#endif
 
 
