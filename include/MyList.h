/*
* Created By: Ethan Chew (S10255990K), Lim Yu Yang (S10255816J)
* Group: 4
*/

#ifndef MYLIST_H
#define MYLIST_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <models/Actor.h>
#include <models/Movie.h>

// Enum representing the different types of sorting criteria
enum SortType {
    ALPHABETICALLY,    // Sort alphabetically (actor name/movie title)
    AGE,               // Sort by age (for actors)
    RELEASE_YEAR,      // Sort by release year (for movies)
    RATING             // Sort by rating
};

template<typename T>
class MyList
{
private:
    // Data structure to hold list elements dynamically (using smart pointers for automatic memory management)
    std::unique_ptr<T[]> data;
    int size;              // The current size of the list (number of elements)
    int capacity;          // The total capacity of the array before resizing is required

    // Method to resize the internal storage when the list is full
    void resize() {
        // Double the capacity if it's greater than 0, otherwise initialize with a capacity of 1
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        // Create new memory with the increased capacity
        auto new_data = std::make_unique<T[]>(new_capacity);

        // Move existing elements into the new array (avoid copying, move semantics)
        for (int i = 0; i < size; i++) {
            new_data[i] = std::move(data[i]);
        }

        // Point to the new data array and update the capacity
        data = std::move(new_data);
        capacity = new_capacity;
    }

    // QuickSort implementation to sort the list based on a provided comparison function
    void quickSort(int low, int high, std::function<bool(const void*, const void*)>& compare) {
        // Base case: if the low index is greater or equal to high, no sorting is needed
        if (low < high) {
            // Partition the array and get the pivot index
            int pivot = partition(low, high, compare);
            // Recursively sort elements before and after the pivot
            quickSort(low, pivot - 1, compare);
            quickSort(pivot + 1, high, compare);
        }
    }

    // Partition the array into two parts around the pivot and return the pivot index
    int partition(int low, int high, std::function<bool(const void*, const void*)>& compare) {
        T pivot = data[high];  // Choose the last element as pivot
        int i = low - 1;       // Index for the smaller element

        // Loop through the array and swap elements based on comparison with pivot
        for (int j = low; j < high; j++) {
            if (compare(data[j], pivot)) {  // If the element is less than the pivot
                i++;
                // Swap elements using move semantics to avoid unnecessary copies
                T temp = std::move(data[i]);
                data[i] = std::move(data[j]);
                data[j] = std::move(temp);
            }
        }

        // Swap the pivot element into the correct position
        T temp = std::move(data[i + 1]);
        data[i + 1] = std::move(data[high]);
        data[high] = std::move(temp);

        return i + 1; // Return the pivot index
    }

public:
    // Constructor initializes the list with a capacity of 1 and size of 0
    MyList() : data(std::make_unique<T[]>(1)), size(0), capacity(1) {};

    // Append a new item to the list, resizing if necessary
    void append(T item) {
        // Resize if current size exceeds capacity
        if (size >= capacity) {
            resize();
        }
        // Move the item into the list and increment size
        data[size] = std::move(item);
        size++;
    }

