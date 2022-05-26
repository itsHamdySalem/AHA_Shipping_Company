#include "UI.h"
#include "PreparationEvent.h"
#include "CancellationEvent.h"
#include "PromotionEvent.h"
#include <unistd.h>
#include <fstream>

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
	while (company->getCurrentTime() < 150)
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
    generateOutputFile();
}
void UI::ApplyStepByStep ()
{
    cout << "Simulation Starts...\n\n";
    while (company->getCurrentTime() < 71)
    {
        company->checkEachHour();
        printCurrentTime(company);
        printWaitingCargos(company);
        printDeliveredCargos(company);
        cout << "press ENTER to continue..\n";
        cout << "\n-------------------------------------------------------\n";
        company->setCurrentTime(company->getCurrentTime() + 1);
        sleep(1);
    }

	generateOutputFile();
}
void UI::ApplySilent ()
{
    while (company->getCurrentTime() < 30)
    {
        company->checkEachHour();
        company->setCurrentTime(company->getCurrentTime() + 1);
    }

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
	InFile >> J >> CN >> CS >> CV;

	company->addTrucks(N, NORMAL_TRUCK, NS, NTC, J, CN, 0);
    company->addTrucks(S, SPECIAL_TRUCK, SS, STC, J, CS, N);
    company->addTrucks(V, VIP_TRUCK, VS, VTC, J, CV, N + S);


    int AutoP, MaxW;
	InFile >> AutoP >> MaxW;

	company->setmaxWHours(MaxW);
    company->setautoPromotionLimitHours(24*AutoP);

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
    ofstream myfile;
    myfile.open ("result.txt");

    priority_queue<cargo*> allCargos;
    list<truck*> trucks;
    company->getCalculations(allCargos, trucks);
    int totalCargos = company->getWaitingCargos().size() + company->getDeliveredCargos().size();
    int avgWaitTime = 0, nCargos =0, sCargos=0, vCargos = 0;
    myfile << "CDT  ID  PT  WT   TID\n";
    while(allCargos.size()){
        cargo* c = allCargos.Front();
        allCargos.pop();

        switch(c->getType()){
            case NORMAL_CARGO:
                nCargos++;
                break;
            case SPECIAL_CARGO:
                sCargos++;
                break;
            case VIP_CARGO:
                vCargos++;
                break;
        }

        myfile << toTimeFormat(c->getDeliveredTime()) << " " << c->getID() << " " << toTimeFormat(c->getReadyTime()) << " " << toTimeFormat(c->getWaitTime()) << " " << c->getTruckDeliveredID() << endl;
        avgWaitTime += c->getWaitTime();
    }

    avgWaitTime = 1.0 * avgWaitTime / totalCargos;
    myfile << "Cargos: " << totalCargos << "[N: " << nCargos << ", S: " << sCargos << ", V: " << vCargos << "]" << endl;
    myfile << "Cargo Avg. Wait Time: " << toTimeFormat(avgWaitTime) << endl;
    myfile << "Promoted Cargos: " << (1.0*company->getPromotedCargos()/totalCargos)*100.0 << "%" << endl;

    int nTrucks=0, sTrucks=0, vTrucks = 0;
    double utilization_ = 0;
    for(int i=0;i<trucks.size();i++){

        truck* t = trucks.at(i);
        if(t->getNumberOfJournies())
            utilization_ += 1.0 * t->getTotalCargos() / (t->getCapacity() * t->getNumberOfJournies()) * (t->getActiveTime() / company->getCurrentTime());
        switch(t->getType()){
            case NORMAL_TRUCK:
                nTrucks++;
                break;
            case SPECIAL_TRUCK:
                sTrucks++;
                break;
            case VIP_TRUCK:
                vTrucks++;
                break;
        }

    }
    myfile << "Trucks: " << trucks.size() << "[N: " << nTrucks << ", S: " << sTrucks << ", V: " << vTrucks << "]" << endl;
    myfile << "Avg Active Time: " << 1.0*company->getActiveTime()/company->getCurrentTime() *100 << "%" << endl;
    myfile << "Utilization: " << 1.0*utilization_/(int)trucks.size()*100 << "% " <<  endl;
    myfile.close();

    return 1;
}

void UI::printCurrentTime(Company * cmp){
    int hr = cmp->getCurrentTime();
    cout << "Current Time (Day:Hour):" << hr/24 + 1 << ":" << hr%24 << endl;
}

string UI::toTimeFormat(int tim){
    return to_string(tim/24+1) + ":" + to_string(tim%24);
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
