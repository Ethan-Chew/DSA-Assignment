//
// Created by ethan on 15/1/2025.
//

#pragma once
#include <iostream>

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
    std::string title;
    std::string plot;
    Genre genre;
    int releaseYear;
public:
    Movie(int, std::string, int, std::string, Genre);
    ~Movie();
    int getId();
    std::string getTitle();
    std::string getPlot();
    int getReleaseYear() const;
    Genre getGenre();
    void setTitle(std::string);
    void setPlot(std::string);
    void setGenre(Genre);
    void print();

    // Overload Comparison Operator
    bool operator<(const Movie& other) const;
};