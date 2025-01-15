//
// Created by ethan on 15/1/2025.
//

#pragma once
#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

enum Genre {
    ACTION,
    SCIFI,
    HORROR,
    THRILLER,
    ROMANCE,
    FANTASY,
    NONE,
};

class Movie {
private:
    int id;
    string title;
    string plot;
    Genre genre;
    int releaseYear;
    DoubleLinkedList actors;
public:
    Movie(int, string, int, string, Genre);
};