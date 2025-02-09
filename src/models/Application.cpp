//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"
#include "MyList.h"
#include "models/Admin.h"
#include "models/User.h"
#include "AutoCompletionEngine.h"
#include <limits>

Application* Application::uniqueInstance = nullptr;
Application::Application() {
    // Initialise the Report List
    reports = new MyList<std::unique_ptr<Report>>();

    // Set max Actor and Movie Id values to aid Actor/Movie creation
    maxActorId = 0;
    maxMovieId = 0;

    // Create Demo Accounts
    accounts.add("user1", std::make_unique<User>(User("user1", "password1")));
    accounts.add("user2", std::make_unique<User>(User("user2", "password2")));
    accounts.add("user3", std::make_unique<User>(User("user3", "password3")));
    accounts.add("admin1",  std::make_unique<Admin>(Admin("admin1", "password4")));
    accounts.add("admin2", std::make_unique<Admin>(Admin("admin2", "password5")));
    accounts.add("admin3", std::make_unique<Admin>(Admin("admin3", "password6")));
}

// Singleton checker/maintainer/getter
Application* Application::getInstance() {
    if (uniqueInstance == nullptr) {
        uniqueInstance = new Application();
    }
    return uniqueInstance;
}

// Getter for Account
Account* Application::getAccount(const std::string &username) {
    return (accounts.safe_get(username) != nullptr) ? accounts[username].get() : nullptr;
}

// Getters for max Actor/Movie Id
int Application::getMaxActorId() {
    return maxActorId;
}

int Application::getMaxMovieId() {
    return maxMovieId;
}

// Add/Retrieve/Update Report
void Application::addReport(Report* report) {
    reports->append(std::make_unique<Report>(*report));
}

MyList<std::unique_ptr<Report>> *Application::retrieveAllReports() {
    return reports;
}


// Setters for Actor and Movie
void Application::addActor(std::unique_ptr<Actor> actor) {
    // reminder: actors dict will OWN the pointer
    int id = actor->getId();
    actorNames.add(actor->getName(), id); // Parse Name-Id storage relation before moving object, else reference gets deleted
    actors.add(id, std::move(actor));

    // Add Actor to the Actor-to-Movie Relationship
    if (actorsToMovies[id] == nullptr) {
        actorsToMovies[id] = std::make_unique<SortedList>(SortedList());
    }

    // Update maxActorId value to prevent collision
    if (id > maxActorId) {
        maxActorId = id;
    }
}

void Application::addMovie(std::unique_ptr<Movie> movie) {
    // reminder: movies dict will OWN the pointer
    int id = movie->getId();
    movieNames.add(movie->getTitle(), id); // Parse Name-Id storage relation before moving object, else reference gets deleted
    movies.add(id, std::move(movie));

    // Add Movie to Movie-to-Actor Relationship
    if (moviesToActors[id] == nullptr) {
        moviesToActors[id] = std::make_unique<SortedList>(SortedList());
    }

    // Update maxMovieId value to prevent collision
    if (id > maxMovieId) {
        maxMovieId = id;
    }
}

bool Application::removeActor(const int id) {
    return actors.remove(id);
}

bool Application::removeMovie(const int id) {
    return movies.remove(id);
}

// Getters for Actor and Movie by Id
Actor* Application::getActor(const int id) {
    // if (actors.safe_get(id) != nullptr) {
        return actors[id].get();
    // }
    return nullptr;
}

Movie* Application::getMovie(const int id) {
    // if (movies.safe_get(id) != nullptr) {
        return movies[id].get();
    // }
    return nullptr;
}

// Getters for Actor and Movie by name
int Application::getActorIdByName(const std::string name) {
    if (actorNames.safe_get(name) != nullptr) {
        return actorNames[name];
    }
    return 0;
}

int Application::getMovieIdByName(const std::string name) {
    if (movieNames.safe_get(name) != nullptr) {
        return movieNames[name];
    }
    return 0;
}

MyList<Actor*>* Application::getAllActors() {
    return actors.values();
}

MyList<Movie*>* Application::getAllMovies() {
    return movies.values();
}

// Relationships
bool Application::addActorToMovie(const int actorId, const int movieId) {
    // Add Actor to the Actor-to-Movie Relationship
    SortedList *actorMovieIds = actorsToMovies[actorId].get();
    if (actorMovieIds == nullptr) {
        actorsToMovies[actorId] = std::make_unique<SortedList>(SortedList());
        actorMovieIds = actorsToMovies[actorId].get();
    }
    if (actorMovieIds->find(movieId) != -1) { // Check if the Relationship already exists
        return false;
    }
    actorMovieIds->insert(movieId);

    // Add Movie to Movie-to-Actor Relationship
    SortedList *movieActorIds = moviesToActors[movieId].get();
    if (movieActorIds == nullptr) {
        moviesToActors[movieId] = std::make_unique<SortedList>(SortedList());
        movieActorIds = moviesToActors[movieId].get();
    }
    if (movieActorIds->find(actorId) != -1) { // Check if the Relationship already exists
        return false;
    }
    movieActorIds->insert(actorId);

    return true;
}

