//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"
#include "MyLinkedList.h"
#include <MyLinkedList.h>

Application* Application::uniqueInstance = nullptr;
Application::Application() {
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

Account* Application::getAccount(const std::string &username) {
    return accounts[username].get();
}

// Setters for Actor and Movie
void Application::addActor(std::unique_ptr<Actor> actor) {
    int id = actor->getId();
    // reminder: actors dict will OWN the pointer
    actors.add(id, std::move(actor));
}

void Application::addMovie(std::unique_ptr<Movie> movie) {
    // reminder: movies dict will OWN the pointer
    int id = movie->getId();
    movies.add(id, std::move(movie));
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
