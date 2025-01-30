#pragma once
#include "models/Application.h"

class BasicFeatures {
public:
    // Admin Features
    static void addNewActor(Application&);
    static void addNewMovie(Application&);
    static void addActorToMovie(Application&);
    static void updateActorOrMovie(Application&);
    static void printAll(Application&);

    // User Features
    static void displayActors(Application&);
    static void displayMovies(Application&);
    static void displayActorMovies(Application&);
    static void displayActorsInMovie(Application& application);
    static void displayKnownActors(Application& application);
};