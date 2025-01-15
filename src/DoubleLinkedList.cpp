//
// Created by ethan on 15/1/2025.
//

#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList() {
    firstNode = nullptr;
    lastNode = nullptr;
    size = 0;
}
DoubleLinkedList::~DoubleLinkedList() {
    Node* tempNode = firstNode;
    while (tempNode != nullptr) {
        Node* temp = tempNode->next;
        delete tempNode;
        tempNode = temp;
    }
}
void DoubleLinkedList::add(ItemType item) {
    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (firstNode == nullptr) {
        firstNode = newNode;
        lastNode = newNode;
    } else {
        lastNode->next = newNode;
        newNode->prev = lastNode;
        lastNode = newNode;
    }
    size++;
}
bool DoubleLinkedList::remove(ItemType item) {
    if (isEmpty()) {
        return false;
    }

    if (firstNode->item == item) {
        Node* tempNode = firstNode;
        firstNode = firstNode->next;
        firstNode->prev = nullptr;
        delete tempNode;
        size--;
        return true;
    }
    if (lastNode->item == item) {
        Node* tempNode = lastNode;
        lastNode = lastNode->prev;
        lastNode->next = nullptr;
        delete tempNode;
        size --;
        return true;
    }

    Node* tempNode = firstNode;
    while (tempNode->item != item) {
        tempNode = tempNode->next;
    }

    if (tempNode == nullptr) {
        return false;
    }

    tempNode->prev->next = tempNode->next;
    tempNode->next->prev = tempNode->prev;
    delete tempNode;
    size--;
    return true;
}
int DoubleLinkedList::find(ItemType item) {
    Node* tempNode = firstNode;
    int index = 0;
    while (tempNode->item != item && tempNode != nullptr) {
        tempNode = tempNode->next;
        index++;
    }
    return index;
}
bool DoubleLinkedList::isEmpty() {
    return size == 0;
}

int DoubleLinkedList::getLength() {
    return size;
}
void DoubleLinkedList::print() {
    Node* tempNode = firstNode;
    while (tempNode != nullptr) {
        cout << tempNode->item << " ";
        tempNode = tempNode->next;
    }
    cout << endl;
}
