#include<bits/stdc++.h>
using namespace std;

class ParkingFeeStrategy{
    public: 
    virtual double calculateFee(const string& vehicletype, int hours) =0;
    virtual ~ParkingFeeStrategy() {}
};

class BasicStrategy: public ParkingFeeStrategy{
    public:
    double calculateFee(const string& vehicletype, int hours) override {
        if(vehicletype=="car") return hours*10.0;
        else if(vehicletype=="bike") return hours*5.0;
        return hours*8.0;
    }
};

class PremiumStrategy: public ParkingFeeStrategy{
    public:
    double calculateFee(const string& vehicletype, int hours) override {
        if(vehicletype=="car") return hours*15.0;
        else if(vehicletype=="bike") return hours*8.0;
        return hours*12.0;
    }
};

class Vehicle{
    protected:
    string license;
    string vehicletype;
    ParkingFeeStrategy* pfs;

    public:
    Vehicle(string lp, string vt, ParkingFeeStrategy* fs): license(lp), vehicletype(vt), pfs(fs) {}
    virtual ~Vehicle() {}

    string getVehicleType() const { return vehicletype; }
    string getLicensePlate() const { return license; }

    double calculateFee(int hours) {
        return pfs->calculateFee(vehicletype, hours);
    }
};

class Car: public Vehicle{
    public:
    Car(string lp, ParkingFeeStrategy* fs): Vehicle(lp,"car",fs){}
};

class Bike: public Vehicle{
    public:
    Bike(string lp, ParkingFeeStrategy* fs): Vehicle(lp,"bike",fs) {}
};

class VehicleFactory{
    public:
    static Vehicle* createVehicle(const string& vehicletype, const string& lp, ParkingFeeStrategy* fs){
        if(vehicletype=="car") return new Car(lp,fs);
        else if(vehicletype=="bike") return new Bike(lp,fs);
        return nullptr;
    }
};

class PaymentStrategy{
    public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

class CashPayment: public PaymentStrategy{
    public:
    void processPayment(double amount) override{
        cout<<"Processing cash payment of Rs. "<<amount<<endl;
    }
};

class CardPayment: public PaymentStrategy{
    public:
    void processPayment(double amount) override{
        cout<<"Processing card payment of Rs. "<<amount<<endl;
    }
};

class ParkingSpot{
    protected:
    int spotnumber;
    bool occupied;
    Vehicle* vehicle;
    string spottype;

    public:
    ParkingSpot(int num, string st): spotnumber(num), occupied(false), vehicle(nullptr), spottype(st) {}
    virtual ~ParkingSpot() {}

    bool isOccupied() { return occupied; }
    int getSpotNumber() { return spotnumber; }
    string getSpotType() { return spottype; }
    Vehicle* getVehicle() { return vehicle; }

    virtual bool canParkVehicle(Vehicle* ) = 0;

    void parkVehicle(Vehicle* v){
        if(occupied) throw runtime_error("Spot already occupied");
        if(!canParkVehicle(v)) throw runtime_error("Spot not suitable for " + v->getVehicleType());
        vehicle=v;
        occupied=true;
    }
    void vacate(){
        if(!occupied) throw runtime_error("Spot already vacant.");
        vehicle=nullptr;
        occupied=false;
    }
};

class CarParkingSpot: public ParkingSpot{
    public:
    CarParkingSpot(int num): ParkingSpot(num,"car"){}
    bool canParkVehicle(Vehicle* v) override{
        return v->getVehicleType()=="car";
    }
};

class BikeParkingSpot: public ParkingSpot{
    public:
    BikeParkingSpot(int num): ParkingSpot(num,"bike") {}
    bool canParkVehicle(Vehicle* v) override{
        return v->getVehicleType()=="bike";
    }
};

class ParkingLot{
    vector<ParkingSpot*> spots;
    public:
    ParkingLot(const vector<ParkingSpot*> &s) : spots(s) {}

    ParkingSpot* findAvailableSpot(const string& vehicletype){
        for(auto spot:spots){
            if(!spot->isOccupied() && spot->getSpotType()==vehicletype) return spot;
        }
        return nullptr;
    }

    ParkingSpot* parkVehicle(Vehicle* v){
        ParkingSpot* spot=findAvailableSpot(v->getVehicleType());
        if(spot){
            spot->parkVehicle(v);
            cout<<"Vehicle parked in spot "<<spot->getSpotNumber()<<endl;
            return spot;
        }
        cout<<"No available spots for "<<v->getVehicleType()<<endl;
        return nullptr;
    }

    void vacateSpot(ParkingSpot* spot, Vehicle* v){
        if(spot && spot->isOccupied() && spot->getVehicle()==v){
            spot->vacate();
            cout<<v->getVehicleType()<<" vacated spot "<<spot->getSpotNumber()<<endl;
        }
        else cout<<"Invalid vacate operation"<<endl;
    }
};

int main(){
    vector<ParkingSpot*> spots;
    spots.push_back(new CarParkingSpot(1));
    spots.push_back(new CarParkingSpot(2));
    spots.push_back(new CarParkingSpot(3));
    spots.push_back(new BikeParkingSpot(4));
    spots.push_back(new BikeParkingSpot(5));
    spots.push_back(new BikeParkingSpot(6));

    ParkingLot lot(spots);

    ParkingFeeStrategy* basic=new BasicStrategy();
    ParkingFeeStrategy* premium=new PremiumStrategy();

    Vehicle* car1=VehicleFactory::createVehicle("car","car123",basic);
    Vehicle* bike1=VehicleFactory::createVehicle("bike","bike456",premium);

    ParkingSpot* carspot=lot.parkVehicle(car1);
    ParkingSpot* bikespot=lot.parkVehicle(bike1);

    PaymentStrategy* ps=new CashPayment();
    ps->processPayment(car1->calculateFee(5));
    PaymentStrategy* ps1=new CardPayment();
    ps1->processPayment(bike1->calculateFee(3));

    delete ps1;
    delete ps;
    delete car1;
    delete bike1;
    delete basic;
    delete premium;
    for(auto spot:spots) delete spot;

    return 0;
}