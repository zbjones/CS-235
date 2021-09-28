#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include "Snap.h"
#include "Csg.h"
#include "Cdh.h"
#include "Cr.h"
using namespace std;

//useful function for handling my input
int findNextComma(string substringToEvaluate) {
    for (unsigned int i = 0; i < substringToEvaluate.size(); i++) {
        if (substringToEvaluate[i] == ',') {
            return i;
        }
    }
}

int main(int argc, char *argv[]) {

    //open filestream and create a local string inputfile vector to store input
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);
    out << "Input Strings:" << endl;
    vector<string> inputFile;
    for (string fileLine; getline(in, fileLine);)
    {
        inputFile.push_back(fileLine);
    }
    in.close();

    cout << endl << "NUM LINES IS: " << inputFile.size();

    //define some vectors for use
    vector<Snap*> snapVector;
    vector<Csg*> csgVector;
    vector<Cdh*> cdhVector;
    vector<Cr*> crVector;

    //implement all class input and setting through for block.  Also catch an exception we threw as 666, about how we feel right now.
    string fileLine;
    for (unsigned int i = 0; i < inputFile.size(); i++) {
        try {
            if ("snap(" == inputFile[i].substr(0, 5)) {
                fileLine = inputFile[i].substr(5, inputFile[i].size());
                int numNameComma = 0;
                numNameComma = findNextComma(fileLine);
                string stdIDNum;
                stdIDNum = fileLine.substr(0, numNameComma);
                fileLine = fileLine.substr((numNameComma + 1), fileLine.size());

                //GetName
                int nameAddressComma;
                nameAddressComma = findNextComma(fileLine);
                string stdName;
                stdName = fileLine.substr(0, nameAddressComma);
                fileLine = fileLine.substr((nameAddressComma + 1), fileLine.size());

                //Get Address
                int addressPhoneComma;
                addressPhoneComma = findNextComma(fileLine);
                string stdAddress;
                stdAddress = fileLine.substr(0, addressPhoneComma);
                fileLine = fileLine.substr((addressPhoneComma + 1), fileLine.size());

                //GetPhone
                string stdPhone;
                stdPhone = fileLine.substr(0, fileLine.find(')') );

                //make new object
                snapVector.push_back(new Snap(stdIDNum, stdName, stdAddress, stdPhone));
            }
            else if ("csg(" == inputFile[i].substr(0, 4)) {

                fileLine = inputFile[i].substr(4, inputFile[i].size());
                int cNameStdIDComma = 0;
                cNameStdIDComma = findNextComma(fileLine);
                string courseName;
                courseName = fileLine.substr(0, cNameStdIDComma);
                fileLine = fileLine.substr((cNameStdIDComma + 1), fileLine.size());

                int stdIDStdGradeComma = 0;
                stdIDStdGradeComma = findNextComma(fileLine);
                string stdIDString;
                stdIDString = fileLine.substr(0, stdIDStdGradeComma);
                fileLine = fileLine.substr((stdIDStdGradeComma + 1), fileLine.size());
                string studentGrade;
                studentGrade = fileLine.substr(0, fileLine.find(')'));
                csgVector.push_back(new Csg(stdIDString, studentGrade, courseName));
            }
            else if ("cdh(" == inputFile[i].substr(0, 4)) {
                fileLine = inputFile[i].substr(4, inputFile[i].size());
                int cNameDayComma = 0;
                cNameDayComma = findNextComma(fileLine);
                string courseName;
                courseName = fileLine.substr(0, cNameDayComma);
                fileLine = fileLine.substr((cNameDayComma + 1), fileLine.size());

                int courseDayTimeComma = 0;
                courseDayTimeComma = findNextComma(fileLine);
                string courseDay;
                courseDay = fileLine.substr(0, courseDayTimeComma);
                fileLine = fileLine.substr((courseDayTimeComma + 1), fileLine.size());

                string courseTime;
                courseTime = fileLine.substr(0, fileLine.find(')'));
                cdhVector.push_back(new Cdh(courseName, courseDay, courseTime));
            }
            else if ("cr(" == inputFile[i].substr(0, 3)) {
                fileLine = inputFile[i].substr(inputFile[i].find('(') + 1, inputFile[i].size());
                int cNameRoomComma = 0;
                cNameRoomComma = findNextComma(fileLine);
                string courseName;
                courseName = fileLine.substr(0, cNameRoomComma);
                fileLine = fileLine.substr((cNameRoomComma + 1), fileLine.size());

                string courseRoom;
                courseRoom = fileLine.substr(0, fileLine.find(')'));
                crVector.push_back(new Cr(courseName, courseRoom));
            }
            else {
                throw 666;
            }
        }
        catch (int e) {
            out << "**Error: ";
        }
        out << inputFile[i] << endl;
    }

    //print out the vectors using the overloaded insertion operator
    out << endl << endl << "Vectors: ";
    for (unsigned int i = 0; i < snapVector.size(); i++) {
        out << endl << *snapVector[i];
    }
    for (unsigned int i = 0; i < csgVector.size(); i++) {
        out << endl << *csgVector[i];
    }
    for (unsigned int i = 0; i < cdhVector.size(); i++) {
        out << endl << *cdhVector[i];
    }
    for (unsigned int i = 0; i < crVector.size(); i++) {
        out << endl << *crVector[i];
    }

    //print out course grades using csg/snap vector logic
    out << endl << endl << "Course Grades:";
    for (unsigned int i = 0; i < csgVector.size(); i++) {
        for (unsigned int j = 0; j < snapVector.size(); j++) {
            if (csgVector[i]->getStudentID() == snapVector[j]->getStudentID()) {
                out << endl <<  csgVector[i]->getCourseName() << "," << snapVector[j]->getStudentName() << ","
                    << csgVector[i]->getGrade();
            }
        }
    }

    //do some stuff with the cdh vector so we don't print out duplicates later
    vector<Cdh*> masterCdhVector;
    for (unsigned int i = 0; i < cdhVector.size(); i++) {
        string allDays = cdhVector[i]->getCourseDay();
        for(unsigned int j = 0; j < cdhVector.size(); j++) {
            if (cdhVector[i]->getCourseTime() == cdhVector[j]->getCourseTime() && cdhVector[i]->getCourseName() ==
                cdhVector[j]->getCourseName() && i != j) {
                allDays = allDays + cdhVector[j]->getCourseDay();
            }
        }
        bool found = false;
        for(unsigned int j = 0; j < masterCdhVector.size(); j++) {
            if (cdhVector[i]->getCourseTime() == masterCdhVector[j]->getCourseTime() && cdhVector[i]->getCourseName() ==
            masterCdhVector[j]->getCourseName()) {
                found = true;
            }
        }
        if (!found) {
            masterCdhVector.push_back(new Cdh(cdhVector[i]->getCourseName(), allDays, cdhVector[i]->getCourseTime()));
        }
    }

    //use 4 nested for loops to print out student schedules. A HUGE PAIN.
    out << endl << endl << "Student Schedules:";
    for (unsigned int i = 0; i < snapVector.size(); i++) {
        out << endl << snapVector[i]->getStudentName() << ", " << snapVector[i]->getStudentID() << ", "
            << snapVector[i]->getStudentAddress() << ", " << snapVector[i]->getStudentPhone() << endl;
        for (unsigned int j = 0; j < csgVector.size(); j++) {
            for (unsigned int k = 0; k < masterCdhVector.size(); k++) {
                for(unsigned int l = 0; l < crVector.size(); l++) {
                    if (snapVector[i]->getStudentID() == csgVector[j]->getStudentID() &&
                        csgVector[j]->getCourseName() == masterCdhVector[k]->getCourseName()
                        && crVector[l]->getCourseName() == csgVector[j]->getCourseName()) {
                        out << "  " << csgVector[j]->getCourseName() << " " << masterCdhVector[k]->getCourseDay()
                        << " " << masterCdhVector[k]->getCourseTime() << ", " << crVector[l]->getCourseRoom() << endl;
                    }
                }
            }
        }
    }

    //deallocate all memory
    for (unsigned int i = 0; i < snapVector.size(); i++) {
        delete snapVector[i];
    }
    for (unsigned int i = 0; i < csgVector.size(); i++) {
        delete csgVector[i];
    }
    for (unsigned int i = 0; i < cdhVector.size(); i++) {
        delete cdhVector[i];
    }
    for (unsigned int i = 0; i < crVector.size(); i++) {
        delete crVector[i];
    }
    for (unsigned int i = 0; i < masterCdhVector.size(); i++) {
        delete masterCdhVector[i];
    }

    return 0;
}