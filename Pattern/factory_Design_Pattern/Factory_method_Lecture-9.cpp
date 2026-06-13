#include<iostream>
using namespace std;

// Product class and subclasses

class Burger{
    public:
        virtual void prepare()=0; // Pure virtual function
        virtual ~Burger(){} // Virtual destructure.
};

class BasicBurger: public Burger{
    public:
        void prepare() override{
            cout<<" Preparing basic burger with bunnn"
        }
};

class standardBurger: public Burger{
    public:
        void prepare() override{
            cout<< "Preparing standard burger with bun.."<<endl;
        }
};
class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with bun, patty, cheese, lettuce and special sauce!" << endl;
    }
};
class BasicWheatBurger: public Burger{
    public:
        void prepare() override{
            cout<<" Preparing basic wheat burger..."<<endl;
        }
};
class standardWheatBurger: public Burger{
    public:
        void prepare() override{
            cout<<"Preparing standard wheat burger with bunn";
        }
};
class premiumWheatBurger: public Burger{
    public:
        void prepare() override{
            cout<<"Preparing premium wheat burger with bunn";
        }
};

// Factory and its concreations
class BurgerFactory{
    public:
        virtual Burger* createBurger(string& type)= 0;
};
class SinghBurger: public BurgerFactory{
    public:
        Burger* createBurger(string$ type) override{
            if(type=="basic"){
                return new BasicBurger();
            }else if(type=="standard"){
                return new standardBurger();
            }else if(type=="premium"){
                return new PremiumBurger();
            }else{
                    cout<<"Invalid burger type!"<<endl;
                    return nullptr;
            }

        }
};

class KingBurger: public BurgerFactory{
    public:
        Burger* createBurger(string& type) override{
            if(type=="basic"){
                return new BasicWheatBurger();
            }else if(type=="standard"){
                return new standardWheatBurger();
            }else if(type=="premium"){
                return new PremiumBurger();
            }else{
                cout<<"Invalid burger type!"<<endl;
                return nullptr;
            }
        }
};
int main(){
    string type="basic";
    BurgerFactory* myFactory=new KingBurger();
    Burger* burger= myFactory->createBurger(type);
    burger->prepare();

    return 0;
}