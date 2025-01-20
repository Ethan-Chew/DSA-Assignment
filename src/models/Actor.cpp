//
// Created by ethan on 15/1/2025.
//

#include "models/Actor.h"

Actor::Actor(int id, std::string name, int birthYear) {
    this->id = id;
    this->name = name;
    this->birthYear = birthYear;
}

Actor::~Actor() {}

int Actor::getId() {
    return id;
}
std::string Actor::getName() {
    return name;
}
int Actor::getBirthYear() const {
    return birthYear;
}
void Actor::setName(std::string name) {
    this->name = name;
}
void Actor::setBirthYear(int birthYear) {
    this->birthYear = birthYear;
}
void Actor::print() {
    std::cout << "Actor ID: " << id << " | Name: " << name << " | Birth Year: " << birthYear << "\n";
}

// Overload Operator for Comparison
bool Actor::operator<(const Actor& other) const {
    return name[0] < other.name[0];
}