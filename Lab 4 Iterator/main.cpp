#include <iostream>
#include <fstream>

#include "LinkedList.h"
#include "LinkedListInterface.h"
using namespace std;


int main(int argc, char *argv[]) {
//Open File Stream
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

//Create Linked List object
    LinkedList<string> myLinkedList;
    LinkedList<string>::Iterator iter = myLinkedList.begin(); // THIS EQUALS NULL AT START

    for (string inputLine; getline(in, inputLine, '\n');) {
        string inputCommand, inputText;
        if (inputLine.size() == 0) continue;
        istringstream iss(inputLine);
        iss >> inputCommand;
        if (!inputLine.empty() && inputLine[inputLine.size() - 1] == '\r') {
            inputLine.erase(inputLine.size() - 1);
        }
        out << inputLine;
        //handle input commands
        if (inputCommand == "Insert") {
            while (iss >> inputText) {
                myLinkedList.push_front(inputText);
            }
        } else if (inputCommand == "PrintList") {
            if (!myLinkedList.empty()) {
                out << myLinkedList;
            }
        } else if (inputCommand == "Size") {
            out << " " << myLinkedList.size();
        } else if (inputCommand == "Clear") {
            out << " OK";
            myLinkedList.clear();
        } else if (inputCommand == "Iterate") {
            if (!myLinkedList.empty()) {
                iter = myLinkedList.begin();
                while (iter != myLinkedList.end()) {
                    out << endl << " [" << *iter << "] ";
                    iter = ++iter;
                }
            }
            else {
                out << " Empty!";
            }
        } else if (inputCommand == "Find") {
            while (iss >> inputText) {}
            LinkedList<string>::Iterator foundIter = myLinkedList.find(myLinkedList.begin(), myLinkedList.end(), inputText);
            if (foundIter != NULL) {
                out << " OK";
            }
            else {
                out << " Not Found";
            }
        } else if (inputCommand == "InsertAfter") {
            string inputPos;
            string inputVal;
            iss >> inputVal;
            iss >> inputPos;
            LinkedList<string>::Iterator foundIter = myLinkedList.find(myLinkedList.begin(), myLinkedList.end(), inputPos);
            if (foundIter != NULL) {
                out << " OK";
                myLinkedList.insertAfter(foundIter, inputVal);
            }
            else {
                out << " Not Found";
            }
        } else if (inputCommand == "InsertBefore") {
            string inputPos;
            string inputVal;
            iss >> inputVal;
            iss >> inputPos;
            LinkedList<string>::Iterator foundIter = myLinkedList.find(myLinkedList.begin(), myLinkedList.end(), inputPos);
            if (foundIter != NULL) {
                out << " OK";
                myLinkedList.insertBefore(foundIter, inputVal);
            }
            else {
                out << " Not Found";
            }
        } else if (inputCommand == "Erase") {
            string inputPos;
            iss >> inputPos;
            LinkedList<string>::Iterator foundIter = myLinkedList.find(myLinkedList.begin(), myLinkedList.end(), inputPos);
            if (foundIter != NULL) {
                out << " OK";
                myLinkedList.erase(foundIter);
            }
            else {
                out << " Not Found";
            }
        } else if (inputCommand == "Replace") {
            string inputPos;
            string inputVal;
            iss >> inputPos;
            iss >> inputVal;
            LinkedList<string>::Iterator foundIter = myLinkedList.find(myLinkedList.begin(), myLinkedList.end(), inputPos);
            if (foundIter != NULL && !myLinkedList.empty()) {
                out << " OK";
                myLinkedList.replace(myLinkedList.begin(), myLinkedList.end(), inputPos, inputVal);
            }
            else {
                out << " Empty!";
            }
        }
        out << endl;
    }


//close files and free memory
    in.close();
    out.close();
    myLinkedList.clear();
    return 0;
}

