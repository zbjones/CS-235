#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#include "Deque.h"
#include "Station.h"
#include "Vector.h"
#include "Queue.h"

using namespace std;

int main(int argc, const char * argv[]) {
    //Open File Stream
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

    Station<unsigned int> myStation;

    //handle input commands
    for (string inputLine; getline(in, inputLine, '\n');) {
        string userCommand, inputText;
        if (inputLine.size() == 0) continue;
        istringstream iss(inputLine);
        iss >> userCommand;
        if (!inputLine.empty() && inputLine[inputLine.size() - 1] == '\r') {
            inputLine.erase(inputLine.size() - 1);
        }
        try {
            if (userCommand == "Add:station") {
                iss >> inputText;
                out << inputLine;
                myStation.addCar(stoul(inputText));
                out << " OK";
            }
            else if (userCommand == "Add:stack") {
                out << inputLine << " " << myStation.addStack();
            }
            else if (userCommand == "Add:queue") {
                out << inputLine << " " << myStation.addQueue();
            }
            else if (userCommand == "Remove:station") {
                out << inputLine;
                myStation.removeCar();
                out << " OK";
            }
            else if (userCommand == "Remove:queue") {
                out << inputLine << " " << myStation.removeQueue();
            }
            else if (userCommand == "Remove:stack") {
                out << inputLine << " " << myStation.removeStack();
            }
            else if (userCommand == "Train:") {
                out << inputLine << " " << myStation.toString();
            }
            else if (userCommand == "Top:station") {
                out << inputLine << " " << myStation.topStation();
            }
            else if (userCommand == "Top:queue") {
                out << inputLine << " " << myStation.topQueue();
            }
            else if (userCommand == "Top:stack") {
                out << inputLine << " " << myStation.topStack();
            }
            else if (userCommand == "Size:queue") {
                out << inputLine << " " << to_string(myStation.sizeQueue());
            }
            else if (userCommand == "Size:stack") {
                out << inputLine << " " << to_string(myStation.sizeStack());
            }


        }
        catch (int e) {
            if (e == 999) {
                out << " Turntable empty!";
            }
            if (e == 998) {
                out << " Turntable Occupied!";
            }
            if (e == 996) {
                out << " Queue empty!";
            }
            if (e == 997) {
                out << " Stack empty!";
            }
        }
        out << endl;
    }





//    Queue<int> myDeque;
//
//
//    myDeque.push(666);
//    myDeque.push(667);
//    myDeque.push(668);
//    myDeque.push(669);
//    myDeque.push(670);
//    myDeque.push(671);
//    myDeque.push(672);
//    myDeque.push(673);
//
//    myDeque.pop();
//
//    cout << myDeque.toString();



    return 0;
}

