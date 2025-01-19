#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <iostream>
#include <memory>

template<typename T>
class MyLinkedList 
{
private:
    struct Node
    {
        T item;
        Node* next;
        Node(T val) : item(val), next(nullptr) {}
    };
    Node* firstNode;
    int size;

    // Merge Sort Helper Functions
    Node* split(Node*); // Splits the List into 2 Halves
    Node* merge(Node*, Node*); // Merges 2 Doubly-Linked Lists into One
    Node* MergeSort(Node*); // Recursive Merge Sort
public:
    MyLinkedList();
    ~MyLinkedList();
    bool append(T item);
    bool insert(int idx, T item);
    void remove(int idx);
    T get(int idx);
    bool is_empty();
    int get_length();
    void print();
    void sort();
};

template<typename T>
inline MyLinkedList<T>::MyLinkedList() : firstNode(nullptr), size(0) {};

template<typename T>
MyLinkedList<T>::~MyLinkedList() {
    while (firstNode != nullptr) {
        Node* tempNode = firstNode;
        firstNode = firstNode->next;
        delete tempNode;
    }
}


template<typename T>
bool MyLinkedList<T>::append(T item)
{
    Node* newNode = new Node(item);
    if (is_empty()) {
        firstNode = newNode;
    } else {
        Node* tempNode = firstNode;
        while (tempNode->next != nullptr) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
    size++;

    return true;
}

template<typename T>
bool MyLinkedList<T>::insert(int idx, T item)
{
    if (idx < 0 || idx > size) {
        return false;
    }

    Node* newNode = new Node(item);

    if (idx == 0) {
        newNode->next = firstNode;
        firstNode = newNode;
    } else {
        Node* tempNode = firstNode;
        for (int i = 0; i < idx - 1; i++) {
            tempNode = tempNode->next;
        }
        newNode->next = std::move(tempNode->next);
        tempNode->next = std::move(newNode);
    }

    size++;
    return true;
}

template<typename T>
void MyLinkedList<T>::remove(int idx)
{
    if (idx < 0 || idx >= size) {
        return;
    }

    if (idx == 0) {
        firstNode = firstNode->next;
    } else {
        Node *cur = firstNode;
        for (int i = 0; i < idx - 1; i++) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
    }

    size--;
}

template<typename T>
T MyLinkedList<T>::get(int idx)
{
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node *cur = firstNode;
    for (int i = 0; i < idx; i++) {
        cur = cur->next;
    }
    return cur->item;
}

template<typename T>
bool MyLinkedList<T>::is_empty()
{
    return size == 0;
}

template<typename T>
int MyLinkedList<T>::get_length()
{
    return size;
}

template<typename T>
void MyLinkedList<T>::print()
{
    Node *cur = firstNode;
    while (cur) {
        cur->item->print();
        cur = cur->next;
    }
    std::cout << "\n";
}

// Merge Sort Functionality
template<typename T>
typename MyLinkedList<T>::Node* MyLinkedList<T>::split(Node* head) {
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

    return secondHalf;
}

template<typename T>
typename MyLinkedList<T>::Node* MyLinkedList<T>::merge(Node* left, Node* right) {
    Node* newHead = nullptr;
    Node* tempNode = nullptr;  // tempNode is now a separate pointer

    // Merge the two sorted lists
    while (left && right) {
        if (left->item < right->item) {
            if (newHead == nullptr) {
                newHead = left;
                tempNode = newHead;
            } else {
                tempNode->next = left;
                tempNode = tempNode->next;
            }
            left = left->next;
        } else {
            if (newHead == nullptr) {
                newHead = right;
                tempNode = newHead;
            } else {
                tempNode->next = right;
                tempNode = tempNode->next;
            }
            right = right->next;
        }
    }

    // Add the remaining elements from left or right (if any)
    if (left) {
        tempNode->next = left;
    }
    if (right) {
        tempNode->next = right;
    }

    return newHead;
}

template<typename T>
typename MyLinkedList<T>::Node *MyLinkedList<T>::MergeSort(Node* head) {
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
void MyLinkedList<T>::sort() {
    firstNode = MergeSort(firstNode);
}

#endif