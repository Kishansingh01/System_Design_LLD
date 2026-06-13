#include<iostream>
#include<string>

using namespace std;

class SportsCar {

private:
    // Attributes
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;

public:

    // Constructor
    SportsCar(string b, string m) {

        this->brand = b;
        this->model = m;

        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
    }

    // Getter
    int getCurrentSpeed() {
        return currentSpeed;
    }

    // Start engine
    void startEngine() {

        isEngineOn = true;

        cout << brand << " " << model
             << ": Engine starts with a roar!"
             << endl;
    }

    // Shift gear
    void shiftGear(int gear) {

        if (!isEngineOn) {

            cout << brand << " " << model
                 << ": Engine is off, cannot shift gear."
                 << endl;

            return;
        }

        currentGear = gear;

        cout << brand << " " << model
             << ": Shifted to gear "
             << currentGear << endl;
    }

    // Accelerate
    void accelerate() {

        if (!isEngineOn) {

            cout << brand << " " << model
                 << ": Engine is off, cannot accelerate."
                 << endl;

            return;
        }

        currentSpeed += 20;

        cout << brand << " " << model
             << ": Accelerating to "
             << currentSpeed
             << " km/h" << endl;
    }

    // Brake
    void brake() {

        currentSpeed -= 20;

        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model
             << ": Braking! Speed is now "
             << currentSpeed
             << " km/h" << endl;
    }

    // Stop engine
    void stopEngine() {

        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;

        cout << brand << " " << model
             << ": Engine turned off"
             << endl;
    }
};

int main() {

    SportsCar* mySportsCar =
        new SportsCar("Ford", "Mustang");

    mySportsCar->startEngine();

    mySportsCar->shiftGear(1);

    mySportsCar->accelerate();

    mySportsCar->shiftGear(2);

    mySportsCar->accelerate();

    mySportsCar->brake();

    mySportsCar->stopEngine();

    // Access speed using getter
    cout << "Current speed: "
         << mySportsCar->getCurrentSpeed()
         << " km/h" << endl;

    delete mySportsCar;

    return 0;
}