#pragma once
#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include <MyLinkedList.h>
#include <iostream>
using namespace std;

class BasicFeatures {
public:
    // Admin Features
    static bool addNewActor(Application&);
    static bool addNewMovie(Application&);
    static bool addActorToMovie(Application&);
    static bool updateActorOrMovie(Application&);

    // User Features
    static void displayActorsInMovie(Application& application, int id);
    static MyLinkedList<Actor*> displayKnownActors(Application& application, int id);
};