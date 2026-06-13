#include<iostream>
#include<string>

using namespace std;

// Base Car class
class Car {
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string b, string m) {
        brand = b;
        model = m;
        isEngineOn = false;
        currentSpeed = 0;
    }

    // Common methods
    void startEngine() {
        isEngineOn = true;

        cout << brand << " " << model
             << ": Engine started" << endl;
    }

    void stopEngine() {
        isEngineOn = false;
        currentSpeed = 0;

        cout << brand << " " << model
             << ": Engine turned off" << endl;
    }

    // Pure virtual functions
    virtual void accelerate() = 0;

    // Function overloading with virtual function
    virtual void accelerate(int speed) = 0;

    virtual void brake() = 0;

    virtual ~Car() {}
};

// ManualCar class
class ManualCar : public Car {
private:
    int currentGear;

public:
    ManualCar(string brand, string model)
        : Car(brand, model) {

        currentGear = 0;
    }

    // Unique method
    void shiftGear(int gear) {
        currentGear = gear;

        cout << brand << " " << model
             << ": Shifted to gear "
             << currentGear << endl;
    }

    // Overriding accelerate()
    void accelerate() override {

        if (!isEngineOn) {
            cout << brand << " " << model
                 << ": Engine is off." << endl;
            return;
        }

        currentSpeed += 20;

        cout << brand << " " << model
             << ": Accelerating to "
             << currentSpeed << " km/h" << endl;
    }

    // Overloading + overriding
    void accelerate(int speed) override {

        if (!isEngineOn) {
            cout << brand << " " << model
                 << ": Engine is off." << endl;
            return;
        }

        currentSpeed += speed;

        cout << brand << " " << model
             << ": Accelerating to "
             << currentSpeed << " km/h" << endl;
    }

    // Overriding brake()
    void brake() override {

        currentSpeed -= 20;

        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model
             << ": Braking! Speed is now "
             << currentSpeed << " km/h" << endl;
    }
};

// ElectricCar class
class ElectricCar : public Car {
private:
    int batteryLevel;

public:
    ElectricCar(string b, string m)
        : Car(b, m) {

        batteryLevel = 100;
    }

    // Unique method
    void chargeBattery() {

        batteryLevel = 100;

        cout << brand << " " << model
             << ": Battery fully charged!"
             << endl;
    }

    // Overriding accelerate()
    void accelerate() override {

        if (!isEngineOn) {
            cout << brand << " " << model
                 << ": Engine is off." << endl;
            return;
        }

        if (batteryLevel <= 0) {
            cout << brand << " " << model
                 << ": Battery dead!" << endl;
            return;
        }

        batteryLevel -= 10;
        currentSpeed += 15;

        cout << brand << " " << model
             << ": Accelerating to "
             << currentSpeed
             << " km/h. Battery at "
             << batteryLevel << "%" << endl;
    }

    // Overloading + overriding
    void accelerate(int speed) override {

        if (!isEngineOn) {
            cout << brand << " " << model
                 << ": Engine is off." << endl;
            return;
        }

        if (batteryLevel <= 0) {
            cout << brand << " " << model
                 << ": Battery dead!" << endl;
            return;
        }

        batteryLevel -= 10;
        currentSpeed += speed;

        cout << brand << " " << model
             << ": Accelerating to "
             << currentSpeed
             << " km/h. Battery at "
             << batteryLevel << "%" << endl;
    }

    // Overriding brake()
    void brake() override {

        currentSpeed -= 15;

        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model
             << ": Regenerative braking! Speed is now "
             << currentSpeed
             << " km/h" << endl;
    }
};

// Main function
int main() {

    Car* myManualCar =
        new ManualCar("Suzuki", "WagonR");

    myManualCar->startEngine();
    myManualCar->accelerate();
    myManualCar->accelerate(40);
    myManualCar->brake();
    myManualCar->stopEngine();

    cout << "-------------------" << endl;

    Car* myElectricCar =
        new ElectricCar("Tesla", "Model S");

    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->accelerate(50);
    myElectricCar->brake();
    myElectricCar->stopEngine();

    // Cleanup
    delete myManualCar;
    delete myElectricCar;

    return 0;
}