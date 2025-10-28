#pragma once
#include <iostream>
template<typename Value>
class ArrayList{
private:
    Value* data;
    int length;
    int capacity;

    void resize(int newCapacity);

public:
    // Constructor
    ArrayList():data(nullptr), length(0), capacity(0){}
    ArrayList(int newCapacity) : data(new Value[newCapacity]), length(0), capacity(newCapacity){}
    ArrayList(const ArrayList<Value>& other);
    
    //Destructor
    ~ArrayList();
    
    void add(const Value& value);
    void clear();
    bool empty() const;

    //getters
    Value* getData(int index);
    int getLength() const;
    
    //operators
    ArrayList<Value>& operator=(const ArrayList& other);
    Value& operator[](int index);
};

// This will get the newCapacity value and using that it will resize the funciton 
template <typename Value>
inline void ArrayList<Value>::resize(int newCapacity)
{
    // Create a new data list with the newcapacity
    Value* newData = new Value[newCapacity];
    // Insert all data from the old list into the new one
    for(int i = 0; i < length; i++){
        // Insert the old data into new data
        newData[i] = data[i];
    }
    //Once we are done transferring the data, delete the old list
    delete[] data;
    // updata the data with the new data
    data = newData;
    // Change the capacity to the new one
    capacity = newCapacity;

}

// This will copy the information from other ArrayList and copy it into the current list
template <typename Value>
inline ArrayList<Value>::ArrayList(const ArrayList<Value> &other)
{
    // Change the curret capacity and length with the other arraylist's capacity and length
    capacity = other.capacity;
    length = other.length;
    //Check if the capacity is greater than 0, if it is we are going to copy the values inside the list
    if(capacity > 0){
        // refresh the current data and create a new one using the new capacity value.
        data = new Value[capacity];
        // Copy all element values one by one
        for(int i = 0; i < length; ++i){
            data[i] = other.data[i];
        }
    }else{
        // If the current capacity is currently 0, it has nothing
        data = nullptr;
    }
}

// Destructor : deleating data that's in the array
template <typename Value>
inline ArrayList<Value>::~ArrayList()
{
    clear();
}

// It will get the value and place the information into the ArrayList
template <typename Value>
inline void ArrayList<Value>::add(const Value &value)
{
    // Check if it's full and see if we need to re-size the list
    if(length == capacity){
        // get new capacity which will capacity*2;
        int newCapacity = capacity * 2;
        // If the capacity is 0 for some reason and it's trying to add, give a capacity value of 10
        if(newCapacity == 0){
            newCapacity =10;
        }
        //Once we find the new capacity, resize it
        resize(newCapacity);
    }
    // insert the new value inside the data
    data[length++] = value;
}

// Getter for Data
template <typename Value>
inline Value *ArrayList<Value>::getData(int index)
{
    //Check if the index is within 0 to length
    if(index <0 || index >= length){
        // If not return a nullptr
        return nullptr;
    }
    // If it's within the length, return the data
    return &data[index];
}

// Getter for length
template <typename Value>
inline int ArrayList<Value>::getLength() const
{
    return length;
}

// Clear data and reset the informations
template <typename Value>
inline void ArrayList<Value>::clear()
{
    delete[] data;
    data = nullptr;
    length = 0;
    capacity = 0;
}

// Checks if it's empty or not
template <typename Value>
inline bool ArrayList<Value>::empty() const
{
    // When length is 0, it means the it's empty
    if(length == 0){
        return true;
    }else{ // If not, then it's not empty
        return false;
    }
}

template <typename Value>
inline ArrayList<Value> &ArrayList<Value>::operator=(const ArrayList &other)
{
    // Check if the current arraylist is the same as the other arraylist
    if (this != &other) {
        //If not replace it
        // Delete the old arraylist
        delete[] data;
        // Update length
        length = other.length;
        // Update capacity
        capacity = other.capacity;
        // Create a new arrraylist with the new capacity and insert values one by one 
        data = new Value[capacity];
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }
    // Return the arraylist
    return *this;
}

template <typename Value>
inline Value &ArrayList<Value>::operator[](int index) {
    // Check if the index is with in 0 to length
    if (index < 0 || index >= length) {
        //cout<< ("ArrayList index out of bounds") << endl;

    }
    // If it is, return the data
    return data[index];
}
