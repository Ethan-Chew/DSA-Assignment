//
// Created by ethan on 15/1/2025.
//

#include "models/Actor.h"

Actor::Actor(int id, string name, int birthYear) {
    this->id = id;
    this->name = name;
    this->birthYear = birthYear;
}
int Actor::getId() {
    return id;
}
string Actor::getName() {
    return name;
}
void Actor::setName(string name) {
    this->name = name;
}
void Actor::setBirthYear(int birthYear) {
    this->birthYear = birthYear;
}