#include <iostream>
#include <string>

using namespace std;

// Component Interface
class Character {
public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {}
};

// Concrete Component
class Mario : public Character {
public:
    string getAbilities() const override {
        return "Mario";
    }
};

// Abstract Decorator
class CharacterDecorator : public Character {
protected:
    Character* character;

public:
    CharacterDecorator(Character* c) {
        character = c;
    }

    virtual ~CharacterDecorator() {
        delete character;
    }
};

// Height Power-Up Decorator
class HeightUp : public CharacterDecorator {
public:
    HeightUp(Character* c) : CharacterDecorator(c) {}

    string getAbilities() const override {
        return character->getAbilities() + " + HeightUp";
    }
};

// Gun Power-Up Decorator
class GunPowerUp : public CharacterDecorator {
public:
    GunPowerUp(Character* c) : CharacterDecorator(c) {}

    string getAbilities() const override {
        return character->getAbilities() + " + Gun";
    }
};

// Star Power-Up Decorator
class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) {}

    string getAbilities() const override {
        return character->getAbilities() + " + Power Star (Limited Time)";
    }

    ~StarPowerUp() {
        cout << "Destroying Star Power Decorator" << endl;
    }
};

int main() {

    Character* mario = new Mario();

    cout << "Basic Character: "
         << mario->getAbilities()
         << endl;

    mario = new HeightUp(mario);
    cout << "After HeightUp: "
         << mario->getAbilities()
         << endl;

    mario = new GunPowerUp(mario);
    cout << "After GunPowerUp: "
         << mario->getAbilities()
         << endl;

    mario = new StarPowerUp(mario);
    cout << "After StarPowerUp: "
         << mario->getAbilities()
         << endl;

    delete mario;

    return 0;
}