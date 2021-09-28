//
// Created by Zachary Jones on 2/18/2020.
//

#include "Expression.h"
#include <string>


//outputs the infix expression and does error checking
std::string Expression::infix() {std::string lineToReturn;
    std::stack<char> paranthStack;
    std::vector<string> inputLineVector = loadInputLineVector(inputLine);

    try {
        for (unsigned int i = 0; i < inputLineVector.size(); i++) {
            string currentString = inputLineVector.at(i);
            if (currentString.at(0) == '[' || currentString.at(0) == '{' || currentString.at(0) == '(') { ;
                paranthStack.push(currentString.at(0));
            } else if (currentString.at(0) == ']' || currentString.at(0) == '}' || currentString.at(0) == ')') {
                if (!paranthStack.empty() && ((currentString.at(0) - 1) == paranthStack.top() ||
                                              (currentString.at(0) - 2) == paranthStack.top())) {
                    if (!paranthStack.empty()) {
                        paranthStack.pop();
                    }
                }
            }
        }
        if (!paranthStack.empty()) {
            throw 666; // unbalanced error
        }
        for (unsigned int i = 0; i < inputLineVector.size() - 1; i++) {
            if (isOperator(inputLineVector.at(i))) {
                if (i == 0) {
                    throw 668; //missing operand (first character is an operator case)
                }
                if (isOperator(inputLineVector.at(i + 1))) {
                    throw 668; //Missing Operand error
                }
            } else if (isdigit(inputLineVector.at(i).at(0))) {
                if (isdigit(inputLineVector.at(i + 1).at(0))) {
                    throw 669; //missing operator
                }
            } else if (!isOperator(inputLineVector.at(i)) && !isdigit(inputLineVector.at(i).at(0)) && !isParantheses(inputLineVector.at(i))) {
                throw 667; //illegal operator
            }
        }
        if (isOperator(inputLineVector.at(inputLineVector.size() - 1))) {
            throw 668; //Check for sneaky last character missing operand
        }
    }
    catch (int e) {
        if (e == 666) {
            return " Unbalanced";
        }
        if (e == 667) {
            return " Illegal Operator";
        }
        if (e == 668) {
            return " Missing Operand";
        }
        if (e == 669) {
            return " Missing Operator";
        }
    }
    return inputLine;
}

//Apply the postfix logic and output a postfix expression
std::string Expression::postfix() {
    std::vector<string> inputLineVector = loadInputLineVector(inputLine);
    std::stack<string> operatorStack;
    std::string strToReturn;

    for (unsigned int i = 0; i < inputLineVector.size(); i++) {
        string currentString = inputLineVector.at(i);
        int currentPriority = getPriority(currentString);
        if (currentPriority == 500) {
            strToReturn.append(currentString + " ");
        }
        else if (currentPriority == 0) {
            operatorStack.push(currentString);
        }
        else if (currentPriority == 1) {
            if (operatorStack.empty()) {
                operatorStack.push(currentString);
            }
            else if (getPriority(operatorStack.top()) == 0) {
                operatorStack.push(currentString);
            }
            else {
                while(!operatorStack.empty() && currentPriority <= getPriority(operatorStack.top())) {
                    strToReturn.append(operatorStack.top() + " ");
                    operatorStack.pop();
                }
                operatorStack.push(currentString);
            }
        }
        else if (currentPriority == 2) {
            if (operatorStack.empty()) {
                operatorStack.push(currentString);
            } else if (currentPriority > getPriority(operatorStack.top())) {
                operatorStack.push(currentString);
            } else if (currentPriority == getPriority(operatorStack.top()) ||
                       currentPriority < getPriority(operatorStack.top())) {
                strToReturn.append(operatorStack.top() + " ");
                operatorStack.pop();
                while (!operatorStack.empty() && currentPriority <= getPriority(operatorStack.top())) {
                    strToReturn.append(operatorStack.top() + " ");
                    operatorStack.pop();
                }
                operatorStack.push(currentString);
            }
        }
        else if (currentPriority == 3) {
            if (currentString == "}") {
                while (operatorStack.top() != "{") {
                    strToReturn.append(operatorStack.top() + " ");
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
            if (currentString == ")") {
                while (operatorStack.top() != "(") {
                    strToReturn.append(operatorStack.top() + " ");
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
            if (currentString == "]") {
                while (operatorStack.top() != "[") {
                    strToReturn.append(operatorStack.top() + " ");
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
        }
    }
    while (!operatorStack.empty()) {
        strToReturn.append(operatorStack.top() + " ");
        operatorStack.pop();
    }
    return strToReturn;
}

//Compute the value using an operator stack and postfix methods
int Expression::value() {
    //get a postfix vector of values
    std::string postfixExpression = postfix();
    std::vector<string> postFixVector = loadInputLineVector(postfixExpression);

    //create an intStack and a result
    std::stack<int> intStack;
    int result;

    for (unsigned int i = 0; i < postFixVector.size(); i++) {
        std::string currentString = postFixVector.at(i);
        if (isdigit(currentString.at(0))) {
            intStack.push(stoi(currentString));
        }
        if (isOperator(currentString)) {
            int stackTop;
            int stackBot;
            if (intStack.size() >= 2) {
                stackTop = intStack.top();
                intStack.pop();
                stackBot = intStack.top();
                intStack.pop();
                if (currentString == "+") { result = stackBot + stackTop; }
                if (currentString == "-") { result = stackBot - stackTop; }
                if (currentString == "*") { result = stackBot * stackTop; }
                if (currentString == "/") { result = stackBot / stackTop; }
                if (currentString == "%") { result = stackBot % stackTop; }
            }
            intStack.push(result);
        }
    }
    return intStack.top();
}

//implement prefix
std::string Expression::prefix() {
    std::string postfixExpression = postfix();
    std::vector<string> postFixVector = loadInputLineVector(postfixExpression);

    std::stack<std::string> operandStack;

    int length = postFixVector.size();

    for (unsigned int i = 0; i < length; i++) {
        if (isOperator(postFixVector[i])) {
            std::string operandOne = operandStack.top();
            operandStack.pop();
            std::string operandTwo = operandStack.top();
            operandStack.pop();
            std::string strToPush = postFixVector[i] + " " + operandTwo + " " + operandOne;
            operandStack.push(strToPush);
        }
        else {
            operandStack.push(postFixVector[i]);
        }
    }
    return " " + operandStack.top();
}
