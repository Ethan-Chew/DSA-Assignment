/*
* Created By: Lim Yu Yang (S10255816J)
* Group: 4
*/

#pragma once
#ifndef MYDICT_H
#define MYDICT_H
#include <iostream>
#include <memory>

#include "MyList.h"

// Template to check if a type T is "string-like"
template<typename T>
struct is_string_like {
    static constexpr bool value =
            std::is_convertible_v<T, std::string_view> || // Check if T can be converted to std::string_view
            (std::is_pointer_v<T> && // Check if T is a pointer
            std::is_same_v<std::remove_cv_t<std::remove_pointer_t<T>>, char>); // Check if the underlying type is char
};

// Helper variable template to simplify checking if a type is string-like
template<typename T>
inline constexpr bool is_string_like_v = is_string_like<T>::value;

// Hash map implementation using separate chaining for collision resolution
template<typename K, typename V>
class MyDict
{
private:
    // Node structure for the linked list in each bucket
    struct Node
    {
        K key; // The key of the key-value pair
        V val; // The value of the key-value pair
        std::unique_ptr<Node> next; // Pointer to the next node in the linked list
        Node(const K& k, V v) : key(k), val(std::move(v)), next(nullptr) {};
    };

    // Initial number of buckets in the hash map
    static const int INIT = 128;

    // Load factor threshold for resizing the hash map
    static constexpr double LD_FAC = 0.5;

    // List of buckets, where each bucket is a linked list of nodes
    MyList<std::unique_ptr<Node>> buckets;
    int count; // Number of elements in the hash map

    // Hash function to compute the hash value for a given key
    uint64_t get_hash(const K &key) {
        if constexpr (std::is_integral_v<K>) {
            // For integer keys, use the key itself as the hash value
            return static_cast<size_t>(key);
        }
        else if constexpr (is_string_like_v<K>) {
            // Use the FNV-1a hash algorithm for string-like keys
            uint64_t hash = 0xcbf29ce484222325ULL; // FNV offset basis
            std::string_view sv = key; // Convert key to string_view for hashing
            for (char c : sv) {
                hash ^= static_cast<unsigned char>(c); // XOR with the current character
                hash *= 0x100000001b3ULL; // Multiply by the FNV prime
            }
            return hash;
        }
        else
        {
            // Throw an exception for unsupported key types
            throw std::invalid_argument("key type is not supported.");
        }
    }

    // Compute the bucket index from the hash value using a fast modulo operation
    size_t get_index(uint64_t hash, size_t size) {
        return hash & (size - 1); // Equivalent to hash % size, but faster
    }

    // Compute the bucket index for a given key
    size_t hash(const K &key) {
        return get_index(get_hash(key), buckets.get_length());
    }

    // Resize the hash map by doubling the number of buckets and rehashing all elements
    void rehash()
    {
        MyList<std::unique_ptr<Node>> new_buckets;
        int new_size = buckets.get_length() * 2;

        // Initialize the new buckets with null pointers
        for (int i = 0; i < new_size; i++)
        {
            new_buckets.append(nullptr);
        }

        // Rehash all existing elements into the new buckets
        for (int i = 0; i < buckets.get_length(); i++)
        {
            auto& bucket = buckets.get(i);
            while (bucket)
            {
                auto next = std::move(bucket->next); // Save the next node
                size_t new_idx = get_index(get_hash(bucket->key), new_size); // Compute new bucket index
                bucket->next = std::move(new_buckets.get(new_idx)); // Move the node to the new bucket
                new_buckets.replace(new_idx, std::move(bucket)); // Replace the bucket with the new node
                bucket = std::move(next); // Move to the next node in the old bucket
            }
        }
        buckets = std::move(new_buckets); // Replace the old buckets with the new ones
    }

public:
    // Constructor initializes the hash map with INIT buckets
    MyDict() : count(0) {
        for (int i = 0; i < INIT; i++) {
            buckets.append(nullptr);
        }
    }

    // Add a key-value pair to the hash map
    void add(const K& key, V val) {
        if (static_cast<double>(count + 1) / buckets.get_length() > LD_FAC) {
            rehash(); // Resize if the load factor is exceeded
        }

        size_t idx = hash(key); // Compute the bucket index
        auto& current = buckets.get(idx); // Get the bucket
        Node* curr_ptr = current.get(); // Get the head of the linked list

        // Traverse the linked list to check if the key already exists
        while (curr_ptr) {
            if (curr_ptr->key == key) {
                curr_ptr->val = std::move(val); // Update the value if the key exists
                return;
            }
            curr_ptr = curr_ptr->next.get();
        }

        // Insert the new key-value pair at the head of the linked list
        auto new_node = std::make_unique<Node>(key, std::move(val));
        new_node->next = std::move(current);
        current = std::move(new_node);
        count++; // Increment the element count
    }

