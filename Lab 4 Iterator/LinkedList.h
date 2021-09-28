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

    //NOTE: FROM HERE TO LINE 128 is code from LAB 3.  It is used only minimally.  I call the constructors, destructors,
    // and empty, in addition to using the struct Node, but it can largely be ignored.

    // **** SKIP TO LINE 129 FOR LAB 4 CODE!!!! ****//
    //I left the templated class structure intact, as I built directly on top of lab 3, although it is technically not needed for this lab.
    //BECAUSE IT IS A TEMPLATED CLASS, NO METHODS CAN BE IMPLEMENTED IN A .CPP FILE EVEN IF THEY ARE OVER 10 LINES
    //THEY MUST REMAIN IN A .H FILE.
    // "Due to the nature of template classes (which are templates and not objects), you must implement the entire class
    // in your '.h' file. (Any class method with more than 10 lines of code is also included in the '.h' file and not a separate '.cpp' file."

private:
    struct Node {
        std::string nodeData;
        Node *nextNode;
        Node(const T& nodeString, Node *nextNode = NULL) : nodeData(nodeString), nextNode(nextNode) {}
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

    class Iterator
    {
    private:
        Node* itNode;
    public:
        Iterator(Node* head) : itNode(head) {}
        ~Iterator() {};

        //overload the necessary operators
        bool operator!=(const Iterator& rhs) const {
            return itNode != rhs.itNode;
        }
        Iterator& operator++() {
            itNode = itNode->nextNode;
            return *this;
        }
        T& operator*() const { return itNode->nodeData; }
        Node* getItNode() {
            return itNode;
        }
    };
    //Iterator begin and end functions
    Iterator begin(void) { return LinkedList<T>::Iterator(head); }
    Iterator end(void) { return LinkedList<T>::Iterator(NULL); }

    Iterator find(Iterator begin, Iterator end, T& value) const {
        Iterator iter = begin;
        while (iter != end) {
            if (*iter == value) {
                return iter;
            }
            ++iter;
        }
        return NULL;
    }
    Iterator insertAfter(Iterator posIter, const T& value) {
        Node *insertedNode = new Node(value, posIter.getItNode()->nextNode);
        posIter.getItNode()->nextNode = insertedNode;
        ++posIter;
        ++linkedListSize;
        return posIter;
    }
    Iterator insertBefore(Iterator posIter, const T& value) {
        //First check if isHead
        if (posIter.getItNode() == begin().getItNode()) {
            Node *tempPtr = head;
            head = new Node(value);
            head->nextNode = tempPtr;
            Iterator headIter = Iterator(head);
            ++linkedListSize;
            return headIter;
        }
        //If not head
        else {
            Iterator startIter = begin();
            while(startIter.getItNode() != NULL) {
                if (startIter.getItNode()->nextNode->nodeData == posIter.getItNode()->nodeData) {
                    break;
                }
                ++startIter;
            }
            Node *insertedNode = new Node(value, posIter.getItNode());
            startIter.getItNode()->nextNode = insertedNode;
            Iterator toReturnIter = Iterator(startIter.getItNode());
            ++linkedListSize;
            return toReturnIter;
        }
    }
    Iterator erase(Iterator position) {
        //head case
        if (position.getItNode() == begin().getItNode()) {
            head = position.getItNode()->nextNode;
            delete position.getItNode();
            --linkedListSize;
            return begin();
        }
        //tail case
        else if (position.getItNode()->nextNode == NULL) {
            //Get second to last position
            Iterator startIter = begin();
            Iterator secondLastIter = NULL;
            while (startIter != end()) {
                if (startIter.getItNode()->nextNode->nextNode == NULL) {
                    secondLastIter = startIter;
                    break;
                }
                ++startIter;
            }
            secondLastIter.getItNode()->nextNode = NULL;
            delete position.getItNode();
            --linkedListSize;
            return secondLastIter;
        }
        //middle case
        else {
            Iterator startIter = begin();
            while (startIter != end()) {
                if (startIter.getItNode()->nextNode->nextNode == position.getItNode()->nextNode) {
                    break;
                }
                ++startIter;
            }
            Iterator iterToReturn = Iterator(position.getItNode()->nextNode);
            startIter.getItNode()->nextNode = position.getItNode()->nextNode;
            delete position.getItNode();
            --linkedListSize;
            return iterToReturn;
        }
    }
    void replace(Iterator begin, Iterator end, T& posToReplace, const T& value) {
        Iterator startIter = find(begin, end, posToReplace);
        while (startIter != NULL && startIter.getItNode()->nodeData == posToReplace) {
            startIter.getItNode()->nodeData = value;
            ++startIter;
        }
    }
};



#endif //LAB_3_LINKED_LIST_LINKEDLIST_H

