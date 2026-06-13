#include <iostream>
#include <string>

using namespace std;

// Product 1 -> Burger

class Burger {
public:
    virtual void prepare() = 0;
    virtual ~Burger() {}
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun." << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty and veggies." << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with bun, patty, cheese, lettuce and special sauce." << endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger." << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger with wheat bun." << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Wheat Burger with wheat bun, cheese and special sauce." << endl;
    }
};

// Product 2 -> Garlic Bread

class GarlicBread {
public:
    virtual void prepare() = 0;
    virtual ~GarlicBread() {}
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Basic Garlic Bread." << endl;
    }
};

class CheeseGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Cheese Garlic Bread." << endl;
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Garlic Bread." << endl;
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Cheese Wheat Garlic Bread." << endl;
    }
};

// Abstract Factory

class MealFactory {
public:
    virtual Burger* createBurger(const string& type) = 0;
    virtual GarlicBread* createGarlicBread(const string& type) = 0;
    virtual ~MealFactory() {}
};

// Concrete Factory 1

class SinghBurger : public MealFactory {
public:
    Burger* createBurger(const string& type) override {
        if (type == "basic") {
            return new BasicBurger();
        }
        else if (type == "standard") {
            return new StandardBurger();
        }
        else if (type == "premium") {
            return new PremiumBurger();
        }

        cout << "Invalid Burger Type!" << endl;
        return nullptr;
    }

    GarlicBread* createGarlicBread(const string& type) override {
        if (type == "basic") {
            return new BasicGarlicBread();
        }
        else if (type == "cheese") {
            return new CheeseGarlicBread();
        }

        cout << "Invalid Garlic Bread Type!" << endl;
        return nullptr;
    }
};

// Concrete Factory 2

class KingBurger : public MealFactory {
public:
    Burger* createBurger(const string& type) override {
        if (type == "basic") {
            return new BasicWheatBurger();
        }
        else if (type == "standard") {
            return new StandardWheatBurger();
        }
        else if (type == "premium") {
            return new PremiumWheatBurger();
        }

        cout << "Invalid Burger Type!" << endl;
        return nullptr;
    }

    GarlicBread* createGarlicBread(const string& type) override {
        if (type == "basic") {
            return new BasicWheatGarlicBread();
        }
        else if (type == "cheese") {
            return new CheeseWheatGarlicBread();
        }

        cout << "Invalid Garlic Bread Type!" << endl;
        return nullptr;
    }
};

int main() {

    string burgerType = "premium";
    string garlicBreadType = "cheese";

    // Choose the restaurant/factory
    MealFactory* mealFactory = new KingBurger();

    Burger* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread =
        mealFactory->createGarlicBread(garlicBreadType);

    if (burger)
        burger->prepare();

    if (garlicBread)
        garlicBread->prepare();

    // Cleanup
    delete burger;
    delete garlicBread;
    delete mealFactory;

    return 0;
}