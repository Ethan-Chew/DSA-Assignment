//
// Created by ethan on 15/1/2025.
//

#pragma once

#include "MyDict.h"
#include "Actor.h"
#include "Movie.h"

#include <iostream>
#include <MyLinkedList.h>

#include "Account.h"
#include "SortedList.h"
using namespace std;

// Singleton to store data of Actors and Movies
class Application {
private:
    static Application* uniqueInstance;
    MyDict<int, Actor*> actors;
    MyDict<int, Movie*> movies;

    MyDict<int, SortedList*> actorsToMovies;
    MyDict<int, SortedList*> moviesToActors;

    MyDict<string, Account*> accounts;

    Application();
public:
    static Application* getInstance();

    // Retrieve Account
    Account* getAccount(string username);

    // Add/Remove/Retrieve Actor Objects
    void addActor(Actor actor);
    bool removeActor(int);
    Actor* getActor(int);

    // Add/Remove/Retrieve Movie Objects
    void addMovie(Movie movie);
    bool removeMovie(int);
    Movie* getMovie(int);

    // Relationships
    /// Add/Remove Actor ID into Movie ID
    bool addActorToMovie(int, int);
    bool removeActorFromMovie(int, int);
    /// Get Actors who acted in Movie ID
    // const MyDict<int, SortedList *> &getActorsToMoviesRelationship() const;
    SortedList *getActorMovies(int id);
    DoubleLinkedList<Actor*>* getActors(int);
    /// Get Movies acted by Actor ID
    // const MyDict<int, SortedList *> &getMoviesToActorsRelationship() const;
    DoubleLinkedList<Movie*>* getMovies(int);
    SortedList *getMovieActors(int id);
};