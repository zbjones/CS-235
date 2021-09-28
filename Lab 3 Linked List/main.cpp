#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"

using namespace std;

int main(int argc, char *argv[]) {
//Open File Stream
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

//Create Linked List object
    LinkedList<string> myLinkedList;

for (string inputLine; getline(in, inputLine, '\n');) {
    string inputCommand, inputText;
    if (inputLine.size() == 0) continue;
    istringstream iss(inputLine);
    iss >> inputCommand;
    if (!inputLine.empty() && inputLine[inputLine.size() - 1] == '\r') {
        inputLine.erase(inputLine.size() - 1);
    }
    out  << inputLine;
    //handle input commands
    try {
        if (inputCommand == "Insert") {
            while (iss >> inputText) {
                myLinkedList.push_front(inputText);
            }
        } else if (inputCommand == "PrintList") {
            if (!myLinkedList.empty()) {
                out << myLinkedList;
            } else {
                throw 666;
            }
        } else if (inputCommand == "Empty") {
            bool empty = myLinkedList.empty();
            if (empty) {
                out << " true";
            } else {
                out << " false";
            }
        } else if (inputCommand == "Size") {
            out << " " << myLinkedList.size();
        } else if (inputCommand == "Clear") {
            out << " OK";
            myLinkedList.clear();
        } else if (inputCommand == "Remove") {
            while (iss >> inputText) {
                myLinkedList.remove(inputText);
            }
        } else if (inputCommand == "Delete") {
            if (!myLinkedList.empty()) {
                out << " OK";
                myLinkedList.pop_front();
            } else {
                throw 666;
            }
        } else if (inputCommand == "First") {
            if (!myLinkedList.empty()) {
                out << " " << myLinkedList.front();
            } else {
                throw 666;
            }
        }
        else if (inputCommand == "Reverse") {
            if (!myLinkedList.empty()) {
                out << " OK";
                myLinkedList.reverse();
            } else {
                throw 666;
            }
        }
    }
    catch (int e) {
        out << " Empty!";
    }
    out << endl;
}

//close files and free memory
    in.close();
    out.close();
    myLinkedList.clear();
    return 0;
}

