#include "Company.h"

#include "Types.h"
#include <iostream>
using namespace std;

Company::Company()
{
    currentTime = 0;
	ui = new UI(this);
   
}
 
void Company::executeEvents()
{
	int eventsSize = Events.size();
 
	for(int i=0;i<eventsSize;i++)
	{
		Event* event = Events.Front();
        if(event->ifTimeCome(currentTime)){
            // TODO:: Check if valid event, then execute
            event->Execute(this);
            Events.pop();
        }
	}
}
 
void Company::simulate()
{
	for(int hour = 0;hour < 100;hour++)
		executeEvents();
}
 
void Company::promoteCargo(int cargoID){
 
    int cargosN = Normal_Cargos.size();
 
    for(int i=0;i<cargosN;i++)
    {
        cargo* currentCargo = Normal_Cargos.at(i);
        if(currentCargo->getID() == cargoID){
            Normal_Cargos.remove(currentCargo);
            VIP_Cargos.push(currentCargo, 0);
            break;
        }
    }
 
}
 
void Company::addCargo(cargo* c){
    waitingCargos.add(c);
    switch(c->getType()){
        case NORMAL_CARGO:
            Normal_Cargos.add(c);
            break;
        case SPECIAL_CARGO:
            Special_Cargos.push(c);
            break;
        case VIP_CARGO:
            VIP_Cargos.push(c, 0);
            break;
        default:
            break;
    }
}
 
void Company::addTruck(truck *c){
    availableTrucks.add(c);
    switch(c->getType()){
        case NORMAL_TRUCK:
            Normal_Trucks.add(c);
            break;
        case SPECIAL_TRUCK:
            Special_Trucks.add(c);
            break;
        case VIP_TRUCK:
            VIP_Trucks.add(c);
            break;
        default:
            break;
    }

}
 
void Company::cancelCargo(int cargoID){
    cancelCargo(cargoID, &Normal_Cargos);
    cancelCargo(cargoID, &waitingCargos);
}
 
void Company::cancelCargo(int cargoID, list<cargo*> *ls){
    int CargosN = ls->size();
    for(int i=0;i<CargosN;i++)
    {
        cargo* currentCargo = ls->at(i);
        if(currentCargo->getID() == cargoID){
            ls->remove(currentCargo);
            break;
        }
    }
}

void Company::assignCargos(){
    // GET EMPTY VIP TRUCKS, NORMAl, SPECIAL

    // ASSIGN VIP Cargos (VIP => NORMAL => SPECIAL)

    // ASSIGN SPECIAL (SPECIAL ONLY)

    // ASSIGN NORMAL (NORMAL => VIP)
}

int Company::getCurrentTime(){
    return this->currentTime;
}

void Company::getWaitingCargos(list<cargo*>& wCargos){
    wCargos = waitingCargos;
}

void Company::getMovingCargos(list<cargo*> & mCargos){
    mCargos = movingCargos;
}

void Company::getLoadingTrucks(list<truck*> &lTrucks){
    lTrucks = loadingTrucks;
}

void Company::getEmptyTrucks(list<truck*> &eTrucks){
    eTrucks = availableTrucks;
}

void Company::getCheckUpTrucks(list<truck*> &cTrucks){
    cTrucks = checkUpTrucks;
}

void Company::getDeliveredCargos(list<cargo*>& dCargos){
    dCargos = deliveredCargos;
}

void Company::addTrucks(int N, TruckType typ, int speed, int capacity, int journies, int durationCheckup){
    for(int i=0;i<N;i++){
        truck* t = new truck(capacity, durationCheckup, speed, journies, typ, AVAILABLE_TRUCK);
        addTruck(t);
    }
}

void Company::addEvent(Event* e){
    Events.push(e, 0);
}

void Company::setmaxWHours(int maxW){
    maxWHours = maxW;
}

void Company::setautoPromotionLimitHours(int maxPromotionLimit){
    autoPromotionLimitHours = maxPromotionLimit;
}

