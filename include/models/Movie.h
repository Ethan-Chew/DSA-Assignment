/*
* Created By: Ethan Chew (S10255990K), Darius Koh (S10255626K), Lim Yu Yang (S10255816J)
* Group: 4
*/

#pragma once
#include <iostream>

#include "Printable.h"
#include "Rateable.h"


class Movie: public Rateable, public Printable {
private:
    int id;
    std::string title;
    std::string plot;
    int releaseYear;
public:
    // Constructor and Destructor
    Movie(int, std::string, int, std::string);
    ~Movie();

    // Getters
    int getId();
    std::string getTitle() const;
    std::string getPlot();
    int getReleaseYear() const;

    // Setters
    void setTitle(std::string);
    void setPlot(std::string);
    void setReleaseYear(int);

    // Movie Functions
    void print() override;

    // Overload Comparison Operator
    bool operator<(const Movie& other) const;
};