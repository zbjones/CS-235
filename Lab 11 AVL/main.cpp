#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "AVL.h"

using namespace std;

int main(int argc, char* argv[]) {
    //open files
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

    //declare int and string BST trees
    AVL<int> myIntTree;
    AVL<string> myStringTree;
    string dataType = "";

    for (string line; getline(in, line);) {
        string command, data;
        if (line.size() == 0) continue;
        istringstream iss(line);
        iss >> command;
        iss >> data;

        //remove the newline character if present for clarity and easier processing
        if (!command.empty() && command[command.size() - 1] == '\r') {
            command.erase(command.size() - 1);
        }
        if (!data.empty() && data[data.size() - 1] == '\r') {
            data.erase(data.size() - 1);
        }

        //handle two different datatypes
        if (command == "INT") {
            dataType = "INT";
            out << "INT" << " " << "true" << endl;
        }
        if (command == "STRING") {
            dataType = "STRING";
            out << "STRING" << " " << "true" << endl;
        }
        //add function
        if (command == "add") {
            if (dataType == "STRING") {
                bool success;
                success = myStringTree.addNode(data);
                out << command << " " << data << " ";
                if (success) {
                    out << "true" << endl;
                } else {
                    out << "false" << endl;
                }
            } else if (dataType == "INT") {
                bool success;
                int intData = stoi(data);
                success = myIntTree.addNode(intData);
                out << command << " " << data << " ";
                if (success) {
                    out << "true" << endl;
                } else {
                    out << "false" << endl;
                }
            }
        }
        //print function calls toString method
        if (command == "print") {
            if (dataType == "STRING") {
                out << command << ":" << myStringTree.toString() << endl;
            } else if (dataType == "INT") {
                out << command << ":" << myIntTree.toString() << endl;
            }
        }
        if (command == "size") {
            if (dataType == "STRING") {
                out << command << " " << myStringTree.size() << endl;
            } else if (dataType == "INT") {
                out << command << " " << myIntTree.size() << endl;
            }
        }
        if (command == "remove") {
            bool success = true;
            if (dataType == "STRING") {
                success = myStringTree.removeNode(data);
                out << command << " " << data << " ";
            } else if (dataType == "INT") {
                int valueToRemove = stoi(data);
                success = myIntTree.removeNode(valueToRemove);
                out << command << " " << data << " ";
            }
            out << ((success) ? "true" : "false") << endl;
        }
        if (command == "clear") {
            if (dataType == "STRING") {
                myStringTree.clearTree();
                out << command << " " << "true" << endl;
            } else if (dataType == "INT") {
                myIntTree.clearTree();
                out << command << " " << "true" << endl;
            }
        }
        if (command == "find") {
            bool success = true;
            if (dataType == "STRING") {
                success = myStringTree.findNode(data);
                out << command << " " << data << " ";
            } else if (dataType == "INT") {
                int intData = stoi(data);
                success = myIntTree.findNode(intData);
                out << command << " " << data << " ";
            }
            out << ((success) ? "found" : "not found") << endl;
        }


    }

    //close files, destructor handles deletion
    in.close();
    out.close();
    return 0;
}
