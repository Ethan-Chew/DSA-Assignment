//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"

#include <MyLinkedList.h>

Application* Application::uniqueInstance = nullptr;
Application::Application() { }
Application* Application::getInstance() {
    if (uniqueInstance == nullptr) {
        uniqueInstance = new Application();
    }
    return uniqueInstance;
}

// Setters for Actor and Movie
void Application::addActor(Actor actor) {
    actors.add(actor.getId(), actor);
}
void Application::addMovie(Movie movie) {
    movies.add(movie.getId(), movie);
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
MyLinkedList<Actor*>* Application::getActors(int movieId) {
    SortedList* actorIds = moviesToActors[movieId];
    actorIds->print();
    MyLinkedList<Actor*>* movieActors = new MyLinkedList<Actor*>();

    for (int i = 0; i < actorIds->getLength(); i++) {
        movieActors->append(&actors[actorIds->find(i)]);
    }

    return movieActors;
}
MyLinkedList<Movie*>* Application::getMovies(int actorId) {
    SortedList* movieIds = actorsToMovies[actorId];
    MyLinkedList<Movie*>* actorMovies = new MyLinkedList<Movie*>();

    for (int i = 0; i < movieIds->getLength(); i++) {
        actorMovies->append(&movies[movieIds->find(i)]);
    }

    return actorMovies;
}