// Bank.h
#pragma once
#include <string>
#include <fstream>

class Account {
private:
    std::string username;
    std::string password;
    double balance;

public:
    Account();
    Account(const std::string& user, const std::string& pass);

    std::string getUsername() const;
    bool checkPassword(const std::string& pass) const;

    double getBalance() const;
    void deposit(double amount);
    bool withdraw(double amount);

    void saveToFile(std::ofstream& outFile) const;
    static Account loadFromFile(std::ifstream& inFile);
};
