//
// Created by ethan on 15/1/2025.
//

#pragma once
#include<string>
#include<iostream>
using namespace std;

template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T item;
        Node* next;
        Node* prev;
    };
    Node* firstNode;
    Node* lastNode;
    int size;

    // Merge Sort Helper Functions
    Node* split(Node*); // Splits the List into 2 Halves
    Node* merge(Node*, Node*); // Merges 2 Doubly-Linked Lists into One
    Node* MergeSort(Node*); // Recursive Merge Sort
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void add(T item);
    bool remove(T item);
    int find(T item);
    bool isEmpty();
    int getLength();
    void print();
    void sort();
};