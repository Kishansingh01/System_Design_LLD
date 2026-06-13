#include<iostream>
using namespace std;

class Singleton{
    private:
        Singleton(){
            cout << "Singleton constructor called " <<endl;
        }
    public:
        static Singleton* getInstance(){
            return new Singleton();
        }
};
int main(){
    Singleton* s1=Singleton::getInstance();
    Singleton* s2=Singleton::getInstance();

    cout<<(s1==s2) <<endl;
}