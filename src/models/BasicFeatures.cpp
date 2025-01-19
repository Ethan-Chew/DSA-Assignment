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
        std::string name;
        int birthYear;

        std::cout <<
            "Option: 'Add New Actor' Selected.\n"
            "Please enter name: ";
        getline(std::cin, name);

        std::cout << "\nPlease enter birth year: ";
        std::cin >> birthYear;

        // TODO: Add Id parser

        Actor newActor = Actor(0, name, birthYear);
        application.addActor(newActor);

        return true;
    }
    catch(exception &e) {
        std::cout << "An error has occurred. Please try again." << "\n";
        return false;
    }
}

// Add new movie
bool BasicFeatures::addNewMovie(Application &application) {
    try {
        std::string title;
        int releaseYear;
        std::string plot;

        std::cout <<
            "Option: 'Add New Movie' Selected.\n"
            "Please enter movie title: ";
        getline(std::cin, title);

        std::cout << "\nPlease enter movie release year: ";
        std::cin >> releaseYear;

        std::cout << "\nPlease enter movie plot: ";
        getline(std::cin, plot);

        // TODO: Add Id parser and Genre

        Movie newMovie = Movie(0, title, releaseYear, plot, Genre::NONE);
        application.addMovie(newMovie);

        return true;
    }
    catch (exception &e) {
        std::cout << "An error has occurred. Please try again." << "\n";
        return false;
    }
}

// Add an actor to a movie
bool BasicFeatures::addActorToMovie(Application &application) {
    int actorId;
    int movieId;

    std::cout <<
            "Option: 'Add Actor to Movie' Selected.\n"
            "Please enter actor's id: ";
    std::cin >> actorId;

    std::cout << "\nPlease enter movie id: ";
    std::cin >> movieId;

    if (application.addActorToMovie(actorId, movieId)) {
        std::cout << "Actor added successfully!" << "\n";
        return true;
    }
    return false;
}

// Update actor/movie details
bool BasicFeatures::updateActorOrMovie(Application &application) {
    int movieActorChoice;
    int actorMovieId;

    std::cout <<
            "Option: 'Update actor/movie details' Selected.\n"
            "Update (1) Actor or (2) Movie: ";
    std::cin >> movieActorChoice;

    // TODO: Add get actor/movie with Id functionality in application
    if (movieActorChoice == 1) {
        std::cout << "\nPlease enter actor id: ";
        std::cin >> actorMovieId;

        application.getActor(actorMovieId);
    }
    else if (movieActorChoice == 2) {
        std::cout << "\nPlease enter actor id: ";
        std::cin >> actorMovieId;

        application.getMovie(actorMovieId);
    }
    else {
        std::cout << "Invalid Input. Please try again." << "\n";
        return false;
    }
}

// User Basic Functions
// Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user
bool displayActors(Application &application) {
    std::string ageRange;

    std::cout <<
        "Option: 'Display Actors' Selected.\n"
        "Enter actor age range, seperated by a comma: ";
    std::cin >> ageRange;

    return true;
}

// Display movies made within the past 3 years (in ascending order of year)
bool displayMovies(Application &application) {

    return true;
}

// Display all movies an actor starred in (in alphabetical order)
bool displayActorMovies(Application &application) {
    int actorId;

    std::cout <<
            "Option: 'Display all movies an actor starred in.\n"
            "Enter actor's id: ";
    std::cin >> actorId;

    DoubleLinkedList<Movie*>* movies = application.getMovies(actorId);
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

    std::cout <<
            "Option: 'Display all the actors in a particular movie.\n"
            "Enter movie id: ";
    std::cin >> movieId;

    // TODO: Sort alphabetically
}

// Display a list of all actors that a particular actor knows.
// MyLinkedList<Actor*> BasicFeatures::displayKnownActors(Application &application, int id) {
//     SortedList* actorMovies = application.getActorMovies(id);
//
// }