//
// Created by ethan on 5/2/2025.
//

#include "Account.h"

class User: public Account {
public:
    User(std::string, std::string);
    virtual bool isUserAdmin() const override;
};