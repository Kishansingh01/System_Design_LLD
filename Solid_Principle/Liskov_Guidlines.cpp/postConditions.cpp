#include<iostream>
using namespace std;

// A postcondition must be satisfied after a method is executed.
// Sub classes can strengthen the postcondition but cannot weaken it.

class Car{
    protected:
        int speed;
    public:
        Car(){
            speed=0;
        }
        void accelerate(){
            cout <<"Accelerating" << endl;
            speed += 20;
        }
    // PostCondition: Speed must reduce after brake.
    virtual void brake(){
        cout << "Applying brakes" << endl;
        speed -= 20;
    }
};

// Subclass can strengthen postCondition - Does not violated LSP
class HybridCar : public Car{
    private:
        int charge;
    public:
        HybridCar() : Car(){
            charge=0;
        }
        // PostCondition: Speed must reduce after brake
        // PostCondition: Charge must increase.
        void brake(){
            cout << "Applying brakes" << endl;
            speed -= 20;
            charge += 10;
        }
};

int main(){
    Car* hybridCar= new HybridCar();
    hybridCar->brake(); // Works fine : Hybrid Car reduces speed and also increase charge.

    // Client feels no difference in substituting Hybrid car in place of Car
    return 0;
    
}