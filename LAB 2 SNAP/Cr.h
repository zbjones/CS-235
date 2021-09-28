//
// Created by Zachary Jones on 1/30/2020.
//

#ifndef LAB_2_SNAP_CR_H
#define LAB_2_SNAP_CR_H


#include <string>
#include "Course.h"

class Cr : Course {
public:
    Cr(std::string courseName, std::string courseRoom) : Course(courseName) {
        this->courseRoom = courseRoom;
    }
    std::string toString() const {
        return "cr(" + course + "," + courseRoom + ")";
    }
    std::string getCourseName() {
        return course;
    }
    std::string getCourseRoom() {
        return courseRoom;
    }
    friend std::ostream& operator<< (std::ostream& os, const Cr& cr) {
        os << cr.toString();
        return os;
    }
private:
    std::string courseRoom;

};


#endif //LAB_2_SNAP_CR_H
