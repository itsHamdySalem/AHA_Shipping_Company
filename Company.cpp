#include "Company.h"
#include "cargo.h"
Company::Company()
{
	currentTime = 0;
	ui = new UI(this);
	if (ui->LoadInputFile())
	{
		ui->setMode();
		simulate();
	}
}
 
void Company::executeEvents()
{
    while(!Events.empty() && Events.Front()->getTime() == currentTime) {
        // TODO:: Check if valid event, then execute
        Events.Front()->Execute(this);
        Events.pop();

    }
}
 
void Company::simulate()
{
	ui->ApplyMode();
}
 
void Company::promoteCargo(int cargoID){
 
    int cargosN = Normal_Cargos.size();
 
    for(int i=0;i<cargosN;i++)
    {
        cargo* currentCargo = Normal_Cargos.at(i);
        if(currentCargo->getID() == cargoID){

            Normal_Cargos.remove(currentCargo);
			currentCargo->setType(VIP_CARGO);
			VIP_Cargos.push(currentCargo, currentCargo->getReadyTime() + currentCargo->getCost());
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
    cancelCargo(cargoID, Normal_Cargos);
    cancelCargo(cargoID, waitingCargos);
}
 
void Company::cancelCargo(int cargoID, list<cargo*> &ls){
    int CargosN = ls.size();
    for(int i=0;i<CargosN;i++)
    {
        cargo* currentCargo = ls.at(i);
        if(currentCargo->getID() == cargoID){
            ls.remove(currentCargo);
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
void Company::setCurrentTime(int time)
{
	currentTime = (time > 0)? time : currentTime;
}

list<cargo*>& Company::getWaitingCargos(){
    return waitingCargos;
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

list<cargo*>& Company::getDeliveredCargos(){
    return deliveredCargos;
}

void Company::addTrucks(int N, TruckType typ, int speed, int capacity, int journies, int durationCheckup){
    for(int i=0;i<N;i++){
        truck* t = new truck(capacity, durationCheckup, speed, journies, typ, AVAILABLE_TRUCK);
        addTruck(t);
    }
}

void Company::moveTrucks()
{
	
}

void Company::addEvent(Event* e){
    Events.push(e);
}

void Company::setmaxWHours(int maxW){
    maxWHours = maxW;
}

void Company::setautoPromotionLimitHours(int maxPromotionLimit){
    autoPromotionLimitHours = maxPromotionLimit;
}

void Company::moveCargoOfType(CargoType type, list<cargo*> &cargos)
{
	for (int i = 0; i < cargos.size(); i++)
	{
		if(cargos.at(i)->getType() == type)
		{
			deliveredCargos.add(cargos.at(i));
			// cout << deliveredCargos.at(0)->getID() << '\n';
			cargos.remove(cargos.at(i));
			// cout << deliveredCargos.at(0)->getID() << '\n';
			// system("pause");
			return;
		}
	}
}

void Company::moveCargo ()
{
	moveCargoOfType(NORMAL_CARGO, waitingCargos);
	moveCargoOfType(SPECIAL_CARGO,waitingCargos);
	moveCargoOfType(VIP_CARGO,waitingCargos);
}

void Company::checkIfAutoPPassed(){
	int sz = Normal_Cargos.size();
	for(int i=0;i<sz;i++){
		cargo* cg = Normal_Cargos.at(i);
		if(currentTime - cg->getReadyTime() == autoPromotionLimitHours){
			promoteCargo(cg->getID());
		}
	}
}

void Company::loadCargosIntoTruck(truck *c){
	int cargosAvailable=0;bool mustFill = 0;
	list<cargo*> waitingCargos = getWaitingCargos();
	for(int i=0;i<waitingCargos.size;i++){
		if(currentTime - waitingCargos.at(i)->getReadyTime() >= maxWHours) mustFill = 1;  
		if(waitingCargos.at(i)->getType() == (CargoType)c->getType()){
			cargosAvailable++;
		}
	}

	mustFill&=(c->getType() != VIP_TRUCK);
	if(cargosAvailable >= c->getCapacity() || mustFill){

		int cnt = 0;
		for(int i=0;i<waitingCargos.size;i++){
			if (cnt == c->getCapacity()) break;
			if(currentTime - waitingCargos.at(i)->getReadyTime() >= maxWHours || 
				waitingCargos.at(i)->getType() == (CargoType)c->getType()){
				c->addCargo(waitingCargos.at(i));
				cnt++;
				waitingCargos.remove(waitingCargos.at(i));
			}
		}
	}
}