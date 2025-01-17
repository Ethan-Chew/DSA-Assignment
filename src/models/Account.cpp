//
// Created by ethan on 14/1/2025.
//

#include "models/Account.h"

Account::Account(string usrname, string pwd, bool usrIsAdmin) {
    username = usrname;
    password = pwd;
    isAdmin = usrIsAdmin;
}
string Account::getUsername() {
    return username;
}
bool Account::comparePassword(string pwd) {
    if (password == pwd) {
        return true;
    }
    return false;
}
bool Account::isAdministrator() {
    return isAdmin;
}
