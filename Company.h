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
class Event;

class Company
{
private:

    list<cargo*> Normal_Cargos;
    list<cargo*> Special_Cargos;
    priority_queue<cargo*> VIP_Cargos;

    queue<truck*> VIP_Trucks, Special_Trucks, Normal_Trucks;

    list<cargo*> loadingCargos, waitingCargos, movingCargos, deliveredCargos;
    list<truck*> availableTrucks, loadingTrucks, checkUpTrucks;
    priority_queue<truck*> movingTrucks;

    queue<Event*> Events;

    UI *ui;

    int currentTime, autoPromotionLimitHours, maxWHours;
    int activeTime;double utilization;
    int promotedCargos;

	void cancelCargo(int, list<cargo*>&);
	void moveCargoOfType(CargoType type, list<cargo*> &cargos);
    bool SendTruckForCheckUp(truck* &);
    void AssignCargos(list<cargo*>&, queue<truck*>&, bool&);
    void AssignCargos(priority_queue<cargo*>&, queue<truck*>&, bool&);
    void AssignMaxW(list<cargo*>&, queue<truck*>&, bool&);
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
	void setCurrentTime(int time);

    list<cargo*>& getWaitingCargos();
    list<cargo*>& getMovingCargos();

    list<truck*>& getLoadingTrucks();
    list<truck*>& getEmptyTrucks();
    list<truck*>& getCheckUpTrucks();
    void SendTrucksForCheckUp();
    void CheckAutoPromotion();
    list<cargo*>& getDeliveredCargos();

    void checkCheckupTrucks();
	// phase I : move cargos from waiting to delivered
	void moveCargo ();

    void addTrucks(int N, TruckType typ, int speed, int capacity, int journies, int durationCheckup, int id);
	void moveTrucks();

    void AssignCargos();

    void checkEachHour();

    void getCalculations(priority_queue<cargo*> &c, list<truck*> &ls);
    int getPromotedCargos();
    int getActiveTime();

    void checkReturningTrucks();

    ~Company(){}
};
 
#endif
 

