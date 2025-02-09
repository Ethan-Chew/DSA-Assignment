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

template<typename T>
struct is_string_like {
    static constexpr bool value =
            std::is_convertible_v<T, std::string_view> || // check if T can be converted into a string view
            (std::is_pointer_v<T> && // if its a pointer
            std::is_same_v<std::remove_cv_t<std::remove_pointer_t<T>>, char>); 
            // remove the pointer from the type, and remove the const/volatile from the type
};

template<typename T>
inline constexpr bool is_string_like_v = is_string_like<T>::value; // check the value of is_string_like


// hash map that uses an internal linked list for colision resolution
// in laymans terms: each mapping of the hashmap resolves to a bucket/linked list
// the linked list stores k/v where k is the full key, and v is the unique pointer/object 
// this ensures that collisions will not happen, as the program will crawl the bucket to resolve a full match 
// for the provided key
template<typename K, typename V>
class MyDict
{
private:
    struct Node
    {
        K key;
        V val;
        std::unique_ptr<Node> next;
        Node(const K& k, V v) : key(k), val(std::move(v)), next(nullptr) {};
    };

    // INIT defines how many "buckets" we start off with
    static const int INIT = 128; 

    // load factor is when it resizes, 0.5 means that the list will resize when 
    // it's half full
    static constexpr double LD_FAC = 0.5;

    MyList<std::unique_ptr<Node>> buckets;
    int count;

    // hash method
    uint64_t get_hash(const K &key) {
        if constexpr (std::is_integral_v<K>) {
            // for integers we can just use the int as a key
            return static_cast<size_t>(key);
        }
        else if constexpr (is_string_like_v<K>) {
            // textbook fnv-1a algorithm for string hashing
            uint64_t hash = 0xcbf29ce484222325ULL;
            std::string_view sv = key;
            for (char c : sv) {
                hash ^= static_cast<unsigned char>(c);
                hash *= 0x100000001b3ULL;
            }
            return hash;
        }
        else
        {
            throw std::invalid_argument("key type is not supported.");
        }
    }

    // finds bucket index using the hash value, fast modulo bithack
    size_t get_index(uint64_t hash, size_t size) {
        return hash & (size - 1);
    }

    // gets the bucket index that the key maps to
    size_t hash(const K &key) {
        return get_index(get_hash(key), buckets.get_length());
    }

    // doubles the size of the hashmap and rehashes all existing entries
    void rehash()
    {
        MyList<std::unique_ptr<Node>> new_buckets;
        int new_size = buckets.get_length() * 2;

        for (int i = 0; i < new_size; i++)
        {
            new_buckets.append(nullptr);
        }

        for (int i = 0; i < buckets.get_length(); i++)
        {
            auto& bucket = buckets.get(i);
            while (bucket)
            {
                auto next = std::move(bucket->next);
                size_t new_idx = get_index(get_hash(bucket->key), new_size);
                bucket->next = std::move(new_buckets.get(new_idx));
                new_buckets.replace(new_idx, std::move(bucket));
                bucket = std::move(next);
            }
        }
        buckets = std::move(new_buckets);
    }

public:
    MyDict() : count(0) {
        // init buckets as per the init defined
        for (int i = 0; i < INIT; i++) {
            buckets.append(nullptr);
        }
    }

    // adds a KV pair to dict by resolving the bucket it should be in
    // and prepends it to the linked list, otherwise updates the existing value
    void add(const K& key, V val) {
        if (static_cast<double>(count + 1) / buckets.get_length() > LD_FAC) {
            rehash();
        }

        size_t idx = hash(key);
        auto& current = buckets.get(idx);
        Node* curr_ptr = current.get();

        while (curr_ptr) {
            if (curr_ptr->key == key) {
                curr_ptr->val = std::move(val);
                return;
            }
            curr_ptr = curr_ptr->next.get();
        }

        auto new_node = std::make_unique<Node>(key, std::move(val));
        new_node->next = std::move(current);
        current = std::move(new_node);
        count++;
    }

