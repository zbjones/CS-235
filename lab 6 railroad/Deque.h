#ifndef Deque_h
#define Deque_h
#include <iostream>
#include "DequeInterface.h"
#include <string>
#include <algorithm>

template <typename T>
class Deque : public DequeInterface<T>{
public:
    Deque(void) {
        capacity = DEFAULT_CAPACITY;
        numItems =  0;
        frontIndex = 0;
        rearIndex = DEFAULT_CAPACITY - 1;
        userData = new T[DEFAULT_CAPACITY];
    }
    ~Deque(){
        delete[] userData;
    }
    void push_back(const T& item) {
        if (isFull()) {
            reallocate();
        }
        ++numItems;
        rearIndex = (rearIndex + 1) % capacity;
        userData[rearIndex] = item;
    }
    void push_front(const T& item) {
        if (isFull()) {
            reallocate();
        }
        ++numItems;
        if (frontIndex == 0) {
            frontIndex = capacity - 1;
        }
        else {
            frontIndex = frontIndex - 1;
        }
        userData[frontIndex] = item;
    }
    void pop_back() {
        --rearIndex;
        --numItems;
    }
    void pop_front() {
        if (frontIndex == capacity - 1) {
            frontIndex = 0;
        }
        else {
            ++frontIndex;
        };
        --numItems;
    }
    T& front(void) { return userData[frontIndex]; }
    T& back(void) { return userData[rearIndex]; }
    size_t size(void) const { return numItems; }
    T& at(size_t index) { return userData[index]; }
    bool empty() const { return numItems == 0; }

    std::string toString() const {
        if (empty()) {
            return "EMPTY";
        }
        else if (rearIndex == capacity - 1 && frontIndex == 0) {
            std::string stringToReturn = "";
            for (unsigned int i = 0; i < capacity; i++) {
                stringToReturn = stringToReturn + std::to_string(userData[i]) + " ";
            }
            return stringToReturn;
        }
        else {
            std::string stringToReturn = "";
            for (unsigned int i = frontIndex; i != (rearIndex + 1) % capacity; i = (i + 1) % capacity) {
                stringToReturn = stringToReturn + std::to_string(userData[i]) + " ";
            }
            return stringToReturn;
        }
    }
    friend std::ostream& operator<< (std::ostream& os, const Deque& myClass){
        os << myClass.toString();
        return os;
    }

private:
    size_t capacity;
    int numItems;
    size_t frontIndex;
    size_t rearIndex;
    T* userData;

    bool isFull() const { return numItems == capacity;}
    void reallocate() {
            size_t old_capacity = capacity;
            size_t new_capacity = 2 * capacity;
            T* newData = new T[new_capacity];
            size_t old = frontIndex;
            for (unsigned int i = 0; i < numItems; ++i) {
                newData[i] = userData[old];
                old = (old + 1) % capacity;
            }
            frontIndex = 0;
            rearIndex = numItems - 1;
            capacity = new_capacity;
            numItems = old_capacity;
            std::swap(userData, newData);
            delete[] newData;
        }




};



#endif /* Deque_h */