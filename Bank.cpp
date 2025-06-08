// Bank.cpp
#include "Bank.h"
#include <iostream>

using namespace std;

Account::Account() : balance(0.0) {}

Account::Account(const string& user, const string& pass)
    : username(user), password(pass), balance(0.0) {}

string Account::getUsername() const {
    return username;
}

bool Account::checkPassword(const string& pass) const {
    return pass == password;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    if (amount > 0) balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void Account::saveToFile(ofstream& outFile) const {
    outFile << username << " " << password << " " << balance << "\n";
}

Account Account::loadFromFile(ifstream& inFile) {
    string user, pass;
    double bal;
    inFile >> user >> pass >> bal;
    if (inFile) {
        Account acc(user, pass);
        acc.balance = bal;
        return acc;
    }
    return Account();  // 空のアカウント（無効）
}
