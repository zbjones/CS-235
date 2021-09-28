//
// Created by Zachary Jones on 1/30/2020.
//

#ifndef LAB_2_SNAP_COURSE_H
#define LAB_2_SNAP_COURSE_H
#include <string>

class Course {
public:
    Course(const std::string &course) : course(course) {
        this->course = course;
    };
    virtual std::string toString() const = 0;
protected:
    std::string course;
};


#endif //LAB_2_SNAP_COURSE_H
