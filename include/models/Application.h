//
// Created by ethan on 15/1/2025.
//

#pragma once

#include "MyDict.h"
#include "Actor.h"
#include "Movie.h"

#include <iostream>
using namespace std;

// Singleton to store data of Actors and Movies

class Application {
private:
    static Application* uniqueInstance;
    MyDict<int, Actor> actors;
    MyDict<int, Movie> movies;

    Application();
public:
    static Application* getInstance();
    void setActors(MyDict<int, Actor> actors);
    void setMovies(MyDict<int, Movie> movies);
    MyDict<int, Actor> getActors();
    MyDict<int, Movie> getMovies();
};