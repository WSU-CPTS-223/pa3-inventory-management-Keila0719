#pragma once
#include "hashNode.hpp"
#include "product.hpp"

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;


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
    vector<Value> findCategory(const Key& category);

    int getCurrentSize();
    int getCapacity();
    double getLoadFactor();

private:
    HashNode<Key, Value>** table;
    int currentSize;
    int capacity;
    double loadFactor = 0.5; 
};

//Constructor
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(int newCapacity): currentSize(0), capacity(newCapacity){
    table = new HashNode<Key, Value>*[newCapacity];
    for (int i = 0; i < newCapacity; ++i) {
        table[i] = nullptr;
    }
} 
 
// Destructor : clear all the node inside the table
template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable(){
    // delete all nodes in the table
    clear();
    // delete the table
    delete[] table;
}

/* hash Function:
    Accepts:
            const Key& Key
    Return:
            int (index value)
    Description:
            Accepts the key and convert that key into an array to find and return the index of the key. 
*/
template <typename Key, typename Value>
int HashTable<Key, Value>::hash(const Key &key){
    std::hash<Key> keyID;
    return keyID(key) % capacity;
}

/* Insertion Function:
    Accepts:
            const Key& Key
            const Value& value
    Return:
            Bool (True = succesful, False = not successful)
    Description:
            Accepts the key and value of what we want to insert. We get the index of that key and see if that key already exist.
            If it does exist in the table, we will return false. If the key does not exist, we will create a new node with the
            inserted key
*/
template<typename Key, typename Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value){
    // Get the index of where this key will be inserted
    int index = hash(key);
    //get the current table of that index
    HashNode<Key,Value>* current = table[index];

    // Check if the key already exist so we won't have duplicates
    while (current != nullptr){
        // Check if the current key is the same as the insert key
        if(current->key == key){
            // If yes, return false, meaning the key already exist in the table
            return false;
        }
        // if the current key isn't the same, go to the next node
        current = current->next;
        // repeat this process until we reach the end, nullptr
    }
    
    // Since we don't have a duplicate create a new node with the given key and value
    HashNode<Key, Value>* newNode = new HashNode<Key, Value>(key, value);
    // Insert the new node at the root of the table
    newNode-> next = table[index];
    table[index] = newNode;
    
    // Since we inserted a node, increase the currentSize by 1
    currentSize++;

    // After inserting the new node, check if we need to rehash
    // We will need to rehash if the current size / capacity  is greater than or equal to the loadfactor which is 0.5
    if(double(currentSize)/capacity > loadFactor){
        rehash();
    }

    // return true, meaning the insertion was successful
    return true;
}

/* Remove Function:
    Accepts: 
            const Key& Key
    Return: 
            Bool (True = succesful, False = not successful)
    Description:
            Accepts the key of what we want to remove. It will first get the index of that key and get the table of that index.
            We will check if that removing key exist in the table by looping. If we couldn't find that key, it will return false
            to show it was not successful. If it was able to find that key, remove it and return true to show it was successful.
*/ 
template<typename Key, typename Value>
bool HashTable<Key, Value>::remove(const Key& key){
    // Get the index of where the key is
    int index = hash(key);
    // Get the current table of that index
    HashNode<Key,Value>* current = table[index];
    // Make a previous one which will be used later
    HashNode<Key,Value>* previous = nullptr;

    // Loop until we find the key or we reach the end
    while(current != nullptr){
        // Check if the current key is the same as the key we want to remove
        if(current->key == key){
            // If yes, remove that node
            // but first check if current is head. current is head when previous is a nullptr
            if(previous == nullptr){
                // remove current by making the current table as what we have after current
                table[index] = current->next;
            }else{  // Meaning the current is not a head
                // remove the current by skipping it
                previous->next = current->next;
            }
            // delete the current
            delete current;
            // Since we removed a node, decrease the currentsize by 1
            currentSize--;
            // After removing, return true to show it was successful
            return true;
        }
        // If the current key was not the same as the removing key, go to the next node and save the previous node
        previous = current;
        current = current->next;
    }
    // If we reach the end, meaning the key didn't exist in the table, return false to show it was not successful
    return false;
}

