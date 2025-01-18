//
// Created by d on 17/1/2025.
//

#include "../include/BasicFeatures.h"
#include <iostream>
#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "DoubleLinkedList.h"
using namespace std;

// Admin Basic Functions
// Add new actor
bool BasicFeatures::addNewActor(Application &application) {
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

// Add new movie
bool BasicFeatures::addNewMovie(Application &application) {
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



// Add an actor to a movie
bool BasicFeatures::addActorToMovie(Application &application, int actorId, int movieId, MyDict<int, Actor*> actorList, MyDict<int, Movie*> movieList) {
    int actorId;
    int movieId;

    cout <<
            "Option: 'Add Actor to Movie' Selected.\n"
            "Please enter actor's id: ";
    cin >> actorId;

    cout << "\nPlease enter movie id: ";
    cin >> movieId;

    if (application.addActorToMovie(actorId, movieId)) {
        return true;
    }
    return false;
}

// Update actor/movie details
bool BasicFeatures::updateActorOrMovie(Application &application, bool isActor, int actorMovieId, MyDict<int, Actor*> actorList, MyDict<int, Movie*> movieList) {
    int movieActorChoice;
    int actorMovieId;

    cout <<
            "Option: 'Update actor/movie details' Selected.\n"
            "Update (1) Actor or (2) Movie: ";
    cin >> movieActorChoice;

    // TODO: Add get actor with Id functionality in application
    if (movieActorChoice == 1) {
        cout << "\nPlease enter actor id: ";
        cin >> actorMovieId;
    }
    else if (movieActorChoice == 2) {
        cout << "\nPlease enter actor id: ";
        cin >> actorMovieId;
    }
    else {
        cout << "Invalid Input. Please try again." << endl;
        return false;
    }
}

// User Basic Functions
// Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user
bool displayActors(Application &application) {


    return true;
}

// Display movies made within the past 3 years (in ascending order of year)
bool displayMovies(Application &application) {

    return true;
}

// Display all movies an actor starred in (in alphabetical order)
bool displayActorMovies(Application &application) {
    int actorId;

    cout <<
            "Option: 'Display all movies an actor starred in.\n"
            "Enter actor's id: ";
    cin >> actorId;

    MyLinkedList<Movie*>* movies = application.getMovies(actorId);
    if (movies == nullptr) { return  false; }

    // TODO: Sort alphabetically

    return true;
}

// Display all the actors in a particular movie (in alphabetical order)
void BasicFeatures::displayActorsInMovie(Application& application, int id) {
    int movieId;
    DoubleLinkedList<Actor*>* actors = application.getActors(id);
    actors->sort();
    actors->print();

    cout <<
            "Option: 'Display all the actors in a particular movie.\n"
            "Enter movie id: ";
    cin >> movieId;

    MyLinkedList<Actor*>* actors = application.getActors(movieId);
    if (actors == nullptr) { return false; }

    // TODO: Sort alphabetically
}

// i. Display a list of all actors that a particular actor knows.
// MyLinkedList<Actor*> BasicFeatures::displayKnownActors(Application &application, int id) {
//     SortedList* actorMovies = application.getActorMovies(id);
//
// }