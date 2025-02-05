//
// Created by ethan on 5/2/2025.
//

#include "models/User.h"

User::User(std::string usrname, std::string pwd): Account(usrname, pwd) { }
bool User::isUserAdmin() const {
    return false;
}
