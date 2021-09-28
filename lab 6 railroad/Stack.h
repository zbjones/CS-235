//
// Created by Zachary Jones on 2/22/2020.
//

#ifndef LAB_6_RAILROAD_STACK_H
#define LAB_6_RAILROAD_STACK_H

#include "Deque.h"
#include <string>

template <typename T>
class Stack {
private:
    Deque<T> *dataStack;
public:
    Stack() { dataStack = new Deque<T>(); };
    ~Stack() { delete dataStack; }
    void push(const T& item) { dataStack->push_front(item); }
    void pop() { dataStack->pop_front(); }
    T& top() { return dataStack->front(); }
    size_t size() { return dataStack->size(); }
    T& at(size_t index) { return dataStack->at(index); }
    std::string toString() const { return dataStack->toString(); }
};
#endif //LAB_6_RAILROAD_STACK_H
