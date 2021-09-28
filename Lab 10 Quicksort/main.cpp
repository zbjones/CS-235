#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Quicksort.h"
using namespace std;


int main(int argc, char* argv[]) {
    //open filestream and read input file
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

    //initialize quicksort object
    Quicksort<int> myQuickSortArray;

    for (string inputLine; getline(in, inputLine, '\n');) {
        string userCommand, inputText;
        if (inputLine.size() == 0) continue;
        //get rid of carriage return if its present to help with formatting
        if (!inputLine.empty() && inputLine[inputLine.size() - 1] == '\r') {
            inputLine.erase(inputLine.size() - 1);
        }
        istringstream iss(inputLine);
        string inputCommand = "";
        iss >> inputCommand;

        if (inputCommand == "QuickSort") {
            string capacity = "";
            iss >> capacity;
            myQuickSortArray.createArray(stoi(capacity));
            out << inputLine << " OK" << endl;
        }
        if (inputCommand == "Clear") {
            myQuickSortArray.clear();
            out << inputLine << " OK" << endl;
        }
        if (inputCommand == "Capacity") {
            out << inputLine << " " << myQuickSortArray.capacity() << endl;
        }
        if (inputCommand == "AddToArray") {
            string arrayMember = "";
            out << inputCommand << "  ";
            string noCommaFirst = "";
            while (iss >> arrayMember) {
                myQuickSortArray.addElement(stoi(arrayMember));
                out << noCommaFirst << arrayMember;
                noCommaFirst = ",";
            }
             out <<  " OK" << endl;
        }
        if (inputCommand == "Size") {
            out << inputLine << " " << myQuickSortArray.size() << endl;
        }
        if (inputCommand == "PrintArray") {
            out << inputLine << " " << myQuickSortArray.toString() << endl;
        }
        if (inputCommand == "MedianOfThree") {
            string leftIndex, rightIndex;
            iss >> leftIndex;
            iss >> rightIndex;
            out << inputCommand << " " << leftIndex << "," << rightIndex << " = ";
            out << myQuickSortArray.medianOfThree(stoi(leftIndex), stoi(rightIndex) - 1) << endl;
        }
        if (inputCommand == "Partition") {
            string left, right, index;
            iss >> left;
            iss >> right;
            iss >> index;
            out << inputCommand << " " << left << "," << right << "," << index << " = ";
            out << myQuickSortArray.partition(stoi(left), stoi(right), stoi(index)) << endl;
        }
        if (inputCommand == "SortAll") {
            myQuickSortArray.sortAll();
            out << inputLine << " OK" << endl;
        }
        if (inputCommand == "Sort") {
            string index1, index2;
            iss >> index1;
            iss >> index2;
            myQuickSortArray.sort(stoi(index1), stoi(index2) - 1);
            out << inputCommand << " " << index1 << "," << index2 << " OK" << endl;
        }
    }

    out.close();
    in.close();
    return 0;
}
