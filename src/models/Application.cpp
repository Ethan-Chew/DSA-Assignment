//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"
#include "MyList.h"
#include "models/Admin.h"
#include "models/User.h"

Application* Application::uniqueInstance = nullptr;
Application::Application() {
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
    if (actors.safe_get(id) != nullptr) {
        return actors[id].get();
    }
    return nullptr;
}

Movie* Application::getMovie(const int id) {
    if (movies.safe_get(id) != nullptr) {
        return movies[id].get();
    }
    return nullptr;
}

// Getters for Actor and Movie by name
Actor* Application::getActorByName(const std::string name) {
    if (actorNames.safe_get(name) != nullptr) {
        return actors[actorNames[name]].get();
    }
    return nullptr;
}

Movie* Application::getMovieByName(const std::string name) {
    if (movieNames.safe_get(name) != nullptr) {
        return movies[movieNames[name]].get();
    }
    return nullptr;
}

MyList<Actor*>* Application::getAllActors() {
    return actors.values();
}

MyList<Movie*>* Application::getAllMovies() {
    return movies.values();
}

// Relationships
bool Application::addActorToMovie(const int actorId, const int movieId) {
    // Check if actor or movie objects exists before creating relationship
    if (actors.safe_get(actorId) == nullptr || movies.safe_get(movieId) == nullptr) {
        return false;
    }

    // Add Actor to the Actor-to-Movie Relationship
    SortedList *actorMovieIds = actorsToMovies[actorId].get();
    if (actorMovieIds == nullptr) {
        actorsToMovies[actorId] = std::make_unique<SortedList>(SortedList());
        actorMovieIds = actorsToMovies[actorId].get();
    }
    actorMovieIds->insert(movieId);

    // Add Movie to Movie-to-Actor Relationship
    SortedList *movieActorIds = moviesToActors[movieId].get();
    if (movieActorIds == nullptr) {
        moviesToActors[movieId] = std::make_unique<SortedList>(SortedList());
        movieActorIds = moviesToActors[movieId].get();
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
