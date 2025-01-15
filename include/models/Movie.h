//
// Created by ethan on 15/1/2025.
//

#include <iostream>
using namespace std;

enum Genre {
    ACTION,
    SCIFI,
    HORROR,
    THRILLER,
    ROMANCE,
    FANTASY
};

class Movie {
private:
    int id;
    string title;
    string plot;
    Genre genre;
    int releaseYear;
public:
    Movie(int, string, int, string, Genre);
};