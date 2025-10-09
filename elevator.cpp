#include<bits/stdc++.h>
using namespace std;

enum class Direction {UP,DOWN,IDLE};
enum class ElevatorState {IDLE, MOVING, STOPPED, MAINTENANCE};  // Scoped enums avoid accidental implicit conversion to int (type-safe).

class Floor{
    int floorNumber;
    public:
    Floor(int num): floorNumber(num) {}
    int getFloorNumber() const{ return floorNumber; }
};

// =====================COMMAND PATTERN==========================
class ElevatorCommand{
    public:
    virtual void execute() = 0;
    virtual ~ElevatorCommand() {}
};

class ElevatorController;

class ElevatorRequest: public ElevatorCommand{
    int elevatorId;
    int floor;
    bool isInternal;
    Direction direction;
    ElevatorController* controller;

    public:
    ElevatorRequest(int eid, int f, bool internal, Direction dir, ElevatorController* ctrl)
    : elevatorId(eid), floor(f), isInternal(internal), direction(dir), controller(ctrl) {}

    void execute() override;

    int getFloor() const { return floor; }
    Direction getDirection() const { return direction; }
    bool isInternalRequest() const { return isInternal; }

};

// ================= OBSERVER PATTERN =================
class ElevatorObserver {
public:
    virtual void onElevatorStateChange(int elevatorId, ElevatorState state) = 0;
    virtual void onElevatorFloorChange(int elevatorId, int floor) = 0;
    virtual ~ElevatorObserver() {}
};

class ElevatorDisplay : public ElevatorObserver {
public:
    void onElevatorStateChange(int elevatorId, ElevatorState state) override {
        cout << "Elevator " << elevatorId << " state changed to " << int(state) << endl;
    }
    void onElevatorFloorChange(int elevatorId, int floor) override {
        cout << "Elevator " << elevatorId << " moved to floor " << floor << endl;
    }
};

// =====================STRATEGY PATTERN ==============================
class Elevator;
class SchedulingStrategy{
    public:
    virtual int getNextStop(Elevator* elevator) = 0;
    virtual ~SchedulingStrategy() {}
};

class FCFSSchedulingStrategy : public SchedulingStrategy {
public:
    int getNextStop(Elevator* elevator) override;
};

class ScanSchedulingStrategy : public SchedulingStrategy {
public:
    int getNextStop(Elevator* elevator) override;
};

class LookSchedulingStrategy : public SchedulingStrategy {
public:
    int getNextStop(Elevator* elevator) override;
};

class Elevator{
    int id;
    int currentFloor;
    Direction direction;
    ElevatorState state;
    queue<ElevatorRequest*> requests;
    vector<ElevatorObserver*> observers;

    public:
    Elevator(int eid) : id(eid), currentFloor(1), direction(Direction::IDLE), state(ElevatorState::IDLE) {}
    void addObserver(ElevatorObserver* ob) { observers.push_back(ob); }
    void addRequest(ElevatorRequest* req) { requests.push(req); }

    ElevatorRequest* getNextRequest(){
        if(requests.empty()) return nullptr;
        ElevatorRequest* req=requests.front();
        requests.pop();
        return req;
    }

    bool hasRequests() const { return !requests.empty(); }

    void moveToNextStop(int nextFloor){
        state=ElevatorState::MOVING;
        for(auto obs:observers){
            obs->onElevatorStateChange(id,state);
        }
        direction=(nextFloor>currentFloor) ? Direction::UP : Direction::DOWN;
        while(currentFloor!=nextFloor){
            currentFloor+=(nextFloor>currentFloor) ? 1 : -1;
            for(auto obs:observers){
                obs->onElevatorFloorChange(id,currentFloor);
            }
        }
        state=ElevatorState::STOPPED;
        for(auto obs:observers){
            obs->onElevatorStateChange(id,state);
        }
        direction=Direction::IDLE;
    }

    int getCurrentFloor() const { return currentFloor; }
    int getId() const { return id; }
    Direction getDirection() const { return direction; }
    void setDirection(Direction dir) { direction = dir; }
    ElevatorState getState() const { return state; }
};

class ElevatorController{
    vector<Elevator*> elevators;
    vector<Floor*> floors;
    SchedulingStrategy* strategy;

    public:
    ElevatorController(int numElevators, int numFloors) {
        strategy = new FCFSSchedulingStrategy();
        for (int i = 1; i <= numElevators; i++) elevators.push_back(new Elevator(i));
        for (int i = 1; i <= numFloors; i++) floors.push_back(new Floor(i));
    }
    Elevator* getElevatorById(int id){
        for(auto e:elevators){
            if(e->getId()==id) return e;
        }
        return nullptr;
    }
    void requestElevator(int eid, int floor, Direction dir){
        Elevator* e=getElevatorById(eid);
        if(e){
            e->addRequest(new ElevatorRequest(eid,floor,false,dir,this));
        }
    }
    void requestFloor(int eid, int floor){
        Elevator* e=getElevatorById(eid);
        if(e){
            Direction dir=(floor>e->getCurrentFloor()) ? Direction::UP : Direction::DOWN;
            e->addRequest(new ElevatorRequest(eid,floor,true,dir,this));
        }
    }
    void step(){
        for(auto e:elevators){
            if(e->hasRequests()){
                int nextStop=strategy->getNextStop(e);
                e->moveToNextStop(nextStop);
            }
        }
    }

    vector<Elevator*> getElevators() const { return elevators; }
};

void ElevatorRequest::execute() {
    if (isInternal)
        controller->requestFloor(elevatorId, floor);
    else
        controller->requestElevator(elevatorId, floor, direction);
}
int FCFSSchedulingStrategy::getNextStop(Elevator* elevator) {
    ElevatorRequest* req = elevator->getNextRequest();
    if (req){
        int floor=req->getFloor();
        delete req;
        return floor;
    }
    return elevator->getCurrentFloor();
}

int main(){
    ElevatorController controller(2,10);
    ElevatorDisplay display;
    for(auto e: controller.getElevators()){
        e->addObserver(&display);
    }

    controller.requestElevator(1,5,Direction::UP);
    controller.requestFloor(1,8);

    bool pending = true;
    while(pending) {
        pending = false;
        for(auto e : controller.getElevators()){
            if(e->hasRequests()) pending = true;
        }
        controller.step();
    }
    return 0;
}