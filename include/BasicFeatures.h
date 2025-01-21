#pragma once
#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include <MyLinkedList.h>
#include <iostream>


class BasicFeatures {
public:
    // Admin Features
    static bool addNewActor(Application&);
    static bool addNewMovie(Application&);
    static bool addActorToMovie(Application&);
    static bool updateActorOrMovie(Application&);

    // User Features
    static bool displayActors(Application&);
    static bool displayMovies(Application&);
    static void displayActorsInMovie(Application& application);
    static void displayKnownActors(Application& application);
};