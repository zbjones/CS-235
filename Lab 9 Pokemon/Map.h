//
// Created by zacha on 3/19/2020.
//
#ifndef LAB_9_POKEMON_MAP_H
#define LAB_9_POKEMON_MAP_H
#include "MapInterface.h"
#include "Set.h"
#include <iostream>
#include <string>
#include <utility>
#include <cmath>


template <typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
private:
    size_t capacity;
    std::pair<K, V>* mapPairs[DEFAULT_MAP_HASH_TABLE_SIZE];

public:
    HashMap<K, V>()  {
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            mapPairs[i] = new std::pair<K, V>();
        }
    }
    //empty destructor because we manually call clear in main.
    ~HashMap() { }

    std::string toString(void) const {
        std::string strToReturn;
        size_t sizeMap = size();
        strToReturn = strToReturn + std::to_string(sizeMap) + "/" + std::to_string(DEFAULT_MAP_HASH_TABLE_SIZE) + "\n";
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            if (mapPairs[i]->first.length() > 0) {
                strToReturn = strToReturn + "[" + std::to_string(i) + ":" + mapPairs[i]->first + "->" +
                              stringifyData(mapPairs[i]->second) + "]" + "\n";
            }
        }
        return strToReturn;
    }
    // helper function to be polymorphic in toString() function above
    std::string stringifyData(std::string str) const {
        return str;
    }
    std::string stringifyData(Set<std::string> set) const {
        return set.toString();
    }

    //hash function
    size_t hash(std::string strToHash) {
        size_t value = 0;
        size_t strToHashSize = strToHash.size();
        for(unsigned int i = 0; i < strToHash.size(); i++) {
            value = value + (strToHash[i] * pow(HASH_CONSTANT, strToHashSize - 1 - i));
        }
        value = value % DEFAULT_MAP_HASH_TABLE_SIZE;
        return value;
    }

    //given function, dereferencing bracket operators.  I wrote my own getter functions below to replace some of this functionality.
    V& operator[](const K& key) {
        size_t index = hash(key);
        size_t k = 1;
        while (1)
        {
            if (mapPairs[index]->first.length() > 0)
            {
                if (mapPairs[index]->first == key) break;
                int iteratorNum = 0;
                while (mapPairs[index]->first.length() != 0) {
                    index = (index + k) % DEFAULT_MAP_HASH_TABLE_SIZE;
                    k += 2;
                    iteratorNum++;
                }
            }
            else { mapPairs[index]->first = key; break; }
        }
        return mapPairs[index]->second;
    }

    //overloaded insertion operator
    friend std::ostream& operator<< (std::ostream& os, HashMap<K, V>& hMap) {
        for (size_t i = 0; i < hMap.capacity; ++i) {
            os << std::endl << "  #" << i << " =>" << " " << hMap.mapPairs[i].first << ":" << hMap.mapPairs[i].second;
        }
        return os;
    }


    size_t size(void) const {
        size_t hashMapSize = 0;
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            if (mapPairs[i]->first.length() > 0) {
                hashMapSize++;
            }
        }
        return hashMapSize;
    }

    //helper function to determine whether the value is present in the map
    bool isPresent(std::string key) {
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            if (mapPairs[i]->first == key) {
                return true;
            }
        }
        return false;
    }

    //useful clear function
    void clear() {
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            delete mapPairs[i];
        }
    }

    size_t max_size(void) const {
        size_t maxSize = DEFAULT_MAP_HASH_TABLE_SIZE;
        return maxSize;
    }

    size_t count(const K& key) {
        size_t numMatchingElements = 0;
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            if (mapPairs[i]->first == key) {
                ++numMatchingElements;
            }
        }
        return numMatchingElements;
    }

    //two userful helper functions to avoid using the overloaded brackets to dereference data.  This was more simple to implement
    //because I wrote the code.
    std::string getPair(std::string key) {
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            if (mapPairs[i]->first == key) {
                return stringifyData(mapPairs[i]->second);
            }
        }
        return "Error, no data exists here.";
    }
    Set<std::string> getSet(std::string key) {
        Set<std::string> emptySet;
        for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
            if (mapPairs[i]->first == key) {
                return mapPairs[i]->second;
            }
        }
        //must return something to avoid compiler warnings
        return emptySet;
    }

};


#endif //LAB_9_POKEMON_MAP_H
