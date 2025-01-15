//
// Created by ethan on 15/1/2025.
//

#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef int ItemType;

// DoubleLinkedList to store Actor and Movie IDs (int)
class DoubleLinkedList {
private:
    struct Node {
        ItemType item;
        Node* next;
        Node* prev;
    };
    Node* firstNode;
    Node* lastNode;
    int size;
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void add(ItemType item);
    bool remove(ItemType item);
    int find(ItemType item);
    bool isEmpty();
    int getLength();
    void print();
};