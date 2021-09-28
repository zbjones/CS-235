//
// Created by Zachary Jones on 2/22/2020.
//

#ifndef LAB_6_RAILROAD_QUEUE_H
#define LAB_6_RAILROAD_QUEUE_H

#include "Deque.h"
#include <string>

template <typename T>
class Queue {
private:
    Deque<T> *dataQueue;
public:
    Queue() { dataQueue = new Deque<T>(); }
    ~Queue() { delete dataQueue; }
    void push(const T& item) { dataQueue->push_back(item); }
    void pop() { dataQueue->pop_front(); }
    T& top() { return dataQueue->front(); }
    size_t size() { return dataQueue->size(); }
    T&  at() { return dataQueue->at(); }
    std::string toString() const { return dataQueue->toString(); }
};


#endif //LAB_6_RAILROAD_QUEUE_H
