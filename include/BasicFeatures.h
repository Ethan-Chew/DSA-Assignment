#pragma once
#ifndef BASICFEATURES_H
#define BASICFEATURES_H
#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include <MyLinkedList.h>
#include <iostream>
using namespace std;

// Admin Features
bool addNewActor(Application);
bool addNewMovie(Application);
bool addActorToMovie(Application);
bool updateActorOrMovie(Application);

// User Features
bool displayActors(Application);
bool displayMovies(Application);
bool displayActorMovies(Application);
bool displayMovieActors(Application);

#endif //BASICFEATURES_H