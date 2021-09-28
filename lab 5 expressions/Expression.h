//
// Created by Zachary Jones on 2/17/2020.
//


#ifndef LAB_5_EXPRESSIONS_EXPRESSION_H
#define LAB_5_EXPRESSIONS_EXPRESSION_H

#include "ExpressionManagerInterface.h"
#include <string>
#include <vector>
#include <stack>
#include <sstream>

class Expression : ExpressionManagerInterface {

public:
    //constructors, destructors, toStrings
    Expression(std::string inputLine = "") { inputLine = this->inputLine; };
    ~Expression() { return; }
    void setInputString(std::string input) { inputLine = input; };

    std::string toString() const { return "NULL"; };
    std::string prefix();
    std::string infix();
    std::string postfix();
    int value();

    //Helper function to assign postfix properly
    int getPriority(std::string argumentString) {
        if (isOperator(argumentString) || isParantheses(argumentString)) {
            if(argumentString == "[" || argumentString == "(" || argumentString == "{") { return 0; }
            if(argumentString == "]" || argumentString == ")" || argumentString == "}") { return 3; }
            if(argumentString == "*" || argumentString == "/" || argumentString == "%") { return 2; }
            if(argumentString == "+" || argumentString == "-") { return 1; }
        }
        return 500; //this means an int
    }

    //Using a vector to simplify the syntax involved with reading in the input lines
    std::vector<string> loadInputLineVector(const std::string inputLine) {
        std::vector<string> inputLineVector;
        std::istringstream iss(inputLine);
        std::string currentString;
        while (iss >> currentString ) {
            inputLineVector.push_back(currentString);
        }
        return inputLineVector;
    }

    //Checks to see if a given character is a legal operator
    bool isOperator(const std::string userOperator) {
        bool isOperator = false;
        if (userOperator == "+" || userOperator == "-" || userOperator == "*" || userOperator == "/" || userOperator == "%") {
            isOperator = true;
        }
        return isOperator;
    }

    //checks to see if the given character is a legal parentheses.
    bool isParantheses(const std::string& userParantheses) {
        bool isParantheses = false;
        if (userParantheses == "[" || userParantheses == "]" || userParantheses == "(" || userParantheses == ")" ||
        userParantheses == "{"  || userParantheses == "}")  {
            isParantheses = true;
        }
        return isParantheses;
    }

private:
    std::string inputLine;

};

#endif //LAB_5_EXPRESSIONS_EXPRESSION_H
