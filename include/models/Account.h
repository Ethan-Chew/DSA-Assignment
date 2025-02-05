//
// Created by ethan on 14/1/2025.
//
#pragma once

#include <iostream>

class Account {
private:
    std::string username;
    std::string password;
public:
    Account(std::string, std::string);
    Account();
    ~Account();
    std::string getUsername();
    virtual bool isUserAdmin() const = 0;
    bool comparePassword(std::string);
};