    // Insert an item at the specified index, shifting elements if needed
    void insert(int idx, T item) {
        if (idx >= 0 && idx <= size) {
            // Resize if current size exceeds capacity
            if (size >= capacity) {
                resize();
            }
            // Shift elements one position to the right to make space for the new item
            for (int i = size; i > idx; i--) {
                data[i] = std::move(data[i - 1]);
            }
            // Insert the new item
            data[idx] = std::move(item);
            size++;
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Remove an item at the specified index and shift elements to fill the gap
    void remove(int idx) {
        if (idx >= 0 && idx < size) {
            for (int i = idx; i < size - 1; i++) {
                data[i] = std::move(data[i + 1]);
            }
            size--;
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Get an item by index (non-const version)
    T& get(int idx) {
        if (idx >= 0 && idx < size) {
            return data[idx];
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Get an item by index (const version)
    const T& get(int idx) const {
        if (idx >= 0 && idx < size) {
            return data[idx];
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Print the list elements, checking if the type can be printed directly or needs special handling
    void print() const {
        for (int i = 0; i < size; i++) {
            // Print basic types directly (int, float, string)
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, std::string>) {
                std::cout << data[i] << " ";
            } else {
                // If T is a complex type, attempt to dynamically cast to Printable and call its print() method
                if (auto* printableObj = dynamic_cast<Printable*>(data[i])) {
                    printableObj->print();
                } else {
                    throw std::runtime_error("Error: Object is not Printable!");
                }
            }
        }
        std::cout << "\n";
    }

    // Replace an item at the specified index with a new item
    void replace(int idx, T item) {
        if (idx >= 0 && idx < size) {
            data[idx] = std::move(item);
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Find the index of the given item, returns -1 if not found
    int find(const T& item) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == item) {
                return i;
            }
        }
        return -1;
    }

    // Check if the list is empty
    bool is_empty() const {
        return size == 0;
    }

    // Get the current number of items in the list
    int get_length() const {
        return size;
    }

    // Get the total capacity of the list
    int get_capacity() const {
        return capacity;
    }

    void sort(SortType type) {
        // Determine the Comparator to use for the Quick Sort (either Alphabetically, by Age, or by Release Year) using Lambda Functions
        // Casts void pointers to accept any pointer type, then casts the pointer to the appropriate type
        std::function<bool(const void*, const void*)> comparator;
        switch (type) {
            // Compares the Name or Title for Actor and Movie respectively
            case ALPHABETICALLY:
                comparator = [](const void* a, const void* b) {
                    if (std::is_same_v<T, Actor*>) {
                        const auto* actorA = static_cast<const Actor*>(a);
                        const auto* actorB = static_cast<const Actor*>(b);
                        return actorA->getName().compare(actorB->getName()) < 0; //.compare returns an integer value, so we compare the value to return bool
                    }
                    if (std::is_same_v<T, Movie*>) {
                        const auto* movieA = static_cast<const Movie*>(a);
                        const auto* movieB = static_cast<const Movie*>(b);
                        return movieA->getTitle().compare(movieB->getTitle()) < 0; //.compare returns an integer value, so we compare the value to return bool
                    }
                    throw std::invalid_argument("Alphabetical comparison is not supported");
                };
            break;

            // Compares Actor classes by Age attribute
            case AGE:
                comparator = [](const void* a, const void* b) {
                    return reinterpret_cast<const Actor*>(a)->getBirthYear() < reinterpret_cast<const Actor*>(b)->getBirthYear();
                };
            break;

            // Compares Movie classes by ReleaseYear attribute
            case RELEASE_YEAR:
                comparator = [](const void* a, const void* b) {
                    return reinterpret_cast<const Movie*>(a)->getReleaseYear() < reinterpret_cast<const Movie*>(b)->getReleaseYear();
                };
            break;

            // Compares Movie/Actor classes by their rating
            case RATING:
                comparator = [](const void* a, const void* b) {
                    return reinterpret_cast<const Rateable*>(a)->getRating() < reinterpret_cast<const Rateable*>(b)->getRating();
                };
            break;
        }

        // Call quickSort with the chosen comparator
        quickSort(0, size - 1, comparator);
    }

    // Support for ranged iteration (to use MyList in range-based for loops)
    T* begin() {
        return &data[0];
    }

    T* end() {
        return &data[size];
    }

    const T* begin() const {
        return &data[0];
    }

    const T* end() const {
        return &data[size];
    }

    // Convenience method to access list items using the array indexing syntax
    T& operator[](int idx) {
        if (idx >= 0 && idx < size) {
            return data[idx];
        }

        throw std::invalid_argument("attempted to access list item out of bounds");
    }
};

#endif