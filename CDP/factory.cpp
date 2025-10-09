#include<bits/stdc++.h>
using namespace std;
class Vehicle{
    public:
    virtual void start()=0;
    virtual void stop()=0;
    virtual ~Vehicle() {}
};
class Car: public Vehicle{
    public:
    void start() override{
        cout<<"Car is starting"<<endl;
    }
    void stop() override{
        cout<<"Car stopped"<<endl;
    }
};
class Bike: public Vehicle{
    public:
    void start() override{
        cout<<"Bike is starting"<<endl;
    }
    void stop() override{
        cout<<"Bike stopped"<<endl;
    }
};
class Truck: public Vehicle{
    public:
    void start() override{
        cout<<"Truck is starting"<<endl;
    }
    void stop() override{
        cout<<"Truck stopped"<<endl;
    }
};
class VehicleFactory{
    public:
    static Vehicle* getVehicle(const string &type){
        if(type=="Car") return new Car();
        else if(type=="Bike") return new Bike();
        else if(type=="Truck") return new Truck();
        else{
            throw invalid_argument("Unknown vehicle type: "+type);
        }
    }
};
int main(){
    try{
        Vehicle* v1=VehicleFactory::getVehicle("Car");
        v1->start();
        v1->stop();
        delete v1;

        Vehicle* v2=VehicleFactory::getVehicle("Bus");
        v2->start();
        v2->stop();
        delete v2;

        Vehicle* v3=VehicleFactory::getVehicle("Truck");
        v3->start();
        v3->stop();
        delete v3;
    }
    catch(const invalid_argument &e){
        cout<<"Error: "<<e.what()<<endl;
    }
    return 0;
}