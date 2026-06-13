#include <iostream>
#include <stdexcept>
using namespace std;

// Precondition Rule:
// A subclass may weaken preconditions but must not strengthen them.

class User {
public:
    // Precondition: Password must be at least 8 characters long
    virtual void setPassword(string password) {
        if (password.length() < 8) {
            throw invalid_argument(
                "Password must be at least 8 characters long!");
        }

        cout << "Password set successfully in User" << endl;
    }

    virtual ~User() = default;
};

class AdminUser : public User {
public:
    // Weakened precondition:
    // Only 6 characters required instead of 8
    void setPassword(string password) override {
        if (password.length() < 6) {
            throw invalid_argument(
                "Password must be at least 6 characters long!");
        }

        cout << "Password set successfully in AdminUser" << endl;
    }
};

int main() {
    try {
        User* user = new AdminUser();

        user->setPassword("Admin1"); // 6 chars, works

        delete user;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}