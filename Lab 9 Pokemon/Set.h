//
// Created by zacha on 3/17/2020.
//

#ifndef LAB_9_POKEMON_SET_H
#define LAB_9_POKEMON_SET_H
#include "SetInterface.h"
#include <list>
#include <string>
#include <ostream>
#include <algorithm>

template <typename T>
class Set : public SetInterface<T>
{
private:
    std::list<T> myList;

public:
    Set() {}
    Set(std::initializer_list<T> list) : myList(list) { myList.sort(); myList.unique(); }
    ~Set() {myList.clear();};

    size_t count(const T& item) const
    { return (find(myList.begin(), myList.end(), item) != myList.end()); }

    std::string toString() const {
        std::string myString = "";
        std::string first = "";
        typename std::list<T>::const_iterator iter = myList.begin();
        while (iter != myList.end()) {
            myString = myString + first + *iter;
            iter++;
            first = ",";
        }
        return myString;
    }

    friend std::ostream& operator<<(std::ostream& os, Set& s)
    {
        std::string first = "";
        typename std::list<T>::iterator iter = s.myList.begin();
        while (iter != s.myList.end()) { os << first << *iter++; first = ","; }
        return os;
    }

    bool insert(const T& item){
        myList.insert(myList.begin(),item);
        myList.sort();
        myList.unique();
        return true;
    }

    void clear(){
        myList.clear();
    }

    size_t size() const {
        size_t size = 0;
        typename std::list<T>::const_iterator iter = myList.begin();
        while (iter != myList.end()){
            iter++;
            size++;
        }
        return size;
    }

};



#endif //LAB_9_POKEMON_SET_H
