#include "Company.h"
#include <math.h>

#include <iostream>
using namespace std;

Company::Company()
{
	currentTime = 0;
    activeTime = 0;
    promotedCargos = 0;
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
            Normal_Trucks.push(c);
            break;
        case SPECIAL_TRUCK:
            Special_Trucks.push(c);
            break;
        case VIP_TRUCK:
            VIP_Trucks.push(c);
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

void Company::SendTrucksForCheckUp(){

    /*SendTrucksForCheckUp(Normal_Trucks);
    SendTrucksForCheckUp(Special_Trucks);
    SendTrucksForCheckUp(VIP_Trucks);*/
}

bool Company::SendTruckForCheckUp(truck* &ls)
{
    if (ls->getNumberOfJournies() == ls->getMaxJournies()) {
        ls->setReadyTime(currentTime + ls->getCheckUpTime());
        checkUpTrucks.add(ls);
        return true;
    }
    return false;
}

void Company::checkCheckupTrucks()
{
    list<truck*> &checkUpTrucksIn = checkUpTrucks;
    for(int i=0;i<checkUpTrucksIn.size();i++){
        auto cur = checkUpTrucksIn.at(i);
        if(cur->getReadyTime() == currentTime){
            cur->setNumberOfJournies(0);
            checkUpTrucks.remove(cur);
            addTruck(cur);
            i--;
        }
    }
}


void Company::CheckAutoPromotion()
{
    list<cargo*>& ls = Normal_Cargos;
    for (int i = 0; i < ls.size(); i++) {
        if (currentTime - ls.at(i)->getReadyTime() >= autoPromotionLimitHours && ls.at(i)->getStatus() == WAITING_CARGO){
            promoteCargo(ls.at(i)->getID());
            promotedCargos++;
        }
    }
}

void Company::AssignCargos(){
    // GET EMPTY VIP TRUCKS, NORMAl, SPECIAL

    bool DoneVIP, DoneSpecial, DoneNormal;
    DoneVIP = DoneSpecial = DoneNormal = false;

    AssignMaxW(VIP_Cargos, VIP_Trucks, DoneVIP);
    AssignMaxW(VIP_Cargos, Normal_Trucks, DoneNormal);
    AssignMaxW(VIP_Cargos, Special_Trucks, DoneSpecial);

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

void Company::AssignCargos(priority_queue<cargo*>& Cargos, queue<truck*>& Trucks, bool& done)
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

    if(ready.empty() || Trucks.empty()) return;

    while(!done && !Trucks.empty()) {
        truck* cur = Trucks.Front();
        if (cur->getReadyTime() <= currentTime) {
            if (ready.size() >= cur->getCapacity()) {
                Trucks.pop();
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
                cur->setMoveTime(currentTime + tot);
                cur->setReadyTime(currentTime+(tot + ceil(1.0 * farest / cur->getSpeed())) * 2);
                availableTrucks.remove(cur);
                loadingTrucks.add(cur);
                cur->setStatus(LOADING_TRUCK);
                movingTrucks.push(cur, -cur->getReadyTime());
                cur->setNumberOfJournies(cur->getNumberOfJournies()+1);
                activeTime += (tot + ceil(farest / cur->getSpeed()));
                cur->setActiveTime(cur->getActiveTime() + tot + ceil(1.0 * farest / cur->getSpeed()));
                cnt = cur->getCapacity();

                while (cnt && !ready.empty()) {
                    auto curr = ready.Front();
                    ready.pop(); cnt--;
                    curr->setTruckDeliveredID(cur->getID());
                    curr->setWaitTime(currentTime - curr->getReadyTime());
                    curr->setDeliveredTime(currentTime+tot + ceil(1.0 * curr->getDist() / cur->getSpeed())+curr->getLoadingTime());
                    activeTime += curr->getLoadingTime();
                    cur->setActiveTime(cur->getActiveTime() + curr->getLoadingTime());
                    curr->setStatus(DELIVERED_CARGO);
                    cur->setTotalCargos(cur->getTotalCargos()+1);
                    movingCargos.add(curr);
                    deliveredCargos.add(curr);
                    waitingCargos.remove(curr);
                }
            } else break;
        }
    }

    while (!ready.empty()) {
        Cargos.push(ready.Front(), 100000 - ready.Front()->getReadyTime() + ready.Front()->getCost() + 100000 - ready.Front()->getDist());
        ready.pop();
    }


}

void Company::AssignCargos(list<cargo*>& Cargos, queue<truck*>& Trucks, bool &done)
{
    if (done || Trucks.empty()) return;
    int cnt = 0;
    for (int i = 0; i < Cargos.size(); i++) {
        if (Cargos.at(i)->getStatus() == WAITING_CARGO && Cargos.at(i)->getReadyTime() <= currentTime) cnt++;
    }
    if(!cnt) return;
    while(!done && !Trucks.empty()) {
        truck* cur = Trucks.Front();
        if (cur->getReadyTime() <= currentTime) {
            cnt = min(cnt, cur->getCapacity());
            if (cnt == cur->getCapacity()) {
                Trucks.pop();
                done = true;
                int tot = 0, farest = 0, dumcnt = cnt;
                for (int j = 0; dumcnt && j < Cargos.size(); j++) {
                    if (Cargos.at(j)->getStatus() == WAITING_CARGO && Cargos.at(j)->getReadyTime() <= currentTime) {
                        tot += Cargos.at(j)->getLoadingTime();
                        farest = max(farest, Cargos.at(j)->getDist());
                        dumcnt--;
                    }
                }
                cur->setReadyTime(currentTime+(tot + ceil(1.0 * farest / cur->getSpeed())) * 2);
                cur->setMoveTime(currentTime + tot);
                movingTrucks.push(cur, -cur->getReadyTime());
                availableTrucks.remove(cur);
                loadingTrucks.add(cur);
                cur->setNumberOfJournies(cur->getNumberOfJournies()+1);
                activeTime += (tot + ceil(farest / cur->getSpeed()));
                cur->setActiveTime(cur->getActiveTime() + tot + ceil(1.0 * farest / cur->getSpeed()));
                for (int j = 0; cnt && j < Cargos.size(); j++) {
                    if (Cargos.at(j)->getStatus() == WAITING_CARGO && Cargos.at(j)->getReadyTime() <= currentTime) {
                        Cargos.at(j)->setTruckDeliveredID(cur->getID());
                        Cargos.at(j)->setWaitTime(currentTime - Cargos.at(j)->getReadyTime());
                        Cargos.at(j)->setDeliveredTime(currentTime+tot + ceil(1.0 * Cargos.at(j)->getDist() / cur->getSpeed())+ Cargos.at(j)->getLoadingTime());
                        activeTime += Cargos.at(j)->getLoadingTime();
                        cur->setActiveTime(cur->getActiveTime() + activeTime);
                        Cargos.at(j)->setStatus(DELIVERED_CARGO);
                        cur->setTotalCargos(cur->getTotalCargos()+1);
                        movingCargos.add(Cargos.at(j));
                        deliveredCargos.add(Cargos.at(j));
                        waitingCargos.remove(Cargos.at(j));
                        j--;
                        cnt--;
                    }
                }
            } else break;
        }
    }
}

void Company::AssignMaxW(list<cargo*>& Cargos, queue<truck*>& Trucks, bool& done)
{
    if (done || Trucks.empty()) return;
    int cnt = 0;
    for (int i = 0; i < Cargos.size(); i++) {
        if (Cargos.at(i)->getStatus() == WAITING_CARGO && currentTime - Cargos.at(i)->getReadyTime() >= maxWHours) cnt++;
    }
    if(!cnt) return;
    while(!done && !Trucks.empty()) {
        auto cur = Trucks.Front();
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
            Trucks.pop();
            cur->setReadyTime(currentTime + (tot + ceil(1.0 * farest / cur->getSpeed())) * 2);
            cur->setMoveTime(currentTime + tot);
            movingTrucks.push(cur, -cur->getReadyTime());
            availableTrucks.remove(cur);
            loadingTrucks.add(cur);
            cur->setNumberOfJournies(cur->getNumberOfJournies()+1);
            activeTime += (tot + ceil(farest / cur->getSpeed()));
            cur->setActiveTime(cur->getActiveTime() + tot + ceil(1.0 * farest / cur->getSpeed()));
            for (int j = 0; cnt; j++) {
                if (Cargos.at(j)->getStatus() == WAITING_CARGO && currentTime - Cargos.at(j)->getReadyTime() >= maxWHours) {
                    Cargos.at(j)->setTruckDeliveredID(cur->getID());
                    Cargos.at(j)->setWaitTime(currentTime - Cargos.at(j)->getReadyTime());
                    Cargos.at(j)->setDeliveredTime(currentTime + tot + ceil(1.0 * Cargos.at(j)->getDist() / cur->getSpeed()) + Cargos.at(j)->getLoadingTime());
                    activeTime += Cargos.at(j)->getLoadingTime();
                    cur->setActiveTime(cur->getActiveTime() + activeTime);
                    Cargos.at(j)->setStatus(DELIVERED_CARGO);
                    deliveredCargos.add(Cargos.at(j));
                    waitingCargos.remove(Cargos.at(j));
                    movingCargos.add(Cargos.at(j));
                    cur->setTotalCargos(cur->getTotalCargos()+1);
                    j--;
                    cnt--;
                }
            }
        }
    }
}

