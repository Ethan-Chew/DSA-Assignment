//
// Created by ethan on 16/1/2025.
//

#include "../../include/SortedList.h"
#include <iostream>
using namespace std;

SortedList::SortedList() {
    size = 0;
    capacity = 1;
    data = new int[capacity];
}
void SortedList::insert(int item) {
    if (size >= capacity) {
        resize();
    }

    // Use Binary Search to find where the item should be inserted
    /// start will be the position to insert the element
    int start = 0, end = size - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (data[mid] > item) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    // Shift elements to the right to make space for the new item
    for (int i = size; i > start; i--) {
        data[i] = data[i - 1];
    }

    // Insert Item
    data[start] = item;
    size++;
}
void SortedList::remove(int item) {
    int indexToRemove = this->find(item);
    if (indexToRemove == -1) {
        return; // Item does not exist
    }

    // Shift the elements
    for (int i = indexToRemove; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}
int SortedList::find(int item) {
    int start = 0, end = size - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (data[mid] == item) {
            return mid;
        } else if (data[mid] > item) {
            end = mid - 1;
        } else if (data[mid] < item) {
            start = mid + 1;
        }
    }
    return -1;
}
int SortedList::get(int index) {
    if (index < 0 || index >= size) {
        return -1;
    }
    return data[index];
}

void SortedList::print() {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}
bool SortedList::isEmpty() {
    return size == 0;
}
int SortedList::getLength() {
    return size;
}
int SortedList::getCapacity() {
    return capacity;
}
