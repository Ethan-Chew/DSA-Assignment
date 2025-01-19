#pragma once
#ifndef MYDICT_H
#define MYDICT_H
#include <iostream>
#include <memory>
#include "MyList.h"

template<typename T>
struct is_string_like {
    static constexpr bool value =
            std::is_convertible_v<T, std::string_view> ||
            (std::is_pointer_v<T> &&
             std::is_same_v<std::remove_cv_t<std::remove_pointer_t<T>>, char>);
};

template<typename T>
inline constexpr bool is_string_like_v = is_string_like<T>::value;

template<typename K, typename V>
class MyDict
{
private:
    struct Node
    {
        K key;
        V val;
        std::unique_ptr<Node> next;
        Node(const K& k, const V& v) : key(k), val(v), next(nullptr) {};
    };

    static const int INIT = 128;
    static constexpr double LD_FAC = 0.5;

    MyList<std::unique_ptr<Node>> buckets;
    int count;

    uint64_t get_hash(const K &key) {
        if constexpr (std::is_integral_v<K>) {
            return static_cast<size_t>(key);
        }
        else if constexpr (is_string_like_v<K>) {
            uint64_t hash = 0xcbf29ce484222325ULL;
            std::string_view sv = key;
            for (char c : sv) {
                hash ^= static_cast<unsigned char>(c);
                hash *= 0x100000001b3ULL;
            }
            return hash;
        }
    }

    size_t get_index(uint64_t hash, size_t size) {
        return hash & (size - 1);
    }

    size_t hash(const K &key) {
        return get_index(get_hash(key), buckets.get_length());
    }

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
        for (int i = 0; i < INIT; i++) {
            buckets.append(nullptr);
        }
    }

    void add(const K& key, const V val) {
        if (static_cast<double>(count + 1) / buckets.get_length() > LD_FAC) {
            rehash();
        }

        size_t idx = hash(key);
        auto& current = buckets.get(idx);
        Node* curr_ptr = current.get();

        while (curr_ptr) {
            if (curr_ptr->key == key) {
                curr_ptr->val = val;
                return;
            }
            curr_ptr = curr_ptr->next.get();
        }

        auto new_node = std::make_unique<Node>(key, val);
        new_node->next = std::move(current);
        current = std::move(new_node);
        count++;
    }

    V& operator[](const K& key) {
        size_t idx = hash(key);
        auto& current = buckets.get(idx);
        Node* curr_ptr = current.get();

        while (curr_ptr) {
            if (curr_ptr->key == key) {
                return curr_ptr->val;
            }
            curr_ptr = curr_ptr->next.get();
        }

        if (static_cast<double>(count + 1) / buckets.get_length() > LD_FAC) {
            rehash();
            idx = hash(key);
        }

        auto new_node = std::make_unique<Node>(key, V{});
        V& ref = new_node->val;
        new_node->next = std::move(buckets.get(idx));
        buckets.replace(idx, std::move(new_node));
        count++;
        return ref;
    }

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

    bool is_empty() const {
        return count == 0;
    }

    size_t get_size() const {
        return count;
    }
};

#endif