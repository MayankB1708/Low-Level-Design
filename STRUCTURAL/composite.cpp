#include<bits/stdc++.h>
using namespace std;

class SmartComponent {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~SmartComponent() = default;
};

class AirConditioner : public SmartComponent {
public:
    void turnOn() override {
        cout << "Air Conditioner is now ON." << endl;
    }
    void turnOff() override {
        cout << "Air Conditioner is now OFF." << endl;
    }
};

class SmartLight : public SmartComponent {
public:
    void turnOn() override {
        cout << "Smart Light is now ON." << endl;
    }
    void turnOff() override {
        cout << "Smart Light is now OFF." << endl;
    }
};

class CompositeSmartComponent : public SmartComponent {
private:
    vector<SmartComponent*> components;
public:
    void addComponent(SmartComponent* component) {
        components.push_back(component);
    }
    void removeComponent(SmartComponent* component) {
        components.erase(remove(components.begin(), components.end(), component), components.end());
    }
    void turnOn() override {
        for (auto* component : components) {
            component->turnOn();
        }
    }
    void turnOff() override {
        for (auto* component : components) {
            component->turnOff();
        }
    }
};

int main() {
    SmartComponent* airConditioner = new AirConditioner();
    SmartComponent* smartLight = new SmartLight();

    CompositeSmartComponent* room1 = new CompositeSmartComponent();
    room1->addComponent(airConditioner);
    room1->addComponent(smartLight);

    CompositeSmartComponent* room2 = new CompositeSmartComponent();
    room2->addComponent(new AirConditioner());
    room2->addComponent(new SmartLight());

    CompositeSmartComponent* floor1 = new CompositeSmartComponent();
    floor1->addComponent(room1);
    floor1->addComponent(room2);

    CompositeSmartComponent* room3 = new CompositeSmartComponent();
    room3->addComponent(new AirConditioner());
    room3->addComponent(new SmartLight());

    CompositeSmartComponent* room4 = new CompositeSmartComponent();
    room4->addComponent(new AirConditioner());
    room4->addComponent(new SmartLight());

    CompositeSmartComponent* floor2 = new CompositeSmartComponent();
    floor2->addComponent(room1);
    floor2->addComponent(room2);

    CompositeSmartComponent* house = new CompositeSmartComponent();
    house->addComponent(floor1);
    house->addComponent(floor2);

    cout << "Turning ON all devices in the house:" << endl;
    house->turnOn();

    cout << "\nTurning OFF all devices in the house:" << endl;
    house->turnOff();

    cout << "\nTurning ON all devices on the first floor:" << endl;
    floor1->turnOn();

    cout << "\nTurning OFF all devices on the first floor:" << endl;
    floor1->turnOff();

    cout << "\nTurning ON all devices in Room 1:" << endl;
    room1->turnOn();

    cout << "\nTurning OFF all devices in Room 1:" << endl;
    room1->turnOff();

    delete house;
    delete floor1;
    delete floor2;
    delete room1;
    delete room2;
    delete room3;
    delete room4;
    delete airConditioner;
    delete smartLight;

    return 0;
}
