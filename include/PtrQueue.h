#ifndef PTR_QUEUE_H
#define PTR_QUEUE_H

#include <iostream>
#include <memory>

template<typename T>
class PtrQueue 
{
private:
    struct Node 
    {
        T item;
        std::unique_ptr<Node> next;
        Node(T val) : item(std::move(val)), next(nullptr) {};
    };

    std::unique_ptr<Node> front;
    Node* back;

public:
    PtrQueue();
    bool enqueue(T item);
    bool dequeue();
    bool dequeue(T &item);
    void get_front(T &item);
    bool is_empty();
    void display();
};

template<typename T>
inline PtrQueue<T>::PtrQueue() : front(nullptr), back(nullptr) {};

template<typename T>
bool PtrQueue<T>::is_empty() 
{
    return front == nullptr;
}

template<typename T>
bool PtrQueue<T>::enqueue(T item) 
{
    std::unique_ptr<Node> new_node = std::make_unique<Node>(item);
    
    if (is_empty()) 
    {
        back = new_node.get();
        front = std::move(new_node);
        return true;
    }
    
    back->next = std::move(new_node);
    back = back->next.get();
    return true;
}

template<typename T>
bool PtrQueue<T>::dequeue()
{
    if (is_empty()) 
    {
        return false;
    }
    
    front = std::move(front->next);
    
    if (front == nullptr) 
    {
        back = nullptr;
    }
    
    return true;
}

template<typename T>
bool PtrQueue<T>::dequeue(T &item)
{
    if (is_empty())
    {
        return false;
    }
    
    item = front->item;
    front = std::move(front->next);
    
    if (front == nullptr) 
    {
        back = nullptr;
    }
    
    return true;
}

template<typename T>
void PtrQueue<T>::get_front(T &item) 
{
    if (!is_empty()) 
    {
        item = front->item;    
    }
}

template<typename T>
void PtrQueue<T>::display()
{
    if (is_empty()) 
    {
        std::cout << "Queue is empty\n";
        return;
    }
    
    for (Node *cur = front.get(); cur != nullptr; cur = cur->next.get())
    {
        std::cout << cur->item << " ";
    }
    std::cout << "\n";
}

#endif