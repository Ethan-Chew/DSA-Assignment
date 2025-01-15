//
// Created by ethan on 15/1/2025.
//

#pragma once
#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

class Actor {
private:
    int id;
    string name;
    int birthYear;
    DoubleLinkedList movies;
public:
    Actor(int, string, int);
    int getId();
    string getName();
    int getBirthYear();
    void setName(string);
    void setBirthYear(int);
};