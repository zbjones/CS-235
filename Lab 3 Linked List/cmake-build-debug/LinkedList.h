//
// Created by Zachary Jones on 2/6/2020.
//
#ifndef LAB_3_LINKED_LIST_LINKEDLIST_H
#define LAB_3_LINKED_LIST_LINKEDLIST_H

#include <string>
#include "LinkedListInterface.h"
#include <sstream>

template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    struct Node {
        std::string nodeData;
        Node *nextNode;
        Node(const T& nodeString) : nodeData(nodeString), nextNode(NULL) {}
    };
    Node* head;
    size_t linkedListSize;
public:
    LinkedList() : head(NULL), linkedListSize(0) {}
    virtual ~LinkedList() {}
    void push_front(const T& dataToInsert) {
        if (head == NULL) {
            head = new Node(dataToInsert);
            ++linkedListSize;
            return;
        }
        Node* tempPtr = head;
        head = new Node(dataToInsert);
        head->nextNode = tempPtr;
        ++linkedListSize;
    }
    std::string toString() const {
        std::ostringstream os;
        Node* tempPtr = head;
        while (tempPtr != NULL) {
            os << " " << tempPtr->nodeData;
            tempPtr = tempPtr->nextNode;
        }
        return os.str();
    }
    size_t size() const {
        return linkedListSize;
    }
    bool empty() const {
        bool isEmpty = false;
        if (linkedListSize == 0) {
            isEmpty = true;
        }
        return isEmpty;
    }
    void remove(T& value) {
        Node *currentNode = head;
        Node *nodeToDelete = nullptr;
        while (head != NULL && head->nodeData == value) {
            Node *tempHead = head;
            head = head->nextNode;
            delete tempHead;
            --linkedListSize;
            currentNode = head;
        }
        while (currentNode != NULL && currentNode->nextNode != NULL) {
            if (currentNode->nextNode->nodeData == value) {
                if (currentNode->nextNode->nextNode == NULL) {
                    Node *secondLastNode = currentNode;
                    delete secondLastNode->nextNode;
                    currentNode->nextNode = nullptr;
                    --linkedListSize;
                    return;
                }
                else {
                    nodeToDelete = currentNode->nextNode;
                    currentNode->nextNode = nodeToDelete->nextNode;
                    delete nodeToDelete;
                    --linkedListSize;
                }
            }
            currentNode = currentNode->nextNode;
        }
    }
    void clear()  {
        while (head != NULL) {
            pop_front();
        }
        linkedListSize = 0;
    }
    void pop_front() {
        if (head != NULL) {
            Node *tempHead = head;
            head = head->nextNode;
            delete tempHead;
            tempHead = nullptr;
            --linkedListSize;
        }
    }
    T& front()  {
        return head->nodeData;
    }
    void reverse()  {
        LinkedList<T> *reversedLinkedList = new LinkedList();
        Node *currentNode = head;
        while (currentNode != NULL) {
            reversedLinkedList->push_front(currentNode->nodeData);
            currentNode = currentNode->nextNode;
        }
        clear();
        head = reversedLinkedList->head;
        linkedListSize = reversedLinkedList->linkedListSize;
        delete reversedLinkedList;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& linkedList)
    {
        return os << linkedList.toString();
    }
};



#endif //LAB_3_LINKED_LIST_LINKEDLIST_H

