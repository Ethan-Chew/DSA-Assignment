//
// Created by ethan on 15/1/2025.
//

#pragma once
#include "DoubleLinkedList.h"
#include <iostream>


class Actor {
private:
    int id;
    std::string name;
    int birthYear;
public:
    Actor(int, std::string, int);
    ~Actor();
    int getId();
    std::string getName();
    int getBirthYear();
    void setName(std::string);
    void setBirthYear(int);
    void print();

    // Overload Comparison Operators
    bool operator<(const Actor& other) const;
};