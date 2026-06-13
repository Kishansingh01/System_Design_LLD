#include<iostream>
using namespace std;

class Parent{
    public:
        virtual void getValue() noexcept (false) {
            // Parent throw logic_error exception
            throw logic_error("Parent error");

        }
};
class Child: public Parent{
    public: 
        void getValue() noexcept(false) override{ // Child throws out_of_range exception
            throw out_of_range("Child error");
        }
};

class Client{
    private:
        Parent*p;
    public:
        Client(Parent*p){
            this->p=p;
        }
        void takeValue(){
            try{
            p->getValue();
            }
            catch(const logic_error& e){
                cout<<"Logic error exception occured : "<< e.what() << endl;
            }
        }
};

int main(){
    Parent * parent= new Parent();
    Child* child =new Child();

    Client* Client= new Client(child);
    client->takeValue();

    return 0;
}