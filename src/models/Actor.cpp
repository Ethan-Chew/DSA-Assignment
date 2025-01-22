//
// Created by ethan on 15/1/2025.
//

#include "models/Actor.h"

// Constructor and Destructor
Actor::Actor(int id, std::string name, int birthYear) {
    this->id = id;
    this->name = name;
    this->birthYear = birthYear;
}

Actor::~Actor() {}

// Getters
int Actor::getId() {
    return id;
}

std::string Actor::getName() const {
    return name;
}

int Actor::getBirthYear() const {
    return birthYear;
}

// Setters
void Actor::setName(std::string name) {
    this->name = name;
}

void Actor::setBirthYear(int birthYear) {
    this->birthYear = birthYear;
}

// Actor Functions
void Actor::print() {
    std::cout << "Actor ID: " << id << " | Name: " << name << " | Birth Year: " << birthYear <<  " | Rating: " << getRating() << "\n";
}

// Overload Operator for Comparison
bool Actor::operator<(const Actor& other) const {
    return name < other.name;
}