// main.cpp
#include "Bank.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<Account> loadAccounts(const string& filename) {
    vector<Account> accounts;
    ifstream inFile(filename);
    while (inFile) {
        Account acc = Account::loadFromFile(inFile);
        if (!acc.getUsername().empty()) {
            accounts.push_back(acc);
        }
    }
    return accounts;
}

void saveAccounts(const vector<Account>& accounts, const string& filename) {
    ofstream outFile(filename);
    for (const auto& acc : accounts) {
        acc.saveToFile(outFile);
    }
}

int main() {
    vector<Account> accounts = loadAccounts("accounts.txt");
    string username, password;
    int choice;

    while (true) {
        cout << "\n=== Bank Management System ===\n";
        cout << "1. Create Account\n2. Login\n3. Exit\n> ";
        cin >> choice;

        if (choice == 1) {
            cout << "New Username: ";
            cin >> username;
            cout << "New Password: ";
            cin >> password;
            accounts.emplace_back(username, password);
            cout << "Account created!\n";
        }
        else if (choice == 2) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            bool found = false;
            for (auto& acc : accounts) {
                if (acc.getUsername() == username && acc.checkPassword(password)) {
                    found = true;
                    int userChoice;
                    do {
                        cout << "\nWelcome, " << username << "!\n";
                        cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Logout\n> ";
                        cin >> userChoice;
                        if (userChoice == 1) {
                            cout << "Balance: $" << acc.getBalance() << "\n";
                        }
                        else if (userChoice == 2) {
                            double amount;
                            cout << "Amount to deposit: ";
                            cin >> amount;
                            acc.deposit(amount);
                            cout << "Deposited!\n";
                        }
                        else if (userChoice == 3) {
                            double amount;
                            cout << "Amount to withdraw: ";
                            cin >> amount;
                            if (acc.withdraw(amount)) {
                                cout << "Withdrawn!\n";
                            }
                            else {
                                cout << "Insufficient balance.\n";
                            }
                        }
                    } while (userChoice != 4);
                    break;
                }
            }
            if (!found) cout << "Invalid credentials.\n";
        }
        else if (choice == 3) {
            saveAccounts(accounts, "accounts.txt");
            cout << "Thank you for using!\n";
            break;
        }
    }

    return 0;
}
