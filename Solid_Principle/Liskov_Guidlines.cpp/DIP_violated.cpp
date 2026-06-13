#include<iostream>
using namespace std;

class MySQLDatabase{ // Low-level module
    public:
        void saveToSQL(string data){
            cout<< " Executing SQL query :INSERT INTO users VALUES"<< data<< endl;
        }
};
class MongoDBDatabase{ // Low level module
    public:
        void saveToMongo(string data){
            cout<<"Executing mongoDB function: db.users.insert"<<data<<endl;
        }

};
class UserService{ // High level module (Tightly coupled)
    private:
        MySQLDatabase sqlDb; // Direct dependency on MYSQL
        MongoDBDatabase mongodb; // Direct dependency on MongoDB
    public:
        void storeUserToSQL(string user){
            sqlDb.saveToSQL(user);
        }
        void storeUserToMongo(string user){
            mongodb.saveToMongo(user);
        }
};

int main(){
    UserService service;
    service.storeUserToMongo("Raj");
    service.storeUserToSQL("Aditya");

}