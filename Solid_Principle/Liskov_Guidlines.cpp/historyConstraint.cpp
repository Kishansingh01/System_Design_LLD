#include <iostream>
#include <stdexcept>
using namespace std;

// Parent class
class BankAccount {
protected:
    double balance;

public:
    BankAccount(double b) {
        if (b < 0)
            throw invalid_argument("Balance cannot be negative");

        balance = b;
    }

    // Parent contract:
    // Every BankAccount should allow withdrawal if sufficient funds exist.
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
// FixedDepositAccount changes the expected behavior.
class FixedDepositAccount : public BankAccount {
public:
    FixedDepositAccount(double b) : BankAccount(b) {}

    void withdraw(double amount) override {
        throw runtime_error(
            "Withdraw not allowed in Fixed Deposit Account");
    }
};

int main() {
    try {
        cout << "Normal BankAccount:\n";

        BankAccount* account1 = new BankAccount(100);
        account1->withdraw(50);
        delete account1;

        cout << "\nFixedDepositAccount (LSP Violation):\n";

        BankAccount* account2 = new FixedDepositAccount(100);
        account2->withdraw(50);   // Throws exception

        delete account2;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}