void Company::AssignMaxW(priority_queue<cargo*>& Cargos, queue<truck*>& Trucks, bool& done) {
    if (done || Trucks.empty()) return;
    priority_queue<cargo *> ready, to_be_back;
    while (!Cargos.empty()) {
        auto cur = Cargos.Front();
        Cargos.pop();
        if (currentTime - cur->getReadyTime() >= maxWHours) ready.push(cur,
                                                                       1000000 - cur->getReadyTime() + cur->getCost() +
                                                                       100000 - cur->getDist());
        else to_be_back.push(cur, 0);


    }
    while (!to_be_back.empty()) {
        auto cur = to_be_back.Front();
        to_be_back.pop();
        Cargos.push(cur, 1000000 - cur->getReadyTime() + cur->getCost() + 100000 - cur->getDist());
    }
    if (ready.empty()) return;
    while (!done && !Trucks.empty()) {
        auto cur = Trucks.Front();
        int cnt = cur->getCapacity();

        if (cur->getReadyTime() <= currentTime) {
            done = true;
            int tot = 0, farest = 0;
            cnt = cur->getCapacity();
            int dumcnt = cnt;
            priority_queue<cargo *> dum(ready);
            while (dumcnt && !dum.empty()) {
                auto curr = dum.Front();
                dum.pop();
                if (curr->getStatus() == WAITING_CARGO) {
                    tot += curr->getLoadingTime();
                    farest = max(farest, curr->getDist());
                    dumcnt--;
                }
            }
            Trucks.pop();

            cur->setReadyTime(currentTime + (tot + ceil(1.0 * farest / cur->getSpeed())) * 2);
            cur->setMoveTime(currentTime + tot);
            loadingTrucks.add(cur);
            movingTrucks.push(cur, -cur->getReadyTime());
            availableTrucks.remove(cur);
            cur->setNumberOfJournies(cur->getNumberOfJournies() + 1);
            activeTime += (tot + ceil(farest / cur->getSpeed()));
            cur->setActiveTime(cur->getActiveTime() + tot + ceil(1.0 * farest / cur->getSpeed()));
            while (cnt && !ready.empty()) {
                auto curr = ready.Front();
                ready.pop();
                if (curr->getStatus() == WAITING_CARGO) {
                    curr->setTruckDeliveredID(cur->getID());
                    curr->setWaitTime(currentTime - curr->getReadyTime());
                    curr->setDeliveredTime(
                            currentTime + tot + ceil(1.0 * curr->getDist() / cur->getSpeed()) + curr->getLoadingTime());
                    activeTime += curr->getLoadingTime();
                    cur->setActiveTime(cur->getActiveTime() + activeTime);
                    curr->setStatus(DELIVERED_CARGO);
                    deliveredCargos.add(curr);
                    waitingCargos.remove(curr);
                    movingCargos.add(curr);
                    cur->setTotalCargos(cur->getTotalCargos() + 1);
                    cnt--;
                }
            }
        } else break;
    }

    while (!ready.empty()) {
        Cargos.push(ready.Front(), 100000 - ready.Front()->getReadyTime() + ready.Front()->getCost() + 100000 -
                                   ready.Front()->getDist());
        ready.pop();
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

list<cargo*>& Company::getMovingCargos(){
    return movingCargos;
}

list<truck*>& Company::getLoadingTrucks(){
    return loadingTrucks;
}

list<truck*>& Company::getEmptyTrucks(){
    return availableTrucks;
}

list<truck*>& Company::getCheckUpTrucks(){
    return checkUpTrucks;
}

list<cargo*>& Company::getDeliveredCargos(){
    return deliveredCargos;
}

void Company::addTrucks(int N, TruckType typ, int speed, int capacity, int journies, int durationCheckup, int id){
    for(int i=0;i<N;i++){
        truck* t = new truck(capacity, durationCheckup, speed, journies, typ, AVAILABLE_TRUCK, id+i+1);
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
			cargos.remove(cargos.at(i));
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

void Company::checkEachHour() {

    for(int i=0;i<movingCargos.size();i++){
        if(movingCargos.at(i)->getDeliveredTime() <= currentTime){
            movingCargos.remove(movingCargos.at(i));
            i--;
        }
    }
    this->checkLoadingTrucks();
    this->CheckAutoPromotion();
    this->executeEvents();
    this->checkReturningTrucks();
    this->checkCheckupTrucks();
    if (this->getCurrentTime() % 24 > 4 && this->getCurrentTime() % 24 < 23) {
        this->AssignCargos();
    }
}

void Company::getCalculations(priority_queue<cargo*> &cs, list<truck*> &ls){
    for(int i=0;i<deliveredCargos.size();i++){
        cargo* c = deliveredCargos.at(i);
        cs.push(c, c->getDeliveredTime());
    }

    ls = availableTrucks;
}

int Company::getPromotedCargos(){
    return promotedCargos;
}

int Company::getActiveTime(){
    return activeTime;
}

void Company::checkLoadingTrucks(){
    list<truck*> &loading = loadingTrucks;
    for(int i=0;i<loading.size();i++){
        if(loading.at(i)->getMoveTime() <= currentTime) {
            loading.at(i)->setStatus(MOVING_TRUCK);
            loading.remove(loading.at(i));
            i--;
        }
    }
}

void Company::checkReturningTrucks(){
    priority_queue<truck*> &returning = movingTrucks;
    while(!returning.empty() &&  returning.Front()->getReadyTime() <= currentTime){
        auto returningTruck = returning.Front();
        returning.pop();
        bool is = SendTruckForCheckUp(returningTruck);
        if(!is){
            addTruck(returningTruck);
        }
    }
}