//
// Created by Zachary Jones on 2/22/2020.
//

#ifndef LAB_6_RAILROAD_STATION_H
#define LAB_6_RAILROAD_STATION_H

#include "Queue.h"
#include "Stack.h"
#include "Vector.h"
#include <string>

template <typename T>
class Station {
private:
    Vector<T> *myTrain;
    Stack<T> *myStack;
    Queue<T> *myQueue;
    T turnTableCar;
    bool empty;
public:
    Station() {
        myTrain = new Vector<T>();
        myStack = new Stack<T>();
        myQueue = new Queue<T>();
        empty = true;
        turnTableCar = 0;
    };
    ~Station() {
        delete myTrain;
        delete myStack;
        delete myQueue;
    };
    void addCar(T carToAdd) {
        if (!empty) {
            throw 998;
        }
        else {
            turnTableCar = carToAdd;
            empty = false;
        }
    }
    void removeCar() {
        if (empty) {
            throw 999;
        }
        empty = true;
        myTrain->push_back(turnTableCar);
    }
    std::string removeStack() {
        if (empty) {
            if (myStack->size() == 0) {
                throw 997;
            } else {
                turnTableCar = myStack->top();
                myStack->pop();
                empty = false;
                return " OK";
            }
        }
        else {
            throw 998;
        }
    }
    std::string removeQueue() {
        if (empty) {
            if (myQueue->size() == 0) {
                throw 996;
            }
            else {
                turnTableCar = myQueue->top();
                myQueue->pop();
                empty = false;
                return " OK";
            }
        }
        else {
            throw 998;
        }
    }
    std::string toString() const { return myTrain->toString(); }
    std::string addStack() {
        if (!empty) {
            myStack->push(turnTableCar);
            empty = true;
        }
        else {
            throw 999;
        }
        return "OK";
    }
    std::string addQueue() {
        if (!empty) {
            myQueue->push(turnTableCar);
            empty = true;
        }
        else {
            throw 999;
        }
        return "OK";
    }
    std::string topStack() {
        return std::to_string(myStack->top());
    }
    std::string topQueue() {
        return std::to_string(myQueue->top());
    }
    std::string topStation() {
        return std::to_string(turnTableCar);
    }
    size_t sizeStack() {
        return myStack->size();
    }
    size_t sizeQueue() {
        return myQueue->size();
    }





};


#endif //LAB_6_RAILROAD_STATION_H
