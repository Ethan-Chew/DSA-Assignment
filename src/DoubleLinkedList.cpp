//
// Created by ethan on 15/1/2025.
//

#include "DoubleLinkedList.h"

#include <models/Actor.h>
#include <models/Movie.h>

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() {
    firstNode = nullptr;
    lastNode = nullptr;
    size = 0;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    Node* tempNode = firstNode;
    while (tempNode != nullptr) {
        Node* temp = tempNode->next;
        delete tempNode;
        tempNode = temp;
    }
}

template <typename T>
void DoubleLinkedList<T>::add(T item) {
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

template <typename T>
bool DoubleLinkedList<T>::remove(T item) {
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

template <typename T>
int DoubleLinkedList<T>::find(T item) {
    Node* tempNode = firstNode;
    int index = 0;
    while (tempNode->item != item && tempNode != nullptr) {
        tempNode = tempNode->next;
        index++;
    }
    return index;
}

template <typename T>
bool DoubleLinkedList<T>::isEmpty() {
    return size == 0;
}

template <typename T>
int DoubleLinkedList<T>::getLength() {
    return size;
}

template <typename T>
void DoubleLinkedList<T>::print() {
    Node* tempNode = firstNode;
    while (tempNode != nullptr) {
        tempNode->item->print();
        tempNode = tempNode->next;
    }
    std::cout << "\n";
}

// Merge Sort Functionality
template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::split(Node* head) {
    // Find the Middle of the List by using the Slow and Fast Pointer
    /// Slow Pointer will reach the middle by the time the Fast Pointer meets the end
    Node* slow = head;
    Node* fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the Linked List into Two Halves
    Node* secondHalf = slow->next;
    slow->next = nullptr;
    if (secondHalf != nullptr) {
        secondHalf->prev = nullptr;
    }

    return secondHalf;
}

template<typename T>
typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::merge(Node* left, Node* right) {
    Node* newHead = nullptr;
    Node* tempNode = newHead;

    while (left && right) {
        if (left->item < right->item) {
            if (newHead == nullptr) {
                newHead = left;
                tempNode = newHead;
                left->prev = nullptr;
            } else {
                tempNode->next = left;
                left->prev = tempNode;
            }
            left = left->next;
        } else {
            if (newHead == nullptr) {
                newHead = right;
                tempNode = newHead;
                right->prev = nullptr;
            } else {
                tempNode->next = right;
                right->prev = tempNode;
            }
            right = right->prev;
        }
    }

    // Add the remaining elements
    while (left != nullptr) {
        tempNode->next = left;
        left->prev = tempNode;
        left = left->next;
    }
    while (right != nullptr) {
        tempNode->next = right;
        right->prev = tempNode;
        right = right->next;
    }

    return newHead;
}

template<typename T>
typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::MergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Perform Merge Sort on left and right sides of the array
    /// Split the LinkedList into two halves
    Node* secondHalf = this->split(head);
    /// Perform Merge Sort on Left Half
    head = MergeSort(head);
    /// Perform Merge Sort on Right Half
    secondHalf = MergeSort(secondHalf);

    // Merge the Left and Right Halves together
    return this->merge(head, secondHalf);
}

template<typename T>
void DoubleLinkedList<T>::sort() {
    MergeSort(firstNode);

    // Update the lastNode pointer
    lastNode = firstNode;
    if (lastNode != nullptr) {
        while (lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }
    }
}

template class DoubleLinkedList<Actor*>;
template class DoubleLinkedList<Movie*>;