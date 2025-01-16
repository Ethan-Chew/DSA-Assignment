//
// Created by ethan on 15/1/2025.
//

#pragma once

#include "MyDict.h"
#include "Actor.h"
#include "Movie.h"

#include <iostream>
#include <MyLinkedList.h>

#include "SortedList.h"
using namespace std;

// Singleton to store data of Actors and Movies
class Application {
private:
    static Application* uniqueInstance;
    MyDict<int, Actor> actors;
    MyDict<int, Movie> movies;

    MyDict<int, SortedList*> actorsToMovies;
    MyDict<int, SortedList*> moviesToActors;

    Application();
public:
    static Application* getInstance();

    // Add/Remove Actor Objects
    void addActor(Actor actor);
    bool removeActor(int);

    // Add/Remove Movie Objects
    void addMovie(Movie movie);
    bool removeMovie(int);

    // Relationships
    /// Add/Remove Actor ID into Movie ID
    bool addActorToMovie(int, int);
    bool removeActorFromMovie(int, int);
    /// Get Actors who acted in Movie ID
    MyLinkedList<Actor*>* getActors(int);
    /// Get Movies acted by Actor ID
    MyLinkedList<Movie*>* getMovies(int);
};