//
// Created by Zachary Jones on 1/30/2020.
//

#ifndef LAB_2_SNAP_SNAP_H
#define LAB_2_SNAP_SNAP_H

#include <string>
#include "Student.h"


class Snap : Student {
public:
    Snap(std::string stdID, std::string stdName, std::string stdAddress, std::string stdPhone) : Student(stdID){
        studentID = stdID;
        studentName = stdName;
        studentAddress = stdAddress;
        studentPhone = stdPhone;
    };
    std::string toString() const {
        return "snap(" + studentID + "," + studentName + "," + studentAddress + "," + studentPhone + ")";
    };
    friend std::ostream& operator<< (std::ostream& os, const Snap& snap) {
        os << snap.toString();
        return os;
    }
    std::string getStudentID() {
        return studentID;
    };
    std::string getStudentName() {
        return studentName;
    };
    std::string getStudentAddress() {
        return studentAddress;
    };
    std::string getStudentPhone() {
        return studentPhone;
    };
private:
    std::string studentName;
    std::string studentAddress;
    std::string studentPhone;
};


#endif //LAB_2_SNAP_SNAP_H
