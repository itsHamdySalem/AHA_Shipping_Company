#include "Company.h"
#include "PromotionEvent.h"
#include "CancellationEvent.h"
#include "PreparationEvent.h"

string toTimeFormat(int tim){
    return to_string(tim/24+1) + ":" + to_string(tim%24);
}

bool LoadInputFile(Company *company, string FileName){

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

}

bool generateOutputFile (Company * company)
{
    ofstream myfile;
    myfile.open ("result.txt");

    priority_queue<cargo*> allCargos;
    list<truck*> trucks;
    company->getCalculations(allCargos, trucks);
    int totalCargos = company->getDeliveredCargos().size();
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

        myfile << toTimeFormat(c->getDeliveredTime()) << " " << c->getID() << " " << toTimeFormat(c->getReadyTime()) << " " << toTimeFormat(c->getWaitTime()) << " " << c->getTruckDelivered()->getID() << endl;
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
        if(t->getNumberOfJournies() && company->getCurrentTime() && t->getCapacity())
            utilization_ += (1.0 * t->getTotalCargos() / (1.0 * t->getCapacity() * t->getNumberOfJournies())) * (1.0 * t->getActiveTime() / company->getCurrentTime());
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
    myfile << "Avg Active Time: " << 1.0*company->getActiveTime()/totalCargos  << "%" << endl;
    myfile << "Utilization: " << 1.0*utilization_/(int)trucks.size()*100 << "% " <<  endl;
    myfile.close();

    return 1;
}
