#include <bits/stdc++.h>
using namespace std;

// ---------------- Base Interfaces ----------------
class Car {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Car() {}
};

class Bike {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Bike() {}
};

class Truck {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Truck() {}
};

// ---------------- Honda Vehicles ----------------
class HondaCar : public Car {
public:
    void start() override { cout << "Honda Car starting\n"; }
    void stop() override { cout << "Honda Car stopping\n"; }
};

class HondaBike : public Bike {
public:
    void start() override { cout << "Honda Bike starting\n"; }
    void stop() override { cout << "Honda Bike stopping\n"; }
};

class HondaTruck : public Truck {
public:
    void start() override { cout << "Honda Truck starting\n"; }
    void stop() override { cout << "Honda Truck stopping\n"; }
};

// ---------------- Toyota Vehicles ----------------
class ToyotaCar : public Car {
public:
    void start() override { cout << "Toyota Car starting\n"; }
    void stop() override { cout << "Toyota Car stopping\n"; }
};

class ToyotaBike : public Bike {
public:
    void start() override { cout << "Toyota Bike starting\n"; }
    void stop() override { cout << "Toyota Bike stopping\n"; }
};

class ToyotaTruck : public Truck {
public:
    void start() override { cout << "Toyota Truck starting\n"; }
    void stop() override { cout << "Toyota Truck stopping\n"; }
};

// ---------------- BMW Vehicles ----------------
class BMWCar : public Car {
public:
    void start() override { cout << "BMW Car starting\n"; }
    void stop() override { cout << "BMW Car stopping\n"; }
};

class BMWBike : public Bike {
public:
    void start() override { cout << "BMW Bike starting\n"; }
    void stop() override { cout << "BMW Bike stopping\n"; }
};

class BMWTruck : public Truck {
public:
    void start() override { cout << "BMW Truck starting\n"; }
    void stop() override { cout << "BMW Truck stopping\n"; }
};

// ---------------- Abstract Factory ----------------
class VehicleFactory {
public:
    virtual Car* createCar() = 0;
    virtual Bike* createBike() = 0;
    virtual Truck* createTruck() = 0;
    virtual ~VehicleFactory() {}
};

// ---------------- Concrete Factories ----------------
class HondaFactory : public VehicleFactory {
public:
    Car* createCar() override { return new HondaCar(); }
    Bike* createBike() override { return new HondaBike(); }
    Truck* createTruck() override { return new HondaTruck(); }
};

class ToyotaFactory : public VehicleFactory {
public:
    Car* createCar() override { return new ToyotaCar(); }
    Bike* createBike() override { return new ToyotaBike(); }
    Truck* createTruck() override { return new ToyotaTruck(); }
};

class BMWFactory : public VehicleFactory {
public:
    Car* createCar() override { return new BMWCar(); }
    Bike* createBike() override { return new BMWBike(); }
    Truck* createTruck() override { return new BMWTruck(); }
};

// ---------------- Client Code ----------------
int main() {
    VehicleFactory* hondaFactory = new HondaFactory();
    Car* hondaCar = hondaFactory->createCar();
    Bike* hondaBike = hondaFactory->createBike();
    Truck* hondaTruck = hondaFactory->createTruck();

    hondaCar->start(); hondaCar->stop();
    hondaBike->start(); hondaBike->stop();
    hondaTruck->start(); hondaTruck->stop();

    VehicleFactory* toyotaFactory = new ToyotaFactory();
    Car* toyotaCar = toyotaFactory->createCar();
    Bike* toyotaBike = toyotaFactory->createBike();
    Truck* toyotaTruck = toyotaFactory->createTruck();

    toyotaCar->start(); toyotaCar->stop();
    toyotaBike->start(); toyotaBike->stop();
    toyotaTruck->start(); toyotaTruck->stop();

    VehicleFactory* bmwFactory = new BMWFactory();
    Car* bmwCar = bmwFactory->createCar();
    Bike* bmwBike = bmwFactory->createBike();
    Truck* bmwTruck = bmwFactory->createTruck();

    bmwCar->start(); bmwCar->stop();
    bmwBike->start(); bmwBike->stop();
    bmwTruck->start(); bmwTruck->stop();

    // cleanup
    delete hondaCar; delete hondaBike; delete hondaTruck; delete hondaFactory;
    delete toyotaCar; delete toyotaBike; delete toyotaTruck; delete toyotaFactory;
    delete bmwCar; delete bmwBike; delete bmwTruck; delete bmwFactory;

    return 0;
}
