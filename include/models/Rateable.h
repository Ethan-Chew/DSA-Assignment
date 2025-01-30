//
// Created by ethan on 22/1/2025.
//

#pragma once

class Rateable {
public:
    int avgRating = 0;
    int numRated = 0;

    void addRating(int);
    int getRating() const;
};