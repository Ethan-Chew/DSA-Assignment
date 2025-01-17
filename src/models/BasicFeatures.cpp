//
// Created by d on 17/1/2025.
//

#include "../include/BasicFeatures.h"
#include <iostream>
#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
using namespace std;

// Admin Basic Functions
// a. Add new actor
bool addNewActor(Application &application) {
    try {
        string name;
        int birthYear;

        cout <<
            "Option: 'Add New Actor' Selected.\n"
            "Please enter name: ";
        cin >> name;

        cout << "\nPlease enter birth year: ";
        cin >> birthYear;

        // TODO: Add Id parser

        Actor newActor = Actor(0, name, birthYear);
        application.addActor(newActor);

        return true;
    }
    catch(exception &e) {
        cout << "An error has occurred. Please try again." << endl;
        return false;
    }
}

// b. Add new movie
bool addNewMovie(Application &application) {
    try {
        string title;
        int releaseYear;
        string plot;

        cout <<
            "Option: 'Add New Movie' Selected.\n"
            "Please enter movie title: ";
        cin >> title;

        cout << "\nPlease enter movie release year: ";
        cin >> releaseYear;

        cout << "\nPlease enter movie plot: ";
        cin >> plot;

        // TODO: Add Id parser and Genre

        Movie newMovie = Movie(0, title, releaseYear, plot, Genre::NONE);
        application.addMovie(newMovie);

        return true;
    }
    catch (exception &e) {
        cout << "An error has occurred. Please try again." << endl;
        return false;
    }
}

// c. Add an actor to a movie
bool addActorToMovie(Application &application, int actorId, int movieId, MyDict<int, Actor*> actorList, MyDict<int, Movie*> movieList) {

    return false;
}

// d. Update actor/movie details
bool updateActorOrMovie(Application &application, bool isActor, int actorMovieId, MyDict<int, Actor*> actorList, MyDict<int, Movie*> movieList) {

    return false;
}

// User Basic Functions
// e. Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user


// f. Display movies made within the past 3 years (in ascending order of year)


// g. Display all movies an actor starred in (in alphabetical order)


// h. Display all the actors in a particular movie (in alphabetical order)


// i. Display a list of all actors that a particular actor knows.