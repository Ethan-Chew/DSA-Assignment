//
// Created by ethan on 15/1/2025.
//

#pragma once
#include <iostream>

#include "Account.h"
using namespace std;

class User: public Account {
public:
    using Account::Account;
};
