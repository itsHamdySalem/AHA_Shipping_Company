#include "UI.h"
#include "PreparationEvent.h"
#include "CancellationEvent.h"
#include "PromotionEvent.h"

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
		cout << "Unvalid mode...\nYou should enter a mode number from {1, 2, 3}...!\n";
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
	while (company->getCurrentTime() < 71)
	{
		company->executeEvents();
		if (company->getCurrentTime() % 5 == 0 && company->getCurrentTime())
			company->moveCargo();
		printCurrentTime(company);
		printWaitingCargos(company);
		printDeliveredCargos(company);
		cout << "press ENTER to continue..\n";
	    cin.ignore();
		cout << "\n-------------------------------------------------------\n";
		company->setCurrentTime(company->getCurrentTime() + 1);
		company->checkIfAutoPPassed();
	}
}
void UI::ApplyStepByStep ()
{
	//_sleep(1000);
	cout << "Simulation Starts...\n";
	generateOutputFile();
}
void UI::ApplySilent ()
{
	generateOutputFile();
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
		cout << FileName << " not found!\n";
		return false;
	}

	int N, S, V;
	InFile >> N >> S >> V;
	int NS, SS, VS;
	InFile >> NS >> SS >> VS;
	int NTC, STC, VTC;
	InFile >> NTC >> STC >> VTC;
	int J, CN, CS, CV;
	InFile >> CN >> CS >> CV >> J;

	company->addTrucks(N, NORMAL_TRUCK, NS, NTC, CN, J);
    company->addTrucks(S, SPECIAL_TRUCK, SS, STC, CS, J);
    company->addTrucks(V, VIP_TRUCK, VS, VTC, CV, J);


    int AutoP, MaxW;
	InFile >> AutoP >> MaxW;

	company->setmaxWHours(MaxW);
    company->setautoPromotionLimitHours(AutoP);

	int E;
	InFile >> E;

	char Etype, TYP;
	string ET;
	int ID, DIST, LT, Cost, ExtraMoney;

	for (int i = 0; i < E; i++)
	{
		InFile >> Etype;
        Event *event;
		switch (Etype)
		{
		case 'R':
			InFile >> TYP >> ET >> ID >> DIST >> LT >> Cost;
            event = new PreparationEvent(TYP, ET, ID, DIST, LT, Cost);
            break;
		case 'X':
			InFile >> ET >> ID;
            event = new CancellationEvent(ET, ID);
			break;
		case 'P':
			InFile >> ET >> ID >> ExtraMoney;
            event = new PromotionEvent(ET, ID, ExtraMoney);
			break;
		default:
			break;
		}
        company->addEvent(event);
	}
	
	InFile.close();
	cout << "File has been loaded successfully!\n";
	cout << "\n--------------------------------------------------------------\n";
	return true;
}

bool UI::generateOutputFile ()
{
	// TODO
	if (1)	// if generated successfully
	{
		cout << "Simulation ends, Output file created...\n";
		return true;
	}
	else
	{
		cout << "Error: output file is not generated...!\n";
		return false;
	}
}

void UI::printCurrentTime(Company * cmp){
    int hr = cmp->getCurrentTime();
    cout << "Current Time (Day:Hour):" << hr/24 + 1 << ":" << hr%24 << endl;
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
    list<cargo*>& cargos = cmp->getWaitingCargos();
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
    list<cargo*>& cargos = cmp->getDeliveredCargos();
    cout << cargos.size() << " Delivered Cargos:";

    printCargosOfType(cargos, NORMAL_CARGO, '[', ']');
    printCargosOfType(cargos, SPECIAL_CARGO, '(', ')');
    printCargosOfType(cargos, VIP_CARGO, '{', '}');
    cout << "\n-----------------------------------------\n";
}


UI::~UI()
{
}
