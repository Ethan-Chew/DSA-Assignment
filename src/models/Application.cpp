//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"
#include "MyLinkedList.h"
#include <MyLinkedList.h>

Application* Application::uniqueInstance = nullptr;
Application::Application() {
    // Set max Actor and Movie Id values to aid Actor/Movie creation
    maxActorId = 0;
    maxMovieId = 0;

    // Create Demo Accounts
    accounts.add("user1", std::make_unique<Account>(Account("user1", "password1", false)));
    accounts.add("user2", std::make_unique<Account>(Account("user2", "password2", false)));
    accounts.add("user3", std::make_unique<Account>(Account("user3", "password3", false)));
    accounts.add("admin1",  std::make_unique<Account>(Account("admin1", "password4", true)));
    accounts.add("admin2", std::make_unique<Account>(Account("admin2", "password5", true)));
    accounts.add("admin3", std::make_unique<Account>(Account("admin3", "password6", true)));
}

Application* Application::getInstance() {
    if (uniqueInstance == nullptr) {
        uniqueInstance = new Application();
    }
    return uniqueInstance;
}

// Getter for Account
Account* Application::getAccount(const std::string &username) {
    return accounts[username].get();
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

// Getters for Actor and Movie
Actor* Application::getActor(const int id) {
    if (actors[id] != nullptr) {
        return actors[id].get();
    }
    return nullptr;
}

MyLinkedList<Actor*>* Application::getAllActors() {
    return actors.values();
}

MyList<Actor*> Application::getAllActorsList() {
    MyLinkedList<Actor*>* tmp = actors.values();
    MyList<Actor*> result;
    
    for (int i = 0; i < tmp->get_length(); i++) {
        result.append(tmp->get(i));
    }
    
    return result;
}

MyList<Movie*> Application::getAllMoviesList() {
    MyLinkedList<Movie*>* tmp = movies.values();
    MyList<Movie*> result;
    
    for (int i = 0; i < tmp->get_length(); i++) {
        result.append(tmp->get(i));
    }
    
    return result;
}

MyLinkedList<Movie*>* Application::getAllMovies() {
    return movies.values();
}

Movie* Application::getMovie(const int id) {
    if (movies[id] != nullptr) {
        return movies[id].get();
    }
    return nullptr;
}

// Relationships
bool Application::addActorToMovie(const int actorId, const int movieId) {
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
    // not using std::move as we don't need ownership, we just need to modify
    SortedList* actorMovieIds = actorsToMovies[actorId].get();
    actorMovieIds->remove(movieId);

    SortedList* movieActorIds = moviesToActors[movieId].get();
    movieActorIds->remove(actorId);

    return true;
}

MyLinkedList<Actor*>* Application::getActors(const int movieId) {
    SortedList* actorIds = moviesToActors[movieId].get();
    if (actorIds == nullptr) { return nullptr; }
    auto movieActors = new MyLinkedList<Actor*>();

    for (int i = 0; i < actorIds->getLength(); i++) {
        Actor* actor = actors[actorIds->get(i)].get();
        movieActors->append(actor);
    }

    return movieActors;
}

MyLinkedList<Movie*>* Application::getMovies(int actorId) {
    SortedList* movieIds = actorsToMovies[actorId].get();
    if (movieIds == nullptr) { return nullptr; }
    auto actorMovies = new MyLinkedList<Movie*>();

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

// const MyDict<int, SortedList*>& Application::getActorsToMoviesRelationship() const {
//     return actorsToMovies;
// }
// const MyDict<int, SortedList *> &Application::getMoviesToActorsRelationship() const {
//     return moviesToActors;
// }
