//
// Created by Zachary Jones on 1/30/2020.
//

#ifndef LAB_2_SNAP_CDH_H
#define LAB_2_SNAP_CDH_H
#include <string>
#include "Course.h"

class Cdh : Course {
public:
    Cdh(std::string courseID, std::string courseDay, std::string courseTime) : Course(courseID) {
            this->courseDay = courseDay;
            this->courseTime = courseTime;
    }
    std::string toString() const {
        return "cdh(" + course + "," + courseDay + "," + courseTime + ")";
    }
    std::string getCourseName() {
        return course;
    }
    std::string getCourseDay() {
        return courseDay;
    }
    std::string getCourseTime() {
        return courseTime;
    }
    friend std::ostream& operator<< (std::ostream& os, const Cdh& cdh) {
        os << cdh.toString();
        return os;
    }
private:
    std::string courseDay;
    std::string courseTime;
};


#endif //LAB_2_SNAP_CDH_H
