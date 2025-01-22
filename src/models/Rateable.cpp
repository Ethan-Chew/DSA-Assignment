//
// Created by ethan on 22/1/2025.
//

#include "models/Rateable.h"

void Rateable::addRating(int val) {
    avgRating = (avgRating * numRated) + val;
    numRated++;
}

int Rateable::getRating() const {
    return avgRating;
}