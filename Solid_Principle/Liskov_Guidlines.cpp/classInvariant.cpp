#include <iostream>
#include <stdexcept>
using namespace std;

// Parent class invariant:
// Balance can never be negative.
class BankAccount {
protected:
    double balance;

public:
    BankAccount(double b) {
        if (b < 0)
            throw invalid_argument("Balance cannot be negative");
        balance = b;
    }

    virtual void withdraw(double amount) {
        if (balance - amount < 0)
            throw runtime_error("Insufficient funds");

        balance -= amount;
        cout << "Amount withdrawn. Remaining balance is "
             << balance << endl;
    }

    virtual ~BankAccount() = default;
};

// LSP Violation:
// Child class breaks the invariant by allowing negative balance.
class CheatAccount : public BankAccount {
public:
    CheatAccount(double b) : BankAccount(b) {}

    void withdraw(double amount) override {
        balance -= amount; // LSP violation
        cout << "Amount withdrawn. Remaining balance is "
             << balance << endl;
    }
};

int main() {
    try {
        cout << "Normal BankAccount:\n";
        BankAccount* account1 = new BankAccount(100);
        account1->withdraw(50);
        delete account1;

        cout << "\nCheatAccount (LSP Violation):\n";
        BankAccount* account2 = new CheatAccount(100);
        account2->withdraw(200); // Allows negative balance
        delete account2;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

// Normal BankAccount:
// Amount withdrawn. Remaining balance is 50

// CheatAccount (LSP Violation):
// Amount withdrawn. Remaining balance is -100