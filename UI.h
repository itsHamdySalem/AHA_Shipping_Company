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
	Company* company;

	void printCargosOfType(list<cargo*>&, CargoType, char, char, bool);
    void printTrucksOfType(list<truck*>&, TruckType, char, char, TruckStatus, bool);
    string toTimeFormat(int);
public:
	UI();
	UI(Company *);

	void setMode ();

	void ApplyMode ();
	void ApplyInteractive ();
	void ApplyStepByStep ();
	void ApplySilent ();

	bool LoadInputFile ();
	bool generateOutputFile ();

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