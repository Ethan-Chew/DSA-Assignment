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
bool addActorToMovie(Application, int, int, MyDict<int, Actor*>, MyDict<int, Movie*>);
bool updateActorOrMovie(Application, bool, int, MyDict<int, Actor*>, MyDict<int, Movie*>);

#endif //BASICFEATURES_H