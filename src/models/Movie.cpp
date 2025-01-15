//
// Created by ethan on 15/1/2025.
//

#include "models/Movie.h"

Movie::Movie(int id, string title, int releaseYear, string plot, Genre genre) {
    this->id = id;
    this->title = title;
    this->releaseYear = releaseYear;
    this->plot = plot;
    this->genre = genre;
}