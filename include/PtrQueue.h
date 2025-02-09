/*
* Created By: Darius Koh (S10255626K)
* Group: 4
*/

#ifndef PTR_QUEUE_H
#define PTR_QUEUE_H

#include <iostream>
#include <memory>

// Queue implementation using a linked list with smart pointers for memory management
template<typename T>
class PtrQueue
{
private:
    // Node structure to represent each element in the queue
    struct Node
    {
        T item;                       // The item stored in the node
        std::unique_ptr<Node> next;    // Pointer to the next node, managed by unique_ptr
        Node(T val) : item(std::move(val)), next(nullptr) {}; // Constructor to initialize item and set next to nullptr
    };

    std::unique_ptr<Node> front; // The front of the queue (first element)
    Node* back;                  // The back of the queue (last element)

public:
    PtrQueue();                  // Constructor to initialize the queue
    bool enqueue(T item);        // Add an item to the queue
    bool dequeue();              // Remove the front item from the queue
    bool dequeue(T &item);       // Remove and return the front item
    void get_front(T &item);     // Retrieve the front item without removing it
    bool is_empty();             // Check if the queue is empty
    void display();              // Display the contents of the queue
};

// Constructor to initialize the queue with empty front and back
template<typename T>
inline PtrQueue<T>::PtrQueue() : front(nullptr), back(nullptr) {};

// Check if the queue is empty (front = nullptr)
template<typename T>
bool PtrQueue<T>::is_empty()
{
    return front == nullptr;
}

template<typename T>
bool PtrQueue<T>::enqueue(T item)
{
    // Create a new node to hold the item
    std::unique_ptr<Node> new_node = std::make_unique<Node>(item);

    // If the queue is empty, set the new node as both the front and the back
    if (is_empty())
    {
        back = new_node.get();
        front = std::move(new_node); // Use move to transfer ownership
        return true;
    }

    // If not empty, link the new node to the back of the queue and update the back pointer
    back->next = std::move(new_node); // Transfer ownership to the next pointer of the last node
    back = back->next.get();
    return true;
}

// Dequeue operation: Remove the front item from the queue (no item returned)
template<typename T>
bool PtrQueue<T>::dequeue()
{
    if (is_empty())
    {
        return false; // Can't dequeue from an empty queue
    }

    front = std::move(front->next);

    if (front == nullptr)
    {
        back = nullptr;
    }

    return true;
}

// Dequeue operation: Remove the front item and store it in the passed reference (item)
template<typename T>
bool PtrQueue<T>::dequeue(T &item)
{
    if (is_empty())
    {
        return false; // Can't dequeue from an empty queue
    }

    item = front->item;
    front = std::move(front->next);

    // If the queue becomes empty, set the back pointer to nullptr
    if (front == nullptr)
    {
        back = nullptr;
    }
    return true;
}

// Retrieve the front item without removing it from the queue
template<typename T>
void PtrQueue<T>::get_front(T &item)
{
    if (!is_empty())
    {
        item = front->item;
    }
}

// Display the queue items from front to back
template<typename T>
void PtrQueue<T>::display()
{
    if (is_empty())
    {
        std::cout << "Queue is empty\n";
        return;
    }

    // Traverse the queue from front to back, printing each item
    for (Node *cur = front.get(); cur != nullptr; cur = cur->next.get())
    {
        std::cout << cur->item << " "; // Print the current item
    }
    std::cout << "\n"; // End the output with a newline
}

#endif
