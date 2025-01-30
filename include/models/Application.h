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

// Singleton to store data of Actors and Movies
class Application {
private:
    // Constructor
    Application();

    // Gets maximum value of Actor and Movie Ids to automatically assign an empty Id Key on creation
    int maxActorId;
    int maxMovieId;

    // Singleton Checker
    static Application* uniqueInstance;

    // Dictionary of Actors/Movies
    MyDict<int, std::unique_ptr<Actor>> actors;
    MyDict<int, std::unique_ptr<Movie>> movies;

    // Dictionary containing Actor-Movie and Movie-Actor Relationships
    MyDict<int, std::unique_ptr<SortedList>> actorsToMovies;
    MyDict<int, std::unique_ptr<SortedList>> moviesToActors;

    // Dictionary of all registered accounts
    MyDict<std::string, std::unique_ptr<Account>> accounts;
public:
    // Get instance of Application
    static Application* getInstance();

    // Retrieve Account
    Account* getAccount(const std::string &username);

    // Retrieve max ID values of Actor and Movie
    int getMaxActorId();
    int getMaxMovieId();

    // Add/Remove/Retrieve Actor Objects
    void addActor(std::unique_ptr<Actor> actor);
    bool removeActor(int);
    Actor* getActor(int);
    MyLinkedList<Actor*>* getAllActors();

    // Add/Remove/Retrieve Movie Objects
    void addMovie(std::unique_ptr<Movie> movie);
    bool removeMovie(int);
    Movie* getMovie(int);
    MyLinkedList<Movie*>* getAllMovies();

    // Relationships
    // Add/Remove Actor ID into Movie ID
    bool addActorToMovie(int, int);
    bool removeActorFromMovie(int, int);

    // Get Actors who acted in Movie ID
    SortedList *getActorMovies(int id);
    MyLinkedList<Actor*>* getActors(int);


    MyList<Actor*> getAllActorsList();
    MyList<Movie*> getAllMoviesList();
    // Get Movies acted by Actor ID
    MyLinkedList<Movie*>* getMovies(int);
    SortedList *getMovieActors(int id);

};