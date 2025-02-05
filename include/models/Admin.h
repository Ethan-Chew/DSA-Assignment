//
// Created by ethan on 5/2/2025.
//

#include "Account.h"

class Admin: public Account {
public:
    Admin(std::string, std::string);
    virtual bool isUserAdmin() const override;
};
