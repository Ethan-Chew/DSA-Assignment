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
int Movie::getId() {
  return this->id;
}
string Movie::getTitle() {
    return this->title;
}
string Movie::getPlot() {
    return this->plot;
}
Genre Movie::getGenre() {
    return this->genre;
}
void Movie::setTitle(string title) {
    this->title = title;
}
void Movie::setPlot(string plot) {
    this->plot = plot;
}
void Movie::setGenre(Genre genre) {
    this->genre = genre;
}
void Movie::print() {
    cout << "Movie ID: " << id << " | Title: " << title << " | Plot: " << plot << " | Genre: " << genre << endl;
}


// Overload Operator for Comparison
bool Movie::operator<(const Movie& other) const {
    return title < other.title;
}