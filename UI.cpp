#include "UI.h"
#include "PreparationEvent.h"
#include "CancellationEvent.h"
#include "PromotionEvent.h"
#include <unistd.h>
#include <fstream>
#include "ReadWrite.h"
UI::UI(){
}


UI::UI(Company* c){

	company = c;
}

void UI::setMode ()
{
	int m;
	cout << "\nSelect a mode from the following:\n1-Interactive\t2-Step-by-Step\t3-Silent\n";
	cout << "Enter mode number: ";
	cin >> m;
	switch (m)
	{
	case 1:
		mode = interactive;
		break;
	case 2:
		mode = step_by_step;
		break;
	case 3:
		mode = silent;
		break;
	default:
		cout << "Invalid mode...\nYou should enter a mode number from {1, 2, 3}...!\n";
		setMode();
		break;
	}
	cout << "\n--------------------------------------------------------------\n";
}

void UI::ApplyMode ()
{
	switch (mode)
	{
	case interactive:
		cout << "\nInteractive Mode\n";
		ApplyInteractive();
		break;
	case step_by_step:
		cout << "\nStep-by-Step Mode\n";
		ApplyStepByStep();
		break;
	case silent:
		cout << "\nSilent Mode\n";
		ApplySilent();
		break;
	default:
		break;
	}
	cout << "\n--------------------------------------------------------------\n";
}

void UI::ApplyInteractive ()
{
	cout << "Simulation Starts...\n\n";
	while (company->getCurrentTime() < 250)
	{
        company->checkEachHour();
		printCurrentTime(company);
		printWaitingCargos(company);

        printLoadingTrucks(company);
        printEmptyTrucks(company);
        printMovingCargos(company);
        printInCheckTrucks(company);

        printDeliveredCargos(company);
		cout << "press ENTER to continue..\n";
	    cin.ignore();
		cout << "\n-------------------------------------------------------\n";
		company->setCurrentTime(company->getCurrentTime() + 1);
	}
    ::generateOutputFile(company);
    cout << "Simulation Ended and File Output was created\n";

}
void UI::ApplyStepByStep ()
{
    cout << "Simulation Starts...\n\n";
    while (company->getCurrentTime() < 250)
    {
        company->checkEachHour();
        printCurrentTime(company);
        printWaitingCargos(company);

        printLoadingTrucks(company);
        printEmptyTrucks(company);
        printMovingCargos(company);
        printInCheckTrucks(company);

        printDeliveredCargos(company);
        cout << "\n-------------------------------------------------------\n";
        company->setCurrentTime(company->getCurrentTime() + 1);
        //sleep(1);
    }

    ::generateOutputFile(company);
    cout << "Simulation Ended and File Output was created\n";
}
void UI::ApplySilent ()
{
    cout << "Simulation Starts...\n\n";
    while (company->getCurrentTime() < 250)
    {
        company->checkEachHour();
        company->setCurrentTime(company->getCurrentTime() + 1);
    }

    ::generateOutputFile(company);
    cout << "Simulation Ended and File Output was created\n";
}

bool UI::LoadInputFile ()
{
	string FileName;
	cout << "\nEnter The File Name: ";
	cin >> FileName;
	cout << "Reading File...\n";

    if(::LoadInputFile(company, FileName)){
        cout << "File has been loaded successfully!\n";
        cout << "\n--------------------------------------------------------------\n";
        return true;
    }
    cout << "File not found!\n";
    cout << "\n--------------------------------------------------------------\n";

    return false;

}


void UI::printCurrentTime(Company * cmp){
    int hr = cmp->getCurrentTime();
    cout << "Current Time (Day:Hour):" << hr/24 + 1 << ":" << hr%24 << endl;
}

void UI::printCargosOfType(list<cargo*>& cargos, CargoType cType, char openBracket, char closeBracket, bool forDelivered=0){
    bool isFirstOfType = 1;
	cout << ' ';
    for(int i=0;i<cargos.size();i++) {
        if(cargos.at(i)->getType() == cType){
            if(forDelivered && cargos.at(i)->getDeliveredTime() > company->getCurrentTime()) continue;
			if (isFirstOfType) cout << openBracket << cargos.at(i)->getID();
            else cout << ',' << cargos.at(i)->getID();
            isFirstOfType=0;
        }
    }
    if(!isFirstOfType) cout << closeBracket;

}

void UI::printTrucksOfType(list<truck*>& trucks, TruckType tType, char openBracket, char closeBracket){
    bool isFirstOfType = 1;
	cout << ' ';
    for(int i=0;i<trucks.size();i++) {
        if(trucks.at(i)->getType() == tType){
			if (isFirstOfType) cout << openBracket << trucks.at(i)->getID();
            else cout << ',' << trucks.at(i)->getID();
            isFirstOfType=0;
        }
    }
    if(!isFirstOfType) cout << closeBracket;

}


void UI::printWaitingCargos(Company *cmp){
    list<cargo*>& cargos = cmp->getWaitingCargos();
    cout << cargos.size() << " Waiting Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']');
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')');
    printCargosOfType(cargos, VIP_CARGO, '{', '}');
    cout << "\n-----------------------------------------\n";
}

void UI::printLoadingTrucks(Company *cmp){
    list<truck*>& trucks = cmp->getLoadingTrucks();
    cout << trucks.size() << " Loading Trucks:";

    printTrucksOfType(trucks, NORMAL_TRUCK, '[', ']');
    printTrucksOfType(trucks, SPECIAL_TRUCK, '(', ')');
    printTrucksOfType(trucks, VIP_TRUCK, '{', '}');

    cout << "\n-----------------------------------------\n";
}

void UI::printEmptyTrucks(Company *cmp){
    list<truck*>& trucks = cmp->getEmptyTrucks();
    cout << trucks.size() << " Empty Trucks:";

    printTrucksOfType(trucks, NORMAL_TRUCK, '[', ']');
    printTrucksOfType(trucks, SPECIAL_TRUCK, '(', ')');
    printTrucksOfType(trucks, VIP_TRUCK, '{', '}');
    cout << "\n-----------------------------------------\n";

}

void UI::printMovingCargos(Company *cmp){
    list<cargo*>& cargos = cmp->getMovingCargos();
    cout << cargos.size() << " Moving Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']');
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')');
    printCargosOfType(cargos, VIP_CARGO, '{', '}');
    cout << "\n-----------------------------------------\n";

}

void UI::printInCheckTrucks(Company *cmp){
    list<truck*>& trucks = cmp->getCheckUpTrucks();
    cout << trucks.size() << " Check Up Trucks:";

    printTrucksOfType(trucks, NORMAL_TRUCK, '[', ']');
    printTrucksOfType(trucks, SPECIAL_TRUCK, '(', ')');
    printTrucksOfType(trucks, VIP_TRUCK, '{', '}');
    cout << "\n-----------------------------------------\n";
}

void UI::printDeliveredCargos(Company *cmp){
    list<cargo*>& cargos = cmp->getDeliveredCargos();
    int sz = cargos.size();
    for(int i=0;i<cargos.size();i++){
        if(cargos.at(i)->getDeliveredTime() > company->getCurrentTime()) sz--;
    }
    cout << sz << " Delivered Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']', 1);
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')', 1);
    printCargosOfType(cargos, VIP_CARGO, '{', '}', 1);
    cout << "\n-----------------------------------------\n";
}


UI::~UI()
{
}
