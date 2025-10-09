#include<bits/stdc++.h>
using namespace std;


class SmartDevice {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~SmartDevice() = default; // virtual destructor for cleanup
};

class AirConditioner {
public:
    void connectViaBluetooth() {
        cout << "Air Conditioner connected via Bluetooth." << endl;
    }
    void startCooling() {
        cout << "Air Conditioner is now cooling." << endl;
    }
    void stopCooling() {
        cout << "Air Conditioner stopped cooling." << endl;
    }
    void disconnectBluetooth() {
        cout << "Air Conditioner disconnected from Bluetooth." << endl;
    }
};

class SmartLight {
public:
    void connectToWiFi() {
        cout << "Smart Light connected to Wi-Fi." << endl;
    }
    void switchOn() {
        cout << "Smart Light is now ON." << endl;
    }
    void switchOff() {
        cout << "Smart Light is now OFF." << endl;
    }
    void disconnectWiFi() {
        cout << "Smart Light disconnected from Wi-Fi." << endl;
    }
};

class CoffeeMachine {
public:
    void initializeZigbeeConnection() {
        cout << "Coffee Machine connected via Zigbee." << endl;
    }
    void startBrewing() {
        cout << "Coffee Machine is now brewing coffee." << endl;
    }
    void stopBrewing() {
        cout << "Coffee Machine stopped brewing coffee." << endl;
    }
    void terminateZigbeeConnection() {
        cout << "Coffee Machine disconnected from Zigbee." << endl;
    }
};

class AirConditionerAdapter : public SmartDevice {
private:
    AirConditioner* airConditioner;
public:
    AirConditionerAdapter(AirConditioner* ac){
        this->airConditioner=ac;
    }

    void turnOn() override {
        airConditioner->connectViaBluetooth();
        airConditioner->startCooling();
    }
    void turnOff() override {
        airConditioner->stopCooling();
        airConditioner->disconnectBluetooth();
    }
};

class SmartLightAdapter : public SmartDevice {
private:
    SmartLight* smartLight;
public:
    SmartLightAdapter(SmartLight* light){
        this->smartLight=light;
    }

    void turnOn() override {
        smartLight->connectToWiFi();
        smartLight->switchOn();
    }
    void turnOff() override {
        smartLight->switchOff();
        smartLight->disconnectWiFi();
    }
};

class CoffeeMachineAdapter : public SmartDevice {
private:
    CoffeeMachine* coffeeMachine;
public:
    CoffeeMachineAdapter(CoffeeMachine* cm){
        this->coffeeMachine=cm;
    }

    void turnOn() override {
        coffeeMachine->initializeZigbeeConnection();
        coffeeMachine->startBrewing();
    }
    void turnOff() override {
        coffeeMachine->stopBrewing();
        coffeeMachine->terminateZigbeeConnection();
    }
};

int main() {
    SmartDevice* airConditioner = new AirConditionerAdapter(new AirConditioner());
    SmartDevice* smartLight = new SmartLightAdapter(new SmartLight());
    SmartDevice* coffeeMachine = new CoffeeMachineAdapter(new CoffeeMachine());

    airConditioner->turnOn();
    smartLight->turnOn();
    coffeeMachine->turnOn();

    airConditioner->turnOff();
    smartLight->turnOff();
    coffeeMachine->turnOff();

    delete airConditioner;
    delete smartLight;
    delete coffeeMachine;

    return 0;
}
