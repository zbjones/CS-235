//
// Created by Zachary Jones on 1/30/2020.
//

#ifndef LAB_2_SNAP_CSG_H
#define LAB_2_SNAP_CSG_H
#include <string>
#include "Student.h"
#include "Course.h"

class Csg : Student, Course {
public:
    Csg(std::string stdID, std::string grade, std::string course) : Course(course), Student(stdID) {
        this->grade = grade;
    };
    friend std::ostream& operator<< (std::ostream& os, const Csg& csg) {
        os << csg.toString();
        return os;
    }
    std::string toString() const {
        return "csg(" + course + "," + studentID + "," + grade + ")";
    }
    std::string getCourseName() {
        return course;
    }
    std::string getGrade() {
        return grade;
    }
    std::string getStudentID() {
        return studentID;
    }
private:
    std::string grade;
};


#endif //LAB_2_SNAP_CSG_H
