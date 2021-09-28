#include <fstream>
#include <ostream>

#include "Expression.h"

using namespace std;

int main(int argc, char *argv[]) {

    //Open File Stream
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

    Expression myExpression;

    //handle input commands
    for (string inputLine; getline(in, inputLine, '\n');) {
        string userCommand, inputText;
        if (inputLine.size() == 0) continue;
        istringstream iss(inputLine);
        iss >> userCommand;

        if (!inputLine.empty() && inputLine[inputLine.size() - 1] == '\r') {
            inputLine.erase(inputLine.size() - 1);
        }
        inputLine = inputLine.substr(userCommand.size(), inputLine.size());

        if (userCommand == "Expression:") {
            out << userCommand << inputLine;
            myExpression.setInputString(inputLine);
        }
        else if (userCommand == "Infix:") {
            out << userCommand << myExpression.infix();
        }
        else if (userCommand == "Postfix:") {
            out << userCommand << " " << myExpression.postfix();
        }
        else if (userCommand == "Value:") {
            out << userCommand << " " << myExpression.value() << endl;
        }
        else if (userCommand == "Prefix:") {
            out << userCommand << myExpression.prefix();
        }
        out << endl;
    }

    //close file streams
    in.close();
    out.close();
    return 0;
}
