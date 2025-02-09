/*
* Created By: Ethan Chew (S10255990K), Darius Koh (S10255626K), Lim Yu Yang (S10255816J)
* Group: 4
*/

#pragma once

class Rateable {
public:
    int avgRating = 0;
    int numRated = 0;

    void addRating(int);
    int getRating() const;
};