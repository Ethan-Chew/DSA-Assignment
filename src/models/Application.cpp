//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"

Application* Application::uniqueInstance = nullptr;
Application::Application() { }
Application* Application::getInstance() {
    if (uniqueInstance == nullptr) {
        uniqueInstance = new Application();
    }
    return uniqueInstance;
}
MyDict<int, Actor> Application::getActors() {
    return std::move(actors);
}
MyDict<int, Movie> Application::getMovies() {
    return std::move(movies);
}
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