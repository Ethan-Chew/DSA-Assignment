//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"
#include "DoubleLinkedList.h"
#include <MyLinkedList.h>

Application* Application::uniqueInstance = nullptr;
Application::Application() {
    accounts.add("user1", new Account("user1", "password1", false));
    accounts.add("user2", new Account("user2", "password2", false));
    accounts.add("user3", new Account("user3", "password3", false));
    accounts.add("admin1", new Account("admin1", "password4", true));
    accounts.add("admin2", new Account("admin2", "password5", true));
    accounts.add("admin3", new Account("admin3", "password6", true));
}
Application* Application::getInstance() {
    if (uniqueInstance == nullptr) {
        uniqueInstance = new Application();
    }
    return uniqueInstance;
}

Account* Application::getAccount(string username) {
    return accounts[username];
}

// Setters for Actor and Movie
void Application::addActor(Actor actor) {
    actors.add(actor.getId(), &actor);
}
void Application::addMovie(Movie movie) {
    movies.add(movie.getId(), &movie);
}
bool Application::removeActor(int id) {
    return actors.remove(id);
}
bool Application::removeMovie(int id) {
    return movies.remove(id);
}

// Relationships
bool Application::addActorToMovie(int actorId, int movieId) {
    // Add Actor to the Actor-to-Movie Relationship
    SortedList* actorMovieIds = actorsToMovies[actorId];
    if (actorMovieIds == nullptr) {
        actorMovieIds = new SortedList();
        actorsToMovies[actorId] = actorMovieIds;
    }
    actorMovieIds->insert(movieId);

    // Add Movie to Movie-to-Actor Relationship
    SortedList* movieActorIds = moviesToActors[movieId];
    if (movieActorIds == nullptr) {
        movieActorIds = new SortedList();
        moviesToActors[movieId] = movieActorIds;
    }
    movieActorIds->insert(actorId);

    return true;
}
bool Application::removeActorFromMovie(int actorId, int movieId) {
    SortedList* actorMovieIds = actorsToMovies[actorId];
    actorMovieIds->remove(movieId);

    SortedList* movieActorIds = moviesToActors[movieId];
    movieActorIds->remove(actorId);

    return true;
}
DoubleLinkedList<Actor*>* Application::getActors(int movieId) {
    SortedList* actorIds = moviesToActors[movieId];
    DoubleLinkedList<Actor*>* movieActors = new DoubleLinkedList<Actor*>();

    for (int i = 0; i < actorIds->getLength(); i++) {
        Actor* actor = actors[actorIds->get(i)];
        movieActors->add(actor);
    }

    return movieActors;
}
DoubleLinkedList<Movie*>* Application::getMovies(int actorId) {
    SortedList* movieIds = actorsToMovies[actorId];
    DoubleLinkedList<Movie*>* actorMovies = new DoubleLinkedList<Movie*>();

    for (int i = 0; i < movieIds->getLength(); i++) {
        actorMovies->add(movies[movieIds->get(i)]);
    }

    return actorMovies;
}
SortedList* Application::getActorMovies(int id) {
    return actorsToMovies[id];
}
SortedList* Application::getMovieActors(int id) {
    return moviesToActors[id];
}
// const MyDict<int, SortedList*>& Application::getActorsToMoviesRelationship() const {
//     return actorsToMovies;
// }
// const MyDict<int, SortedList *> &Application::getMoviesToActorsRelationship() const {
//     return moviesToActors;
// }
