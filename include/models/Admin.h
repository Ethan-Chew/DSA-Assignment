//
// Created by ethan on 5/2/2025.
//

#include "Account.h"

class Admin: public Account {
public:
    Admin(std::string, std::string);
    bool isUserAdmin() const override;

    // Admin Features (Basic)
    void addNewActor();
    void addNewMovie();
    void addActorToMovie();
    void updateActorOrMovie();
    void printAll();
};
