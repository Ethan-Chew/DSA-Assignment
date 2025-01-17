//
// Created by ethan on 16/1/2025.
//

#include <iostream>
using namespace std;

class SortedList {
private:
    int* data;
    int size;
    int capacity;

    void resize() {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        auto new_data = new int[new_capacity];

        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
public:
    SortedList();
    void insert(int item);
    void remove(int item);
    int find(int item);
    int get(int index);
    void print();
    bool isEmpty();
    int getLength();
    int getCapacity();
};