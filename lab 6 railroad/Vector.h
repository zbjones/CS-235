//
// Created by Zachary Jones on 2/22/2020.
//

#ifndef LAB_6_RAILROAD_VECTOR_H
#define LAB_6_RAILROAD_VECTOR_H

#include "Deque.h"
#include <string>

template <typename T>
class Vector
{
private:
    Deque<T> *dataVector;
public:
    Vector() { dataVector = new Deque<T>(); }
    ~Vector()  { delete dataVector; }
    void push_back(const T& item) { dataVector->push_back(item); }
    void pop_back() { dataVector->pop_back(); }
    T& back() { return dataVector->back(); }
    size_t size() { return dataVector->size(); }
    T& at() { return dataVector->at(); }
    std::string toString() const { return dataVector->toString(); }

};



#endif //LAB_6_RAILROAD_VECTOR_H
