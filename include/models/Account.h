/*
* Created By: Ethan Chew (S10255990K), Darius Koh (S10255626K), Lim Yu Yang (S10255816J)
* Group: 4
*/
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
