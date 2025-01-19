//
// Created by ethan on 16/1/2025.
//

#include "models/Stack.h"
#include "models/Movie.h"

#include <iostream>


Stack::Stack() {
    topNode = nullptr;
}
Stack::~Stack() {
    while (topNode != nullptr) {
        Node* tempNode = topNode;
        topNode = topNode->next;
        delete tempNode;;
    }
}
bool Stack::isEmpty() {
    return topNode == nullptr;
}
void Stack::push(Movie newMovie) {
    Node* newNode = new Node(newMovie,  topNode->next);
    topNode = newNode;
}
void Stack::pop(Movie &movie) {
    if (topNode != nullptr) {
        Node* tempNode = topNode;
        topNode = topNode->next;
        movie = tempNode->item;
        delete tempNode;
    }
}
void Stack::getTop(Movie &item) {
    item = topNode->item;
}
