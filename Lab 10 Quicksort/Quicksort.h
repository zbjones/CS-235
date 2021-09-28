//
// Created by zacha on 3/26/2020.
//

#ifndef LAB_10_QUICKSORT_QUICKSORT_H
#define LAB_10_QUICKSORT_QUICKSORT_H

#include "QSInterface.h"
#include <string>
#include <iostream>

template<typename T>
class Quicksort : public QSInterface<T> {

private:
    size_t arrayCapacity;
    size_t arraySize;
    T* qsArray;
public:
    Quicksort() {
        arraySize = 0;
        arrayCapacity = 0;
    };
    //handle array deletes in destructor
    ~Quicksort() {
        delete[] qsArray;
    };

    bool createArray(size_t capacity) {
        if (arrayCapacity > 0) {
            delete[] qsArray;
            arraySize = 0;
            arrayCapacity = 0;
        }
        qsArray = new T[capacity];
        arrayCapacity = capacity;
        return true;
    }

    size_t capacity() const {
        return arrayCapacity;
    }

    bool addElement(T element) {
        if (arraySize == arrayCapacity) {
            realloc();
        }
        qsArray[arraySize++] = element;
        return true;
    }

    void realloc() {
        T* tempArray = new T[arrayCapacity * 2];
        T* originalToDelete = qsArray;
        for (unsigned int i = 0; i < arrayCapacity; i++) {
            tempArray[i] = qsArray[i];
        }
        arrayCapacity = arrayCapacity * 2;
        qsArray = tempArray;
        delete[] originalToDelete;
    };

    size_t size() const {
        return arraySize;
    }

    bool clear() {
        //easiest way to avoid memory leaks: delete and reinitialize on a clear.
        delete[] qsArray;
        qsArray = new T[arrayCapacity];
        arraySize = 0;
        return true;
    }

    std::string toString() const {
        std::string strToReturn;
        if (arraySize == 0) {
            strToReturn += "Empty";
        }
        std::string noCommaFirst = "";
        for (unsigned int i = 0; i < arraySize; i++) {
            strToReturn += noCommaFirst + std::to_string(qsArray[i]);
            noCommaFirst = ",";
        }
        return strToReturn;
    }

    //friend insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Quicksort& qsObject) {
        return os << qsObject.toString();
    }

    //return the middle value of the function.  Use a -1 in main for the right index, correct for it here to make everything
    //play nicely together for all test cases
    int medianOfThree(size_t left, size_t right) {
        if (left >= right + 1|| arraySize == 0 || left < 0) {
            return -1;
        }
        int middleIndex = (left + right + 1) / 2;
//        right--;
        while (qsArray[middleIndex] > qsArray[right] || qsArray[left] > qsArray[middleIndex]) {
            if (qsArray[middleIndex] > qsArray[right]) {
                swap(middleIndex, right);
            }
            if (qsArray[left] > qsArray[middleIndex]) {
                swap(left, middleIndex);
            }
        }
         return middleIndex;
    }

    //basic swap function, swaps two array values, takes in the indices
    void swap(size_t index1, size_t index2) {
        T tempData = qsArray[index1];
        qsArray[index1] = qsArray[index2];
        qsArray[index2] = tempData;
    }

    //partition function: partition and sort using bubble sort method
    int partition(size_t left, size_t right, size_t pivotIndex) {
        //false cases
        if (left >= right || arraySize == 0 || left < 0 || pivotIndex > right) {
            return -1;
        }
        swap(pivotIndex, left);
        size_t up = left + 1;
        size_t down = right - 1;
        do {
            while (qsArray[left] >= qsArray[up]) {
                if (up == right - 1) {
                    break;
                }
                up++;
            }
            while (qsArray[left] < qsArray[down]) {
                if (down == left) {
                    break;
                }
                down--;
            }
            if (up < down) {
                swap(up, down);
            }
        } while (up < down);

        swap(left, down);
        return down;
    };

    //recursive starter function for sort all
    bool sortAll() {
        if (arraySize < 0) return false;
        sort(0, arraySize - 1);
        return true;
    }

    //recursive starter function for one sort
    bool sort(size_t left, size_t right) {
        sortRecursive(left, right);
        return true;
    }

    //Main recursive sorting function.
    void sortRecursive(int left, int right) {
        //Handle three bases cases: right next to each other, the same index, and out of bounds/not allowed
        if (right == left) return;
        if (right - left == 1){
            if (qsArray[right] > qsArray[left]){
                return;
            }
            else {
                swap(left, right);
                return;
            }
        }
        if (left < 0 || right > static_cast<int>(arraySize - 1)  || right < left || left > right) return;
        //business of recursive function: call median of three to get the pivotindex, use pivot index to partition and get
        //new index.  Sort Left and Right sides of new index recursively.
        int pivotIndex = medianOfThree(left, right);
        int newIndex = partition(left, right, pivotIndex);
        sort(left, newIndex - 1);
        sort(newIndex + 1, right);
    }


};


#endif //LAB_10_QUICKSORT_QUICKSORT_H
