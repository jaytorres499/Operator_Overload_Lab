//Assignment: Lab Activities: Advanced Objects and Classes II
//Date: 2/9/26
//Author: Jeziel Torres
#include <iostream>
using namespace std;
#include <vector>

class BankAccount {
    public:
        BankAccount();
        BankAccount(const BankAccount& other) = default;
        BankAccount& operator=(const BankAccount& other) = default;
        ~BankAccount() = default;
        BankAccount(string name, string number, double money) {
            accountName = name;
            accountNumber = number;
            balance = money;;
        }
        //Setters
        void SetName(string name) {
            accountName = name;
        }
        //Getters
        string GetName() {
            return accountName;
        }
        string GetNumber() {
            return accountNumber;
        }
        double GetBalance() {
            return balance;
        }
        //+/- Operators
        BankAccount& operator+=(double amount) {
            if (amount > -1) {
                balance += amount;
            }
            return *this;
        }
        BankAccount& operator-=(double amount) {
            if (amount > -1 && balance > amount) {
                balance -= amount;
            }
            else {
                if (amount < 0) {
                    cout << "Amount cannot be negative." << endl;
                }
                if (amount > balance) {
                    cout << "Insufficient funds." << endl;
                }
            }
            return *this;
        }
        //Comparison functions
        bool operator==(const BankAccount& other) const {
            return accountNumber == other.accountNumber;
        }
        bool operator<(const BankAccount& other) const {
            return balance < other.balance;
        }
        bool operator>(const BankAccount& other) const {
            return balance > other.balance;
        }
        //Static Utility Functions
        static void printAccount(const BankAccount& account) {
            cout << "Account Name: " << account.accountName << endl;
            cout << "Account Number: " << account.accountNumber << endl;
            cout << "Balance: " << account.balance << endl;
        }
        static BankAccount createAccountFromInput() {
            string name;
            string number;
            double money;
            cout << "Enter account name:" << endl;
            cin >> name;
            cout << "Enter account number:" << endl;
            cin >> number;
            cout << "Enter account balance:" << endl;
            cin >> money;
            BankAccount account(name, number, money);
            cout << "Created Account " << name << " with account number " << number << " with a balance of $" << money << endl;
            return account;
        }

    private:
        string accountNumber;
        string accountName;
        double balance;

};


int main() {
    vector<BankAccount> accounts;
    int choice;
    int viewAccount;
    int accountChoice;
    double amountChange;
    string accountNameInput;

    do {
        cout << "Bank Account Manager" << endl;
        cout << "1. Create Account" << endl << "2. View Accounts" << endl << "3. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                accounts.push_back(BankAccount::createAccountFromInput());
                break;
            case 2:
                cout << "Choose account to view:" << endl;
                for (int i = 0; i < accounts.size(); i++) {
                    cout << i + 1 << ". " << accounts[i].GetName() << endl;
                }
                cin >> viewAccount;
                if (viewAccount > accounts.size()) {
                    cout << "Invalid account choice" << endl;
                    break;
                }
                accountChoice = 0;
                while (accountChoice != -1) {
                    BankAccount::printAccount(accounts[viewAccount - 1]);
                    cout << "1. Change Name" << endl << "2. Deposit" << endl << "3. Withdraw" << endl << "4. Compare Account" << endl << "-1. Exit" << endl;
                    cin >> accountChoice;
                    if (accountChoice > 4 || accountChoice < -1) {
                        cout << "Invalid Choice" << endl;
                    }
                    else if (accountChoice == 1) {
                        cout << "Enter new account name:" << endl;
                        cin >> accountNameInput;
                        accounts[viewAccount - 1].SetName(accountNameInput);
                    }
                    else if (accountChoice == 2) {
                        cout << "Enter amount to deposit:" << endl;
                        cin >> amountChange;
                        accounts[viewAccount - 1] += amountChange;
                    }
                    else if (accountChoice == 3) {
                        cout << "Enter amount to withdraw:" << endl;
                        cin >> amountChange;
                        if (accounts[viewAccount - 1].GetBalance() < amountChange) {
                            cout << "Insufficient Funds" << endl;
                        }
                        else {
                            accounts[viewAccount - 1] -= amountChange;
                            cout << "New Balance: " << accounts[viewAccount - 1].GetBalance() << endl;
                        }
                    }
                    else if (accountChoice == 4) {
                        int compareAccount = 0;
                        cout << "Choose account to compare:" << endl;
                        for (int i = 0; i < accounts.size(); i++) {
                            cout << i + 1 << ". " << accounts[i].GetName() << endl;
                        }
                        cin >> compareAccount;
                        if (compareAccount > accounts.size()) {
                            cout << "Invalid account choice" << endl;
                        }
                        else {
                            if (accounts[viewAccount - 1] == accounts[compareAccount - 1]) {
                                cout << "Same Account Number: True" << endl;
                            }
                            else {
                                cout << "Same Account Number: False" << endl;
                            }
                            if (accounts[viewAccount - 1] > accounts[compareAccount - 1]) {
                                cout << accounts[viewAccount - 1].GetName() << " has a larger balance than " << accounts[compareAccount - 1].GetName() << endl << endl;
                            }
                            else if (accounts[viewAccount - 1] < accounts[compareAccount - 1]) {
                                cout << accounts[viewAccount - 1].GetName() << " has a smaller balance than " << accounts[compareAccount - 1].GetName() << endl << endl;
                            }
                        }
                    }
                }
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
        }
    }while (choice != 3); {
        return 0;
    }
}