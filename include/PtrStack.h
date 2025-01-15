#include <iostream>
#include <memory>
#include <functional>

template<typename T>
class PtrStack 
{
private:
    struct Node 
    {
        T item;
        std::unique_ptr<Node> next;
        Node(T val) : item(std::move(val)), next(nullptr) {};
    };

    std::unique_ptr<Node> top;

public:
    PtrStack();
    bool is_empty();
    bool push(T item);
    bool pop();
    bool pop(T &item);
    void get_top(T &item);
    void display(bool back = false);
};

template<typename T>
inline PtrStack<T>::PtrStack() : top(nullptr) {};

template<typename T>
bool PtrStack<T>::is_empty() 
{
    return top == nullptr;
}

template<typename T>
bool PtrStack<T>::push(T item) 
{
    std::unique_ptr<Node> new_node = std::make_unique<Node>(item);
    new_node->next = std::move(top);
    top = std::move(new_node);

    return true;
}

template<typename T>
bool PtrStack<T>::pop()
{
    if (is_empty()) 
    {
        return false;
    }

    top = std::move(top->next);
    return true;
}

template<typename T>
bool PtrStack<T>::pop(T &item)
{
    if (is_empty())
    {
        return false;
    }

    item = top->item;
    top = std::move(top->next);
    return true;
}

template<typename T>
void PtrStack<T>::get_top(T &item) 
{
    if (!is_empty()) 
    {
        item = top->item;    
    }
}

template<typename T>
void PtrStack<T>::display(bool back)
{
    if (is_empty()) 
    {
        std::cout
            << "Stack is empty\n";
        return;
    }
    
    if (!back)
    {
        for (Node *cur = top.get(); cur != nullptr; cur = cur->next.get())
        {
             std::cout 
                << cur->item << " ";
        }

        std::cout << "\n";
    } 
    else
    {
        std::function<void(const std::unique_ptr<Node>&)> rev_helper = 
            [&](const std::unique_ptr<Node> &node)     
            {
                if (!node) return;
                rev_helper(node->next);
                std::cout
                    << node->item << " ";
            };
        rev_helper(top);
        std::cout << "\n";
    }
}
