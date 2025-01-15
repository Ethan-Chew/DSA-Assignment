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
void Application::setActors(MyDict<int, Actor> actors) {
    this->actors = std::move(actors);
}
void Application::setMovies(MyDict<int, Movie> movies) {
    this->movies = std::move(movies);
}
MyDict<int, Actor> Application::getActors() {
    return std::move(actors);
}
MyDict<int, Movie> Application::getMovies() {
    return std::move(movies);
}
