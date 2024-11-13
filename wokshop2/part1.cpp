#include <iostream>
using namespace std;

// BankAccount class with encapsulation
class BankAccount {
private:
    double balance; // balance is now private
public:
    BankAccount(double balance) : balance(balance) {}

    // Method to get the current balance (read-only)
    double getBalance() const { return balance; }

    // Method to withdraw money from the account
    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Method to deposit money into the account
    void deposit(double amount) {
        balance += amount;
    }
};

// Transaction class now uses encapsulated methods
class Transaction {
private:
    BankAccount* from;
    BankAccount* to;
    double amount;
public:
    Transaction(BankAccount* from, BankAccount* to, double amount)
        : from(from), to(to), amount(amount) {}

    bool execute() {
        if (from->withdraw(amount)) { // Use the withdraw method
            to->deposit(amount);       // Use the deposit method
            return true;
        }
        return false;
    }
};

int main() {
    BankAccount* account1 = new BankAccount(1000.0);
    BankAccount* account2 = new BankAccount(500.0);

    Transaction* transaction1 = new Transaction(account1, account2, 500.0);
    cout << (transaction1->execute() ? "Transaction successful" : "Transaction failed") << endl;

    Transaction* transaction2 = new Transaction(account1, account2, 2000.0);
    cout << (transaction2->execute() ? "Transaction successful" : "Transaction failed") << endl;

    cout << "Account 1 Balance: " << account1->getBalance() << endl;
    cout << "Account 2 Balance: " << account2->getBalance() << endl;

    delete account1;
    delete account2;
    delete transaction1;
    delete transaction2;
    return 0;
}