    // allows operators T val = dict[K] and dict[K] = val 
    // if key exists, it returns a ref to the existing value
    // otherwise, it creates a new node, and returns a ref to the 
    // newly inserted value
    V& operator[](const K& key) {
        size_t idx = hash(key);
        auto& current = buckets.get(idx);
        Node* curr_ptr = current.get();

        while (curr_ptr) {
            if (curr_ptr->key == key) {
                // return val ref if it exists
                return curr_ptr->val;
            }
            curr_ptr = curr_ptr->next.get();
        }

        // expand if load factor is reached
        if (static_cast<double>(count + 1) / buckets.get_length() > LD_FAC) {
            rehash();
            idx = hash(key);
        }

        auto new_node = std::make_unique<Node>(key, V{});
        V& ref = new_node->val;
        new_node->next = std::move(buckets.get(idx));
        buckets.replace(idx, std::move(new_node));
        count++;
        // return ref to newly created val
        return ref;
    }

    // Used when key may not exist to prevent memory error
    V* safe_get(const K& key) {
        size_t idx = hash(key);
        auto& current = buckets.get(idx);
        Node* curr_ptr = current.get();

        while (curr_ptr) {
            if (curr_ptr->key == key) {
                return &curr_ptr->val;
            }
            curr_ptr = curr_ptr->next.get();
        }
        return nullptr;
    }

    // finds the key and removes if it exists
    bool remove(const K& key) {
        size_t idx = hash(key);
        auto& bucket = buckets.get(idx);

        if (!bucket) {
            return false;
        }

        if (bucket->key == key) {
            bucket = std::move(bucket->next);
            count--;
            return true;
        }

        Node* current = bucket.get();
        while (current->next) {
            if (current->next->key == key) {
                current->next = std::move(current->next->next);
                count--;
                return true;
            }
            current = current->next.get();
        }
        return false;
    }

    // displays a nicely formatted version of the map content
    void display() const {
        if (is_empty()) {
            std::cout << "{ }" <<"\n";
            return;
        }

        std::cout << "{" << "\n";
        bool first_item = true;

        for (int i = 0; i < buckets.get_length(); i++) {
            const auto& current = buckets.get(i);
            Node* curr_ptr = current.get();

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

    // basically returns all the keys of the hashmap in a container provided
    // given container provides an append method, otherwise behaviour is undefined
    template <typename Container>
    Container *keys() const {
        Container container = new Container();

        for (int i = 0; i < buckets.get_length(); i++) {
            const std::unique_ptr<Node> &cur = buckets.get(i);
            Node *cur_ptr = cur.get();

            while (cur_ptr != nullptr) {
                container.append(cur_ptr->key.get());
                cur_ptr = cur_ptr->next.get();
            }
        }

        return container;
    }

    // same as above, but returns values
    template <typename Container>
    Container *values() const {
        Container container = new Container();

        for (int i = 0; i < buckets.get_length(); i++) {
            const std::unique_ptr<Node> &cur = buckets.get(i);
            Node *cur_ptr = cur.get();

            while (cur_ptr != nullptr) {
                container.append(cur_ptr->val.get());
                cur_ptr = cur_ptr->next.get();
            }
        }

        return container;
    }

    // same as above, but returns in a MyList instance instead.
    auto *values() const {
        // MyList<T> where T is a dummy value of type V without instantiation, dereferences to get raw value type
        // then removes any references from the type
        // * for pointer type
        // basically returns a list of raw pointers (we can't be giving away unique ptr ownership, the table must own it)
        auto* vals = new MyList<std::remove_reference_t<decltype(*std::declval<V>())>*>();

        // Iterate through every element in the bucket
        for (int i = 0; i < buckets.get_length(); i++) {
            const auto& current = buckets.get(i); // Returns the unique_ptr<Node>
            Node* curr_ptr = current.get();

            // Iterate through nodes with the same ID
            while (curr_ptr != nullptr) {
                vals->append(curr_ptr->val.get());
                curr_ptr = curr_ptr->next.get();
            }
        }

        return vals;
    }

    bool is_empty() const {
        return count == 0;
    }

    size_t get_size() const {
        return count;
    }
};

#endif