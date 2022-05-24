#include "Company.h"

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
            VIP_Cargos.push(currentCargo, 100000-currentCargo->getReadyTime()+currentCargo->getCost()+100000-currentCargo->getDist());
            break;
        }
    }
 
}
 
// priority eqaution is readytime less, cost high, distance less.

void Company::addCargo(cargo* c){
    waitingCargos.add(c);
    switch(c->getType()){
        case NORMAL_CARGO:
            Normal_Cargos.add(c);
            break;
        case SPECIAL_CARGO:
            Special_Cargos.add(c);
            break;
        case VIP_CARGO:
            VIP_Cargos.push(c, 100000-c->getReadyTime()+c->getCost()-c->getDist()+100000);
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

void Company::SendTrucksForCheckUp()
{
    SendTrucksForCheckUp(Normal_Trucks);
    SendTrucksForCheckUp(Special_Trucks);
    SendTrucksForCheckUp(VIP_Trucks);
}

void Company::SendTrucksForCheckUp(list<truck*> &ls)
{
    int sz = ls.size();
    for (int i = 0; i < sz; i++) {
        if (ls.at(i)->getNumberOfJournies() == ls.at(i)->getMaxJournies()) {
            ls.at(i)->setReadyTime(ls.at(i)->getReadyTime() + ls.at(i)->getCheckUpTime());
        }
    }
}

void Company::CheckAutoPromotion()
{
    list<cargo*>& ls = Normal_Cargos;
    for (int i = 0; i < ls.size(); i++) {
        if (currentTime - ls.at(i)->getReadyTime() >= autoPromotionLimitHours)
            promoteCargo(ls.at(i)->getID());
    }
}

void Company::AssignCargos(){
    // GET EMPTY VIP TRUCKS, NORMAl, SPECIAL

    bool DoneVIP, DoneSpecial, DoneNormal;
    DoneVIP = DoneSpecial = DoneNormal = false;

    AssignMaxW(Special_Cargos, Special_Trucks, DoneSpecial);
    AssignMaxW(Normal_Cargos, Normal_Trucks, DoneNormal);
    AssignMaxW(Normal_Cargos, VIP_Trucks, DoneVIP);

    AssignCargos(VIP_Cargos, VIP_Trucks, DoneVIP);
    AssignCargos(VIP_Cargos, Normal_Trucks, DoneNormal);
    AssignCargos(VIP_Cargos, Special_Trucks, DoneSpecial);

    AssignCargos(Special_Cargos, Special_Trucks, DoneSpecial);

    AssignCargos(Normal_Cargos, Normal_Trucks, DoneNormal);
    AssignCargos(Normal_Cargos, VIP_Trucks, DoneVIP);

    // ASSIGN VIP Cargos (VIP => NORMAL => SPECIAL)

    // ASSIGN SPECIAL (SPECIAL ONLY)

    // ASSIGN NORMAL (NORMAL => VIP)
}

void Company::AssignCargos(priority_queue<cargo*>& Cargos, list<truck*>& Trucks, bool& done)
{
    if (done) return;
    priority_queue <cargo*> ready;
    while (!Cargos.empty()) {
        cargo* cur = Cargos.Front();
        Cargos.pop();
        if (cur->getStatus() != WAITING_CARGO) continue;
        if (cur->getReadyTime() > currentTime) {
            Cargos.push(cur, 100000 - cur->getReadyTime() + cur->getCost() + 100000 - cur->getDist());
            break;
        }
        ready.push(cur, 100000 - cur->getReadyTime() + cur->getCost() + 100000 - cur->getDist());
    }
    for (int i = 0; !done && i < Trucks.size(); i++) {
        truck* cur = Trucks.at(i);
        if (cur->getReadyTime() <= currentTime) {
            if (ready.size() >= cur->getCapacity()) {
                done = true;
                int tot = 0, farest = 0;
                priority_queue<cargo*> dumpq(ready); // a dum pq just to calculate the total loading time and farest distance.
                int cnt = cur->getCapacity();
                while (cnt && !dumpq.empty()) {
                    auto curr = dumpq.Front();
                    dumpq.pop(); cnt--;
                    tot += curr->getLoadingTime();
                    farest = max(farest, curr->getDist());
                }
                cur->setReadyTime(currentTime+(tot + ceil(farest / cur->getSpeed())) * 2);
                cnt = cur->getCapacity();
                while (cnt && !ready.empty()) {
                    auto curr = ready.Front();
                    ready.pop(); cnt--;
                    curr->setDeliveredTime(currentTime+tot + ceil(curr->getDist() / cur->getSpeed())+curr->getLoadingTime());
                    curr->setStatus(DELIVERED_CARGO);
                    waitingCargos.remove(curr);
                    deliveredCargos.add(curr);
                }
                while (!ready.empty()) {
                    Cargos.push(ready.Front(), 100000 - ready.Front()->getReadyTime() + ready.Front()->getCost() + 100000 - ready.Front()->getDist());
                    ready.pop();
                }
            }
        }
    }
}

void Company::AssignCargos(list<cargo*>& Cargos, list<truck*>& Trucks, bool &done)
{
    if (done) return;
    int cnt = 0;
    for (int i = 0; i < Cargos.size(); i++) {
        if (Cargos.at(i)->getStatus() == WAITING_CARGO && Cargos.at(i)->getReadyTime() <= currentTime) cnt++;
    }
    for (int i = 0; !done && i < Trucks.size(); i++) {
        truck* cur = Trucks.at(i);
        if (cur->getReadyTime() <= currentTime) {
            cnt = min(cnt, cur->getCapacity());
            if (cnt == cur->getCapacity()) {
                done = true;
                int tot = 0, farest = 0, dumcnt = cnt;
                for (int j = 0; dumcnt && j < Cargos.size(); j++) {
                    if (Cargos.at(j)->getStatus() == WAITING_CARGO && Cargos.at(j)->getReadyTime() <= currentTime) {
                        tot += Cargos.at(j)->getLoadingTime();
                        farest = max(farest, Cargos.at(j)->getDist());
                        dumcnt--;
                    }
                }
                cur->setReadyTime(currentTime+(tot + ceil(farest / cur->getSpeed())) * 2);
                for (int j = 0; cnt && j < Cargos.size(); j++) {
                    if (Cargos.at(j)->getStatus() == WAITING_CARGO && Cargos.at(j)->getReadyTime() <= currentTime) {
                        Cargos.at(j)->setDeliveredTime(currentTime+tot + ceil(Cargos.at(j)->getDist() / cur->getSpeed())+ Cargos.at(j)->getLoadingTime());
                        waitingCargos.remove(Cargos.at(j));
                        deliveredCargos.add(Cargos.at(j));
                        Cargos.at(j)->setStatus(DELIVERED_CARGO);
                        cnt--;
                    }
                }
            }
        }
    }
}

void Company::AssignMaxW(list<cargo*>& Cargos, list<truck*>& Trucks, bool& done)
{
    if (done) return;
    int cnt = 0;
    for (int i = 0; i < Cargos.size(); i++) {
        if (Cargos.at(i)->getStatus() == WAITING_CARGO && currentTime - Cargos.at(i)->getReadyTime() >= maxWHours) cnt++;
    }
    for (int i = 0; i < Trucks.size(); i++) {
        auto cur = Trucks.at(i);
        if (cur->getReadyTime() <= currentTime) {
            done = true;
            int tot = 0, farest = 0;
            cnt = min(cnt, cur->getCapacity());
            int dumcnt = cnt;
            for (int j = 0; dumcnt; j++) {
                if (Cargos.at(j)->getStatus() == WAITING_CARGO && currentTime - Cargos.at(j)->getReadyTime() >= maxWHours) {
                    tot += Cargos.at(j)->getLoadingTime();
                    farest = max(farest, Cargos.at(j)->getDist());
                    dumcnt--;
                }
            }
            cur->setReadyTime(currentTime + (tot + ceil(farest / cur->getSpeed())) * 2);
            for (int j = 0; cnt; j++) {
                if (Cargos.at(j)->getStatus() == WAITING_CARGO && currentTime - Cargos.at(j)->getReadyTime() >= maxWHours) {
                    Cargos.at(j)->setDeliveredTime(currentTime + tot + ceil(Cargos.at(j)->getDist() / cur->getSpeed()) + Cargos.at(j)->getLoadingTime());
                    waitingCargos.remove(Cargos.at(j));
                    deliveredCargos.add(Cargos.at(j));
                    Cargos.at(j)->setStatus(DELIVERED_CARGO);
                    cnt--;
                }
            }
        }
    }
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