//
// Created by ethan on 14/1/2025.
//

#include "models/Account.h"

// Constructor
Account::Account(std::string usrname, std::string pwd) {
    username = usrname;
    password = pwd;
}

// Default Constructor
Account::Account() {}

// Destructor
Account::~Account() { }

// Retrieve Username
std::string Account::getUsername() {
    return username;
}

// Account Functions
bool Account::comparePassword(std::string pwd) {
    if (password == pwd) {
        return true;
    }
    return false;
}