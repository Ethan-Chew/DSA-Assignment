//
// Created by ethan on 14/1/2025.
//
#pragma once

#include <iostream>
using namespace std;

class Account {
private:
    string username;
    string password;
    bool isAdmin;
public:
    Account(string, string, bool);
    string getUsername();
    bool comparePassword(string);
    bool isAdministrator();
};
