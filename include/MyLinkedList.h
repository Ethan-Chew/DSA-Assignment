#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <functional>
#include <iostream>
#include <optional>
#include "models/Actor.h"
#include "models/Movie.h"

enum FilterType {
    AGE_RANGE,
    PAST_THREE_YEARS
};

enum SortType {
    ALPHABETICALLY,
    AGE,
    RELEASE_YEAR
};

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
    Node* merge(Node*, Node*, SortType); // Merges 2 Doubly-Linked Lists into One
    Node* MergeSort(Node*, SortType); // Recursive Merge Sort

    // // Comparator Lambda Functions
    // // Compares the Name or Title for Actor and Movie respectively
    // std::function<bool(const T&, const T&)> compareTextAlphabetically = [](const T& a, const T& b) {
    //     return a < b;
    // };
    //
    // // Compares Actor classes by Age attribute
    // std::function<bool(Actor* const&, Actor* const&)> compareByAge = [](Actor* const& a, Actor* const& b) {
    //     return a->getBirthYear() < b->getBirthYear();
    // };
    //
    // // Compares Movie classes by ReleaseYear attribute
    // std::function<bool(Movie* const&, Movie* const&)> compareByReleaseYear = [](Movie* const& a, Movie* const& b) {
    //     return a->getReleaseYear() < b->getReleaseYear();
    // };

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
    void sort(SortType);
    void filter(MyLinkedList<T>&, FilterType, std::optional<int>, std::optional<int>);
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
typename MyLinkedList<T>::Node* MyLinkedList<T>::merge(Node* left, Node* right, SortType type) {
    Node* newHead = nullptr;
    Node* tempNode = nullptr;

    // Determine the Comparator to use for the Merge Sort (either Alphabetically, by Age, or by Release Year) using Lambda Functions
    // Casts void pointers to accept any pointer type, then casts the pointer to the appropriate type
    std::function<bool(const void*, const void*)> comparator;
    switch (type) {
        // Compares the Name or Title for Actor and Movie respectively
        case ALPHABETICALLY:
            comparator = [](const void* a, const void* b) {
                if (std::is_same_v<T, Actor*>) {
                    const auto* actorA = static_cast<const Actor*>(a);
                    const auto* actorB = static_cast<const Actor*>(b);
                    return actorA < actorB;
                }
                if (std::is_same_v<T, Movie*>) {
                    const auto* movieA = static_cast<const Movie*>(a);
                    const auto* movieB = static_cast<const Movie*>(b);
                    return movieA < movieB;
                }
                throw std::invalid_argument("Alphabetical comparison is not supported");
            };
        break;

        // Compares Actor classes by Age attribute
        case AGE:
            comparator = [](const void* a, const void* b) {
                const auto* actorA = static_cast<const Actor*>(a);
                const auto* actorB = static_cast<const Actor*>(b);
                return actorA->getBirthYear() < actorB->getBirthYear();
        };
        break;

        // Compares Movie classes by ReleaseYear attribute
        case RELEASE_YEAR:
            comparator = [](const void* a, const void* b) {
                const auto* movieA = static_cast<const Movie*>(a);
                const auto* movieB = static_cast<const Movie*>(b);
                return movieA->getReleaseYear() < movieB->getReleaseYear();
        };
        break;
    }

    // Merge the two sorted lists
    while (left && right) {
        if (comparator(left->item, right->item)) {
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
typename MyLinkedList<T>::Node *MyLinkedList<T>::MergeSort(Node* head, SortType type) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Perform Merge Sort on left and right sides of the array
    /// Split the LinkedList into two halves
    Node* secondHalf = split(head);
    /// Perform Merge Sort on Left Half
    head = MergeSort(head, type);
    /// Perform Merge Sort on Right Half
    secondHalf = MergeSort(secondHalf, type);

    // Merge the Left and Right Halves together
    return merge(head, secondHalf, type);
}

template<typename T>
void MyLinkedList<T>::sort(SortType type) {
    // Call the Merge Sort Function
    firstNode = MergeSort(firstNode, type);
}

template<typename T>
void MyLinkedList<T>::filter(MyLinkedList<T>& filteredList, FilterType filterType, std::optional<int> startAge, std::optional<int> endAge) {
    // // Type Check the Objects currently in the array (T)
    // if (filterType == FilterType::AGE_RANGE) {
    //     if (!std::is_same_v<T, Actor>) {
    //         throw std::invalid_argument("AGE_RANGE filter can only be applied to Actors");
    //     }
    //     if (!(startAge.has_value() && endAge.has_value())) {
    //         throw std::invalid_argument("startAge and endAge must be both non-zero when filtering by AGE_RANGE");
    //     }
    // }
    // if (filterType == FilterType::PAST_THREE_YEARS && !std::is_same_v<T, Movie>) {
    //     throw std::invalid_argument("PAST_THREE_YEARS filter can only be applied to Movies");
    // }
    //
    // // TODO: Can we use STL to get the current year?
    // const int currentYear = 2025;
    //
    // // Filter the List
    // Node* currNode = firstNode;
    // while (currNode != nullptr) {
    //     switch (filterType) {
    //         case FilterType::AGE_RANGE:
    //             Actor* actor = reinterpret_cast<Actor*>(currNode->item);
    //             const int actorCurrentAge = currentYear - actor->getBirthYear();
    //             if (actorCurrentAge >= startAge && actorCurrentAge <= endAge) {
    //                 filteredList.append(actor);
    //             }
    //         break;
    //         case FilterType::PAST_THREE_YEARS:
    //             Movie* movie = reinterpret_cast<Movie*>(currNode->item);
    //             if (movie->getReleaseYear() > 3) {
    //                 filteredList.append(movie);
    //             }
    //         break;
    //     }
    //     currNode = currNode->next;
    // }
}


#endif