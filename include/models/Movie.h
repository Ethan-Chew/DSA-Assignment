//
// Created by ethan on 15/1/2025.
//

#pragma once
#include <iostream>

#include "Printable.h"
#include "Rateable.h"

enum Genre {
    ACTION,
    SCIFI,
    HORROR,
    THRILLER,
    ROMANCE,
    FANTASY,
    NONE,
};

class Movie: public Rateable, public Printable {
private:
    int id;
    std::string title;
    std::string plot;
    Genre genre;
    int releaseYear;
public:
    // Constructor and Destructor
    Movie(int, std::string, int, std::string, Genre);
    ~Movie();

    // Getters
    int getId();
    std::string getTitle() const;
    std::string getPlot();
    int getReleaseYear() const;
    Genre getGenre();

    // Setters
    void setTitle(std::string);
    void setPlot(std::string);
    void setGenre(Genre);
    void setReleaseYear(int);

    // Movie Functions
    void print() override;

    // Overload Comparison Operator
    bool operator<(const Movie& other) const;
};