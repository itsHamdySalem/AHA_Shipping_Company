#include "Company.h"
 
#include <iostream>
using namespace std;
 
Company::Company()
{
 
}
 
void Company::executeEvents()
{
	int eventsSize = Events.size();
 
	for(int i=0;i<eventsSize;i++)
	{
		Event* event = Events.at(i);
		event->Execute();
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
            VIP_Cargos.add(currentCargo);
            break;
        }
    }
 
}
 
void Company::addCargo(cargo* c){
    switch(c->getType()){
        case 0: Normal_Cargos.add(c);
        case 1: Special_Cargos.add(c);
        default: VIP_Cargos.add(c);
    }
}
 
void Company::addTruck(truck *c){
    Trucks.add(c);
}
 
void Company::cancelCargo(int cargoID){
    cancelCargo(cargoID, &VIP_Cargos);
    cancelCargo(cargoID, &Special_Cargos);
    cancelCargo(cargoID, &Normal_Cargos);
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