//
// Created by Zachary Jones on 1/30/2020.
//

#ifndef LAB_2_SNAP_STUDENT_H
#define LAB_2_SNAP_STUDENT_H
#include <string>

class Student {
public:
    Student(std::string stdID) {
        this->studentID = stdID;
    };
    virtual std::string toString() const = 0;
protected:
    std::string studentID;
};


#endif //LAB_2_SNAP_STUDENT_H
