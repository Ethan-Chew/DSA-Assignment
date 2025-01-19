//
// Created by ethan on 14/1/2025.
//
#pragma once

#include <iostream>
using namespace std;

class Account {
private:
    std::string username;
    std::string password;
    bool isAdmin;
public:
    Account(std::string, std::string, bool);
    std::string getUsername();
    bool comparePassword(std::string);
    bool isAdministrator();
};
