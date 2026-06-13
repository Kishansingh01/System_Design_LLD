#include <iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0; // Pure virtual function
    virtual ~Burger() {}        // Virtual destructor
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty and ketchup!" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, cheese and ketchup!" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with bun, patty, cheese, lettuce and special sauce!" << endl;
    }
};

class BurgerFactory {
public:
    Burger* createBurger(const string& type) {
        if (type == "basic") {
            return new BasicBurger();
        }
        else if (type == "standard") {
            return new StandardBurger();
        }
        else if (type == "premium") {
            return new PremiumBurger();
        }
        else {
            cout << "Invalid burger type!" << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "standard";

    BurgerFactory* myBurgerFactory = new BurgerFactory();

    Burger* burger = myBurgerFactory->createBurger(type);

    if (burger != nullptr) {
        burger->prepare();
        delete burger;
    }

    delete myBurgerFactory;

    return 0;
}