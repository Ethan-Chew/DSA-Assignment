//
// Created by ethan on 16/1/2025.
//

#pragma once
#include <iostream>
#include "Movie.h"
using namespace std;

class Stack {
private:
    struct Node {
        Movie item;
        Node* next;

        Node(Movie& m, Node* n = nullptr) : item(m), next(n) {}
    };

    Node* topNode;
public:
    Stack();
    ~Stack();
    bool isEmpty();
    void push(Movie item);
    void pop(Movie &item);
    void getTop(Movie &item);
};