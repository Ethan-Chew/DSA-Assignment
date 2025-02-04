#ifndef MYLIST_H
#define MYLIST_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <models/Actor.h>
#include <models/Movie.h>

enum SortType {
    ALPHABETICALLY,
    AGE,
    RELEASE_YEAR,
    RATING
};

template<typename T>
class MyList
{
private:
    std::unique_ptr<T[]> data;
    int size;
    int capacity;

    void resize() {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        auto new_data = std::make_unique<T[]>(new_capacity);

        for (int i = 0; i < size; i++) {
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
        capacity = new_capacity;
    }

    void quickSort(int low, int high, std::function<bool(const void*, const void*)>& compare) {
        if (low < high) {
            int pivot = partition(low, high, compare);
            quickSort(low, pivot - 1, compare);
            quickSort(pivot + 1, high, compare);
        }
    }

    int partition(int low, int high, std::function<bool(const void*, const void*)>& compare) {
        T pivot = data[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (compare(data[j], pivot)) {
                i++;
                T temp = std::move(data[i]);
                data[i] = std::move(data[j]);
                data[j] = std::move(temp);
            }
        }

        T temp = std::move(data[i + 1]);
        data[i + 1] = std::move(data[high]);
        data[high] = std::move(temp);

        return i + 1;
    }

public:
    MyList() : data(std::make_unique<T[]>(1)), size(0), capacity(1) {};

    void append(T item) {
        if (size >= capacity) {
            resize();
        }
        data[size] = std::move(item);
        size++;
    }

    void insert(int idx, T item) {
        if (idx >= 0 && idx <= size) {
            if (size >= capacity) {
                resize();
            }
            for (int i = size; i > idx; i--) {
                data[i] = std::move(data[i - 1]);
            }
            data[idx] = std::move(item);
            size++;
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

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

    T& get(int idx) {
        if (idx >= 0 && idx < size) {
            return data[idx];
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    const T& get(int idx) const {
        if (idx >= 0 && idx < size) {
            return data[idx];
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
                std::cout << data[i] << " ";
            } else if constexpr (std::is_same_v<T, Actor*> || std::is_same_v<T, Movie*>) {
                data[i]->print();
            } else {
                std::cout << std::string(data[i]) << " ";
            }
        }
        std::cout << "\n";
    }

    void replace(int idx, T item) {
        if (idx >= 0 && idx < size) {
            data[idx] = std::move(item);
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    int find(const T& item) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == item) {
                return i;
            }
        }
        return -1;
    }

    bool is_empty() const {
        return size == 0;
    }

    int get_length() const {
        return size;
    }

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

            // Compares Movie/Actor classes by their rating
            case RATING:
                comparator = [](const void* a, const void* b) {
                    const auto* objA = static_cast<const Rateable*>(a);
                    const auto* objB = static_cast<const Rateable*>(b);

                    if (!objA || !objB) {
                        throw std::invalid_argument("Comparison by Rating requires Rateable objects");
                    }
                    return objA->getRating() > objB->getRating();
                };
            break;
        }

        quickSort(0, size - 1, comparator);
    }

    // support for ranged iterator

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

    // convenience

    T& operator[](int idx) {
        if (idx >= 0 && idx < size) {
            return data[idx];
        }

        throw std::invalid_argument("attempted to access list item out of bounds");
    }
};

#endif