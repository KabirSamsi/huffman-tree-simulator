#ifndef CS_124_Lab_4_HASHMAP_HPP
#define CS_124_Lab_4_HASHMAP_HPP

#include <vector>
#include <iostream>

template <typename PairKey, typename PairValue>
class HashMapNode {
public:
    PairKey key;
    PairValue value;
    HashMapNode(PairKey key, PairValue value) {
        this -> key = key;
        this -> value = value;
    }
};

template <typename HashMapKey, typename HashMapValue>
class HashMap {
public:
    HashMap(int (*hashFunction)(HashMapKey), int capacity) {
        this -> hashFunction = hashFunction;
        this -> capacity = capacity;
        this -> size = 0;
        for (int i = 0; i < capacity; i++) {
            this -> table.push_back(nullptr);
        }
    }
    bool exists(HashMapKey key) {
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                return true;
            }
            index = (index + 1) % capacity;
        }
        return false;
    }
    HashMapValue get(HashMapKey key) {
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                return table[index] -> value;
            }
            index = (index + 1) % capacity;
        }
        return HashMapValue();
    }
    void set(HashMapKey key, HashMapValue value) {
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                table[index] -> value = value;
                return;
            }
            index = (index + 1) % capacity;
        }
        table[index] = new HashMapNode<HashMapKey, HashMapValue>(key, value);
        size++;
    }
    void remove(HashMapKey key) {
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                delete table[index];
                table[index] = nullptr;
                size--;
                return;
            }
            index = (index + 1) % capacity;
        }
    }
    ~HashMap() {
        for (auto i : table) {
            delete i;
        }
    }
private:
    int (*hashFunction)(HashMapKey);
    int capacity = 0;
    int size = 0;
    std::vector<HashMapNode<HashMapKey, HashMapValue>*> table;
};


#endif