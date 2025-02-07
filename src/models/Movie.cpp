//
// Created by ethan on 15/1/2025.
//

#include "models/Movie.h"

// Constructor and Destructor
Movie::Movie(int id, std::string title, int releaseYear, std::string plot) {
    this->id = id;
    this->title = title;
    this->releaseYear = releaseYear;
    this->plot = plot;
}

Movie::~Movie() {}

// Getters
int Movie::getId() {
    return this->id;
}

std::string Movie::getTitle() const {
    return this->title;
}

std::string Movie::getPlot() {
    return this->plot;
}

int Movie::getReleaseYear() const {
    return this->releaseYear;
}

// Setters
void Movie::setTitle(std::string title) {
    this->title = title;
}
void Movie::setPlot(std::string plot) {
    this->plot = plot;
}

void Movie::setReleaseYear(int releaseYear) {
    this->releaseYear = releaseYear;
}

// Movie Functions
void Movie::print() {
    std::cout << "Movie ID: " << id << " | Title: " << title << " | Release Year: " << releaseYear << " | Plot: " << plot << " | Rating: " << getRating() << "\n";
}

// Overload Operator for Comparison
bool Movie::operator<(const Movie& other) const {
    return title < other.title;
}