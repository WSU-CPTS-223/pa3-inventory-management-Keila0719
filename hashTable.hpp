#pragma once
#include "hashNode.hpp"
#include <iostream>
#include <vector>

using std::vector;

template<typename Key, typename Value>
class HashTable{
public:
    // Construction
    HashTable(int newCapacity);
    // Destruction
    ~HashTable();    

    int hash(const Key& key);
    bool insert(const Key& key, const Value& value);
    bool remove(const Key& key);
    Value* find(const Key& key);
    void clear();
    void rehash();

    int getCurrentSize();
    int getCapacity();
    double getLoadFactor();

private:
    vector<HashNode<Key, Value>*> table;
    int currentSize;
    int capacity;
    double loadFactor = 0.5; 
};