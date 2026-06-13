#include <iostream>
using namespace std;

// Abstraction
class Database {
public:
    virtual void save(string data) = 0;
};

// MySQL implementation
class MySQLDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing SQL Query: Insert into users: "
             << data << endl;
    }
};

// MongoDB implementation
class MongoDBDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing MongoDB function: db.users.insert("
             << data << ")" << endl;
    }
};

// High-level module
class UserService {
private:
    Database* db;

public:
    UserService(Database* database) {
        db = database;
    }

    void storeUser(string user) {
        db->save(user);
    }
};

int main() {
    MySQLDatabase sqlDb;
    MongoDBDatabase mongoDb;

    UserService service1(&sqlDb);
    service1.storeUser("Aditya");

    UserService service2(&mongoDb);
    service2.storeUser("Rajaa");

    return 0;
}