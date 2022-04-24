#pragma once
#ifndef UI_H
#define UI_H

#include <iostream>
#include <fstream>
#include <string>
#include "Types.h"
#include "Company.h"
using namespace std;

class Company;

class UI
{
private:
    MODE mode;
    void printCargosOfType(list<cargo*>&, CargoType, char, char);
    void printTrucksOfType(list<truck*>&, TruckType, char, char);
    Company* company;
public:
	UI(Company *);
    UI();

	void setMode ();
	void ApplyMode ();
	void ApplyInteractive ();
	void ApplyStepByStep ();
	void ApplySilent ();

	bool LoadInputFile ();
	void generateOutputFile ();

    void printCurrentTime(Company *);
    void printWaitingCargos(Company *);
    void printLoadingTrucks(Company *);
    void printEmptyTrucks(Company *);
    void printMovingCargos(Company *);
    void printInCheckTrucks(Company *);
    void printDeliveredCargos(Company *);

	~UI();

};

#endif

