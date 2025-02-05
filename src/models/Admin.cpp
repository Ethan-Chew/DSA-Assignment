//
// Created by ethan on 5/2/2025.
//

#include "models/Admin.h"

Admin::Admin(std::string usrname, std::string pwd): Account(usrname, pwd) { }
bool Admin::isUserAdmin() const {
    return true;
}