    // Overloaded subscript operator for accessing and modifying values
    V& operator[](const K& key) {
        size_t idx = hash(key); // Compute the bucket index
        auto& current = buckets.get(idx); // Get the bucket
        Node* curr_ptr = current.get(); // Get the head of the linked list

        // Traverse the linked list to check if the key exists
        while (curr_ptr) {
            if (curr_ptr->key == key) {
                return curr_ptr->val; // Return the value if the key exists
            }
            curr_ptr = curr_ptr->next.get();
        }

        // Resize if the load factor is exceeded
        if (static_cast<double>(count + 1) / buckets.get_length() > LD_FAC) {
            rehash();
            idx = hash(key); // Recompute the bucket index after resizing
        }

        // Insert a new key-value pair at the head of the linked list
        auto new_node = std::make_unique<Node>(key, V{});
        V& ref = new_node->val; // Get a reference to the new value
        new_node->next = std::move(buckets.get(idx)); // Move the current head to the next node
        buckets.replace(idx, std::move(new_node)); // Replace the bucket with the new node
        count++; // Increment the element count
        return ref; // Return the reference to the new value
    }

    // Safely get a pointer to the value associated with a key
    V* safe_get(const K& key) {
        size_t idx = hash(key); // Compute the bucket index
        auto& current = buckets.get(idx); // Get the bucket
        Node* curr_ptr = current.get(); // Get the head of the linked list

        // Traverse the linked list to find the key
        while (curr_ptr) {
            if (curr_ptr->key == key) {
                return &curr_ptr->val; // Return a pointer to the value if the key exists
            }
            curr_ptr = curr_ptr->next.get();
        }
        return nullptr; // Return nullptr if the key does not exist
    }

    // Remove a key-value pair from the hash map
    bool remove(const K& key) {
        size_t idx = hash(key); // Compute the bucket index
        auto& bucket = buckets.get(idx); // Get the bucket

        if (!bucket) {
            return false; // Return false if the bucket is empty
        }

        // Check if the key is in the head of the linked list
        if (bucket->key == key) {
            bucket = std::move(bucket->next); // Remove the head node
            count--; // Decrement the element count
            return true;
        }

        // Traverse the linked list to find the key
        Node* current = bucket.get();
        while (current->next) {
            if (current->next->key == key) {
                current->next = std::move(current->next->next); // Remove the node
                count--; // Decrement the element count
                return true;
            }
            current = current->next.get();
        }
        return false; // Return false if the key was not found
    }

    // Display the contents of the hash map in a formatted manner
    void display() const {
        if (is_empty()) {
            std::cout << "{ }" <<"\n";
            return;
        }

        std::cout << "{" << "\n";
        bool first_item = true;

        // Iterate through all buckets
        for (int i = 0; i < buckets.get_length(); i++) {
            const auto& current = buckets.get(i); // Get the bucket
            Node* curr_ptr = current.get(); // Get the head of the linked list

            // Traverse the linked list and print each key-value pair
            while (curr_ptr) {
                if (!first_item) {
                    std::cout << "," << "\n";
                }
                std::cout << "  " << curr_ptr->key << " : " << curr_ptr->val;
                first_item = false;
                curr_ptr = curr_ptr->next.get();
            }
        }
        std::cout << "\n" << "}" << "\n";
    }

    // Return all keys in the hash map as a container
    template <typename Container>
    Container *keys() const {
        Container container = new Container();

        // Iterate through all buckets
        for (int i = 0; i < buckets.get_length(); i++) {
            const std::unique_ptr<Node> &cur = buckets.get(i); // Get the bucket
            Node *cur_ptr = cur.get(); // Get the head of the linked list

            // Traverse the linked list and append each key to the container
            while (cur_ptr != nullptr) {
                container.append(cur_ptr->key.get());
                cur_ptr = cur_ptr->next.get();
            }
        }

        return container;
    }

    // Return all values in the hash map as a container
    template <typename Container>
    Container *values() const {
        Container container = new Container();

        // Iterate through all buckets
        for (int i = 0; i < buckets.get_length(); i++) {
            const std::unique_ptr<Node> &cur = buckets.get(i); // Get the bucket
            Node *cur_ptr = cur.get(); // Get the head of the linked list

            // Traverse the linked list and append each value to the container
            while (cur_ptr != nullptr) {
                container.append(cur_ptr->val.get());
                cur_ptr = cur_ptr->next.get();
            }
        }

        return container;
    }

    // Return all values in the hash map as a MyList of raw pointers
    auto *values() const {
        // Create a MyList of raw pointers to the values
        auto* vals = new MyList<std::remove_reference_t<decltype(*std::declval<V>())>*>();

        // Iterate through all buckets
        for (int i = 0; i < buckets.get_length(); i++) {
            const auto& current = buckets.get(i); // Get the bucket
            Node* curr_ptr = current.get(); // Get the head of the linked list

            // Traverse the linked list and append each value to the list
            while (curr_ptr != nullptr) {
                vals->append(curr_ptr->val.get());
                curr_ptr = curr_ptr->next.get();
            }
        }

        return vals;
    }

    // Check if the hash map is empty
    bool is_empty() const {
        return count == 0;
    }

    // Get the number of elements in the hash map
    size_t get_size() const {
        return count;
    }
};

#endif