/* Find Function:
    Accepts: 
            const Key& Key
    Return: 
            Value* (value of that key's node, or nullptr = not successful)
    Description:
            Accepts the key of the finding key. Get the index of that key and get the table of that index. It will
            loop through the table to see if that key exist. If not it will return nullptr meaning that it was not
            successful. If it was able to find the key in the table, return that node's value.
*/ 
template<typename Key, typename Value>
Value* HashTable<Key, Value>::find(const Key& key){
    // Get the index of where the key is
    int index = hash(key);
    // Get the current table of that index
    HashNode<Key,Value>* current = table[index];

    // Loop the current table until we find the node or we reach the end of the table
    while (current != nullptr){
        // Check if the current key is the same as the finding key
        if(current->key == key){
            // If yes, return the value of that node
            return &(current->value);
        }
        // if the current key isn't the same, go to the next node
        current = current->next;
    }
    // When we reach the end of the table meaning that we couldn't find the finding key. return nullptr to show we were not successful
    return nullptr;
}

/* Clear Function:
    Accepts: NA
    Return: void
    Description:
            Starting from the index 0, get the table of the current index and delete the node one by one until it's empty.
*/ 
template<typename Key, typename Value>
void HashTable<Key, Value>::clear(){
    //Starting from index 0, loop through until the max capacity and delete each node
    for(int index = 0; index < capacity; index++){
        // Get the table of the current index
        HashNode<Key,Value>* current = table[index];
        // Until we reach the end of the loop, delete nodes one by one
        while(current != nullptr){
            // Use the temp variable to save the information after the current node
            HashNode<Key, Value>* temp = current->next;
            // Delete the current node
            delete current;
            // After deleting the current node, go to the next node
            current = temp;
        }
        // Once finished deleting each node, let the current index table to be nullptr to save it's empty
        table[index] = nullptr;
    }
}

/* ReHash Function:
    Accepts: NA
    Return: void
    Description:
            Rehash the table by making the capacity double and prime. Then, re-enter all the information into the new table.
*/ 
template <typename Key, typename Value>
void HashTable<Key, Value>::rehash(){
    // Get the current capacity and table
    int currentCap = capacity;
    HashNode<Key, Value>** currentTable = table; 

    // Create a new capacity which is a prime number and at least currentCap*2
    // First get the double the currentCap
    int newCap = currentCap*2;

    // Next, check if the newCap is a prime
    // create a bool variable that will be used in the loop to check if the current number is a prime or not
    bool isPrime = false;

    // Loop until the number is a prime number
    while(isPrime == false){
        // starting from 2 until current number-1, to see if any number will divide the newcap 
        int primeCheck = 0;
        for(int i = 2; i*i <= newCap; i++){
            // If we were able to divide, meaning it's not prime
            if(newCap % i == 0){
                primeCheck++;
            }
        }
        // If primeCheck is 0 meaning there was no number that was able to divide the currrent number, make the isPrime variable to true and end the loop
        if(primeCheck == 0){
            isPrime = true;
        }else{  // If not increase the newCap by one
            newCap++;
        }
    }
    // Once we found the new prime capacity that is double the previous one, rehash the table
    // Create a new table with new capacity
    table = new HashNode<Key, Value>* [newCap];

    // insert nullptr for all elements
    for (int i = 0; i < newCap; ++i) {
        table[i] = nullptr;
    }
    // update the capacity as the new capacity
    capacity = newCap;
    // Re-set the currentSize since it will increase as we insert from old table to new table
    currentSize = 0;
    // Insert each node in the old table into the new table
    int index = 0;
    // loop until it reches the end of the table
    while(index < currentCap){
        // get the current table at the index
        HashNode<Key, Value>* current = currentTable[index];
        // loop through that table and insert each node until it reches the end of the table
        while(current != nullptr){
            HashNode<Key, Value>* temp = current;
            // insert the current node's key and value into our new table
            insert(temp->key, temp->value);
            // go to the next node
            current = current->next;
            // delete the reference
            delete(temp);
        }
        // After the insertion of that index's table is done, increase the index to go to the next table
        index++;   
    }
    // Clear the current table
    delete[] currentTable;
}

template <typename Key, typename Value>
vector<Value> HashTable<Key, Value>::findCategory(const Key& category) {
    // Find the values with the same category inputted
    vector<Product>* result = this->find(category);
    // Check if the result was found or not
    if(result != nullptr){ // If found, return the vector
        return *result;
    } else {// if not return a empty vector
        return vector<Product>();
    }
}

// Getter for currentSize variable : return the currentSize
template <typename Key, typename Value>
int HashTable<Key, Value>::getCurrentSize()
{
    return currentSize;
}

// Getter for the capacity variable : return the capacity
template <typename Key, typename Value>
int HashTable<Key, Value>::getCapacity()
{
    return capacity;
}

// Getter for the loadFactor variable : return the loadFactor
template <typename Key, typename Value>
double HashTable<Key, Value>::getLoadFactor()
{
    return loadFactor;
}

