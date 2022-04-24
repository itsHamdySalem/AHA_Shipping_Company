#include "UI.h"
#include "PreparationEvent.h"
#include "CancellationEvent.h"
#include "PromotionEvent.h"

UI::UI(){
}


UI::UI(Company* c){
    company = c;
    cout << "\n--------------------------------------------------------------\n";
	if (LoadInputFile())
	{
		cout << "\n--------------------------------------------------------------\n";
		setMode();
		cout << "\n--------------------------------------------------------------\n";
		ApplyMode();
		cout << "\n--------------------------------------------------------------\n";
	}
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
		cout << "Unvalid mode...\nYou should enter a mode number from {1, 2, 3}...!\n";
		setMode();
		break;
	}
}

void UI::ApplyMode ()
{
	//LoadInputFile();
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
}
void UI::ApplyInteractive ()
{
	// apply
	// _sleep(1000);
	cout << "Simulation Starts...\n";
	printCurrentTime(company);
	printEmptyTrucks(company);
	printWaitingCargos(company);
	generateOutputFile();
	cout << "Simulation ends, Output file created...\n";
}
void UI::ApplyStepByStep ()
{
	// apply
	cout << "Simulation Starts...\n";
	generateOutputFile();
	cout << "Simulation ends, Output file created...\n";
}
void UI::ApplySilent ()
{
	cout << "Simulation starts...\n";
	generateOutputFile();
	cout << "Simulation ends, Output file created...\n";
}

bool UI::LoadInputFile ()
{
	string FileName;
	cout << "\nEnter The File Name: ";
	cin >> FileName;
	cout << "Reading File...\n";

	ifstream InFile;
	InFile.open(FileName+".txt");
	if (!InFile.is_open())
	{
		cout << FileName << " not fount!\n";
		return false;
	}

	int N, S, V;
	InFile >> N >> S >> V;
	// do something...
	int NS, SS, VS;
	InFile >> NS >> SS >> VS;
	// do something...
	int NTC, STC, VTC;
	InFile >> NTC >> STC >> VTC;
	// do something...
	int J, CN, CS, CV;
	InFile >> CN >> CS >> CV >> J;
	// do something...
    company->addTrucks(N, NORMAL_TRUCK, NS, NTC, CN, J);
    company->addTrucks(S, SPECIAL_TRUCK, SS, STC, CS, J);
    company->addTrucks(V, VIP_TRUCK, VS, VTC, CV, J);


    int AutoP, MaxW;
	InFile >> AutoP >> MaxW;
	// do something...
    company->setmaxWHours(MaxW);
    company->setautoPromotionLimitHours(AutoP);

	int E;
	InFile >> E;
	// do something...

	char Etype;
	char TYP;
	string ET;
	int ID, DIST, LT, Cost, ExtraMoney;

	for (int i = 0; i < E; i++)
	{
		InFile >> Etype;
        Event *Event;
		switch (Etype)
		{
		case 'R':
			InFile >> TYP >> ET >> ID >> DIST >> LT >> Cost;
			// do something...
            Event = new PreparationEvent(TYP, ET, ID, DIST, LT, Cost);
            break;
		case 'X':
			InFile >> ET >> ID;
			// do something...
            Event = new CancellationEvent(ET, ID);
			break;
		case 'P':
			InFile >> ET >> ID >> ExtraMoney;
			// do something...
            Event = new PromotionEvent(ET, ID, ExtraMoney);
			break;
		default:
			break;
		}

        company->addEvent(Event);
	}
	
	InFile.close();
	cout << "File has been loaded successfully!\n";
	return true;
}
void UI::generateOutputFile ()
{
}

void UI::printCurrentTime(Company * cmp){
    int hr = cmp->getCurrentTime();
    cout << "Current Time (Day:Hour):" << hr/24 << ":" << hr%24 << endl;
}

void UI::printCargosOfType(list<cargo*>& cargos, CargoType cType, char openBracket, char closeBracket){
    bool isFirstOfType = 1;
	cout << ' ';
    for(int i=0;i<cargos.size();i++) {
        if(cargos.at(i)->getType() == cType){
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
			if (isFirstOfType) cout << openBracket << trucks.at(i)->getCapacity();
            // TODO:: Edit get capacity
            else cout << ',' << trucks.at(i)->getCapacity();
            isFirstOfType=0;
        }
    }
    if(!isFirstOfType) cout << closeBracket;

}


void UI::printWaitingCargos(Company *cmp){
    list<cargo*> cargos;
    cmp->getWaitingCargos(cargos);
    cout << cargos.size() << " Waiting Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']');
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')');
    printCargosOfType(cargos, VIP_CARGO, '{', '}');
    cout << "\n-----------------------------------------\n";
}

void UI::printLoadingTrucks(Company *cmp){
    list<truck*> trucks;
    cmp->getLoadingTrucks(trucks);
    cout << trucks.size() << " Loading Trucks:";

    printTrucksOfType(trucks, NORMAL_TRUCK, '[', ']');
    printTrucksOfType(trucks, SPECIAL_TRUCK, '(', ')');
    printTrucksOfType(trucks, VIP_TRUCK, '{', '}');
    cout << "\n-----------------------------------------\n";
}

void UI::printEmptyTrucks(Company *cmp){
    list<truck*> trucks;
    cmp->getEmptyTrucks(trucks);
    cout << trucks.size() << " Empty Trucks:";

    printTrucksOfType(trucks, NORMAL_TRUCK, '[', ']');
    printTrucksOfType(trucks, SPECIAL_TRUCK, '(', ')');
    printTrucksOfType(trucks, VIP_TRUCK, '{', '}');
    cout << "\n-----------------------------------------\n";

}

void UI::printMovingCargos(Company *cmp){
    list<cargo*> cargos;
    cmp->getMovingCargos(cargos);
    cout << cargos.size() << " Moving Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']');
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')');
    printCargosOfType(cargos, VIP_CARGO, '{', '}');
    cout << "\n-----------------------------------------\n";

}

void UI::printInCheckTrucks(Company *cmp){
    list<truck*> trucks;
    cmp->getCheckUpTrucks(trucks);
    cout << trucks.size() << " Check Up Trucks:";

    printTrucksOfType(trucks, NORMAL_TRUCK, '[', ']');
    printTrucksOfType(trucks, SPECIAL_TRUCK, '(', ')');
    printTrucksOfType(trucks, VIP_TRUCK, '{', '}');
    cout << "\n-----------------------------------------\n";
}

void UI::printDeliveredCargos(Company *cmp){
    list<cargo*> cargos;
    cmp->getDeliveredCargos(cargos);
    cout << cargos.size() << " Delivered Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']');
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')');
    printCargosOfType(cargos, VIP_CARGO, '{', '}');
    cout << "\n-----------------------------------------\n";

}


UI::~UI()
{
}
