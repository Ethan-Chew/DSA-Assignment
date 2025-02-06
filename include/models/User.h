//
// Created by ethan on 5/2/2025.
//

#include "Account.h"

class User: public Account {
public:
    User(std::string, std::string);
    bool isUserAdmin() const override;

    // User Features (Basic)
    void displayActors();
    void displayMovies();
    void displayActorMovies();
    void displayActorsInMovie();
    void displayKnownActors();
    void fileReport();

    // User Features (Advanced)
    void displayAndSortMovies();
    void displayAndSortActors();
    void findDistanceBetweenActors();
};