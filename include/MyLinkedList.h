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
        std::unique_ptr<Node> next;
        Node(T val) : item(val), next(nullptr) {}
    };
    std::unique_ptr<Node> firstNode;
    int size;

public:
    MyLinkedList();
    bool append(T item);
    bool insert(int idx, T item);
    void remove(int idx);
    T get(int idx);
    bool is_empty();
    int get_length();
    void print();
};

template<typename T>
inline MyLinkedList<T>::MyLinkedList() : size(0) {};

template<typename T>
bool MyLinkedList<T>::append(T item)
{
    auto node = std::make_unique<Node>(item);
    if (is_empty()) {
        firstNode = std::move(node);
    } else {
        Node *cur = firstNode.get();
        while (cur->next) {
            cur = cur->next.get();
        }
        cur->next = std::move(node);
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
    
    auto node = std::make_unique<Node>(item);
    
    if (idx == 0) {
        node->next = std::move(firstNode);
        firstNode = std::move(node);
    } else {
        Node *cur = firstNode.get();
        for (int i = 0; i < idx - 1; i++) {
            cur = cur->next.get();
        }
        node->next = std::move(cur->next);
        cur->next = std::move(node);
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
        firstNode = std::move(firstNode->next);
    } else {
        Node *cur = firstNode.get();
        for (int i = 0; i < idx - 1; i++) {
            cur = cur->next.get();
        }
        cur->next = std::move(cur->next->next);
    }
    
    size--;
}

template<typename T>
T MyLinkedList<T>::get(int idx)
{
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node *cur = firstNode.get();
    for (int i = 0; i < idx; i++) {
        cur = cur->next.get();
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
    Node *cur = firstNode.get();
    while (cur) {
        std::cout << cur->item << " ";
        cur = cur->next.get();
    }
    std::cout << "\n";
}

#endif