bool Application::removeActorFromMovie(const int actorId, const int movieId) {
    // Check if actor or movie objects exists before deleting relationship
    if (actors.safe_get(actorId) == nullptr || movies.safe_get(movieId) == nullptr) {
        return false;
    }

    // not using std::move as we don't need ownership, we just need to modify
    SortedList* actorMovieIds = actorsToMovies[actorId].get();
    actorMovieIds->remove(movieId);

    SortedList* movieActorIds = moviesToActors[movieId].get();
    movieActorIds->remove(actorId);

    return true;
}

MyList<Actor*>* Application::getActors(const int movieId) {
    SortedList* actorIds = moviesToActors[movieId].get();
    if (actorIds == nullptr) { return nullptr; }
    auto movieActors = new MyList<Actor*>();

    for (int i = 0; i < actorIds->getLength(); i++) {
        Actor* actor = actors[actorIds->get(i)].get();
        movieActors->append(actor);
    }

    return movieActors;
}

MyList<Movie*>* Application::getMovies(int actorId) {
    SortedList* movieIds = actorsToMovies[actorId].get();
    if (movieIds == nullptr) { return nullptr; }
    auto actorMovies = new MyList<Movie*>();

    for (int i = 0; i < movieIds->getLength(); i++) {
        actorMovies->append(movies[movieIds->get(i)].get());
    }

    return actorMovies;
}

SortedList* Application::getActorMovies(int id) {
    return actorsToMovies[id].get();
}

SortedList* Application::getMovieActors(int id) {
    return moviesToActors[id].get();
}

Actor* Application::searchForActor() {
    int inputChoice;
    int actorId;

    // Input validation while true loops
    while (true) {
        // Validate search-by input (1/2)
        while (true) {
            std::cout << "=== Actor Search Options ===\n"
                     "1. Search by ID\n"
                     "2. Select by Name\n"
                     "Please choose an option: ";
            if (std::cin >> inputChoice) {
                if (inputChoice == 1 || inputChoice == 2) {
                    break;
                }
            }

            // Validate Input
            std::cout << "Invalid choice! Please enter either 1 (Id) or 2 (name)." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // If search-by-Id was selected
        if (inputChoice == 1) {
            // Validate Id
            while (true) {
                std::cout << "Please enter Actor ID: ";
                if (std::cin >> actorId) { break; }

                // Validate ActorID
                std::cout << "Invalid Actor ID! Please enter a valid ID." << std::endl;
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }
        }
        // If search-by-name was selected
        else {
            AutoCompletionEngine AutoComplete = AutoCompletionEngine(ACTOR);
            std::string name;

            // Validate name
            while (true) {
                std::cout << "Please enter actor name: ";

                // Only clear input buffer if previous input was not from getline()
                if (std::cin.peek() == '\n') {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::getline(std::cin, name);  // Read full line

                std::string actorName = AutoComplete.getUserInput(name);

                actorId = getActorIdByName(actorName);
                if (actorId != 0) {
                    break;
                }
                std::cout << "No Actor with that name was found!" << std::endl;
            }
        }

        // Validate valid Actor object (ID/Name exists in data) before passing actor to caller
        Actor* actor = getActor(actorId);
        if (actor != nullptr) {
            return actor; // All checks pass
        }
        std::cout << "Actor not found, please enter a valid Id or Name." << std::endl;
    }
}

Movie* Application::searchForMovie() {
    int inputChoice;
    int movieId;

    // Input validation while true loops
    while (true) {
        // Validate search-by input options are either 1 or 2
        while (true) {
            std::cout << "=== Movie Search Options ===\n"
                     "1. Select by ID\n"
                     "2. Select by Title\n"
                     "Please choose an option: ";
            if (std::cin >> inputChoice) {
                if (inputChoice == 1 || inputChoice == 2) {
                    break;
                }
            }

            // Validate Input
            std::cout << "Invalid choice! Please enter either 1 (Id) or 2 (name)." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // If search-by-Id was selected
        if (inputChoice == 1) {
            // Validate Id
            while (true) {
                std::cout << "Please enter Movie ID: ";
                if (std::cin >> movieId) { break; }

                // Validate MovieId
                std::cout << "Invalid Movie ID! Please enter a valid ID." << std::endl;
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }
        }
        // If search-by-name was selected
        else {
            AutoCompletionEngine AutoComplete = AutoCompletionEngine(MOVIE);
            std::string title;

            // Validate title
            while (true) {
                std::cout << "Please enter the Movie Title: ";

                // Only clear input buffer if previous input was not from getline()
                if (std::cin.peek() == '\n') {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::getline(std::cin, title);  // Read full line
                std::string movieName = AutoComplete.getUserInput(title);

                movieId = getMovieIdByName(movieName);
                if (movieId != 0) {
                    break;
                }
                std::cout << "No Movie with that name was found!" << std::endl;
            }
        }

        // Validate valid Movie object (Id/Name exists in data) before passing movie to caller
        Movie* movie = getMovie(movieId);
        if (movie != nullptr) {
            return movie; // All checks pass
        }
        std::cout << "Movie not found, please enter a valid Id or Name." << std::endl;
    }
}