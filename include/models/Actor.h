//
// Created by ethan on 15/1/2025.
//

#pragma once
#include <iostream>

#include "Printable.h"
#include "Rateable.h"


class Actor: public Rateable, public Printable {
private:
    int id;
    std::string name;
    int birthYear;
public:
    // Constructor and Destructor
    Actor(int, std::string, int);
    ~Actor();

    // Getters
    int getId();
    std::string getName() const;
    int getBirthYear() const;

    // Setters
    void setName(std::string);
    void setBirthYear(int);

    // Actor Functions
    void print() override;

    // Overload Comparison Operators
    bool operator<(const Actor& other) const;
};
