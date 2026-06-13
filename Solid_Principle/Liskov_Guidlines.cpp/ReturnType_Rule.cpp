
// Return Type rule:
// Subtype overridden method return type should be either identical
// or narrower then the parent method's return type
//This is also called as return type type covariance
// C++ enforces this by covariance

// Since Dog is a subtype of Animal, returning Dog* is allowed.

#include <iostream>
using namespace std;

// Base class
class Animal {
public:
    virtual ~Animal() = default;
};

// Derived class
class Dog : public Animal {
};

// Parent class
class Parent {
public:
    virtual Animal* getAnimal() {
        cout << "Parent: returning Animal instance" << endl;
        return new Animal();
    }

    virtual ~Parent() = default;
};

// Child class
class Child : public Parent {
public:
    Dog* getAnimal() override {   // Covariant return type
        cout << "Child: returning Dog instance" << endl;
        return new Dog();
    }
};

// Client class
class Client {
private:
    Parent* p;

public:
    Client(Parent* p) {
        this->p = p;
    }

    void takeAnimal() {
        Animal* animal = p->getAnimal();
        delete animal;
    }
};

int main() {
    Parent* parent = new Parent();
    Child* child = new Child();

    Client* client = new Client(child);

    client->takeAnimal();

    delete client;
    delete child;
    delete parent;

    return 0;
}

// Output
// Child: returning Dog instance