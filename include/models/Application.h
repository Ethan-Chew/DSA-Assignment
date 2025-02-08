//
// Created by ethan on 15/1/2025.
//

#pragma once

#include "MyDict.h"
#include "Actor.h"
#include "Movie.h"

#include <iostream>

#include "Account.h"
#include "SortedList.h"
#include "MyList.h"
#include "Report.h"
#include "AutoCompletionEngine.h"

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

    // List of Reports
    MyList<std::unique_ptr<Report>>* reports;

    // Dictionary of Actors/Movies
    MyDict<int, std::unique_ptr<Actor>> actors;
    MyDict<int, std::unique_ptr<Movie>> movies;

    // Dictionary containing Actor-Movie and Movie-Actor Relationships
    MyDict<int, std::unique_ptr<SortedList>> actorsToMovies;
    MyDict<int, std::unique_ptr<SortedList>> moviesToActors;

    // Dictionary that helps match Name to Pointer of Actor/Movie Object
    MyDict<std::string, int> actorNames;
    MyDict<std::string, int> movieNames;

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

    // Add/Retrieve/Update Report
    void addReport(Report* report);
    // void updateReport(Report report);
    MyList<std::unique_ptr<Report>> *retrieveAllReports();

    // Add/Remove/Retrieve Actor Objects
    void addActor(std::unique_ptr<Actor> actor);
    bool removeActor(int);
    Actor* getActor(int);
    int getActorIdByName(std::string);
    MyList<Actor*>* getAllActors();

    // Add/Remove/Retrieve Movie Objects
    void addMovie(std::unique_ptr<Movie> movie);
    bool removeMovie(int);
    Movie* getMovie(int);
    int getMovieIdByName(std::string);
    MyList<Movie*>* getAllMovies();

    // Relationships
    // Add/Remove Actor ID into Movie ID
    bool addActorToMovie(int, int);
    bool removeActorFromMovie(int, int);

    // Get Actors who acted in Movie ID
    SortedList *getActorMovies(int id);
    MyList<Actor*>* getActors(int);

    // Get Movies acted by Actor ID
    MyList<Movie*>* getMovies(int);
    SortedList *getMovieActors(int id);

    // Menu for search choice (name/id)
    Actor* searchForActor();
    Movie* searchForMovie();
};