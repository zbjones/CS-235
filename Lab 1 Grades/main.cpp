#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

char returnGrade(const double examScore, const double examAverage) {
    if (examScore <= (examAverage - 15)) {
        return 'E';
    } else if (examScore >= (examAverage + 15)) {
        return 'A';
    } else if (examScore < (examAverage + 15) && examScore > (examAverage + 5)) {
        return 'B';
    } else if (examScore > (examAverage - 15) && examScore < (examAverage - 5)) {
        return 'D';
    } else if (examScore <= (examAverage + 5) && examScore >= (examAverage - 5)) {
        return 'C';
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {

    // Open up a filestream to the input file and assign number of students and exams
    ifstream in(argv[1]);
    int NUM_STUDENTS = 0;
    int NUM_EXAMS = 0;
    in >> NUM_STUDENTS >> NUM_EXAMS;

    //Create a 1D Dynamic array to store students names
    string *allStudents = new string[NUM_STUDENTS];

    //Create a 2D dynamic array to store exam scores
    int **examScores = new int *[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        examScores[i] = new int[NUM_EXAMS];
    }

    //read the text file
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        string studentFirstName = "";
        string studentLastName = "";
        in >> studentFirstName >> studentLastName;
        for (int j = 0; j < NUM_EXAMS; j++) {
            in >> examScores[i][j];
        }
        allStudents[i] = studentFirstName + " " + studentLastName;
    }
    in.close();

    //Create a dynamic array of averages
    double *allExamAverages = new double[NUM_EXAMS];

    //Calculate the average exam scores
    for (unsigned int i = 0; i < NUM_EXAMS; i++) {
        double examTotalScore = 0.0;
        for (unsigned int j = 0; j < NUM_STUDENTS; j++) {
            examTotalScore = examTotalScore + examScores[j][i];
        }
        double examAverage = 0.0;
        examAverage = examTotalScore / NUM_STUDENTS;
        allExamAverages[i] = examAverage;
    }

    //Create a dynamic 2d array of grades
    char **examGrades = new char *[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        examGrades[i] = new char[NUM_EXAMS];
    }
    // Calculate letter grades
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        for (unsigned int j = 0; j < NUM_EXAMS; j++) {
            examGrades[i][j] = returnGrade(examScores[i][j], allExamAverages[j]);
        }
    }
    //Make Grade distribution
    const int NUM_LETTER_GRADES = 5;
    int **gradeDistribution = new int *[NUM_EXAMS];
    for (unsigned int i = 0; i < NUM_EXAMS; i++) {
        gradeDistribution[i] = new int[NUM_LETTER_GRADES];
    }
    //Assign letter grades
    for (unsigned int i = 0; i < NUM_EXAMS; i++) {
        for (unsigned int j = 0; j < NUM_LETTER_GRADES; j++) {
            int numOccurences = 0;
            for (int k = 0; k < NUM_STUDENTS; k++) {
                if (examGrades[k][i] == 'A' + j)
                    numOccurences++;
            }
            gradeDistribution[i][j] = numOccurences;
        }
    }

    //Calculate student final grades

    //Create a dynamic array of student average exam scores
    double *stdAvgExamScore = new double[NUM_STUDENTS];

    //Assign student averages
    double studentCumulativeTotal = 0.0;
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        double totalRawScore = 0.0;
        for (unsigned int j = 0; j < NUM_EXAMS; j++) {
            totalRawScore = totalRawScore + examScores[i][j];
        }
        double studentAvg = 0.0;
        studentAvg = totalRawScore / NUM_EXAMS;
        stdAvgExamScore[i] = studentAvg;
        studentCumulativeTotal = studentCumulativeTotal + stdAvgExamScore[i];
    }
    double classCumulativeAvg = 0.0;
    classCumulativeAvg = studentCumulativeTotal / NUM_STUDENTS;

    //Calculate letter grades
    char *stdAvgGrade = new char[NUM_STUDENTS];
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        stdAvgGrade[i] = returnGrade(stdAvgExamScore[i], classCumulativeAvg);
    }

    //WRITE EVERYTHING TO A TXT FILE
    ofstream out;
    out.open(argv[2]);
    out << "Student Scores:" << endl;
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        out << right << setw(20) << allStudents[i];
        for (unsigned int j = 0; j < NUM_EXAMS; j++) {
            out << setw(7) << examScores[i][j];
        }
        out << endl;
    }
    out << "Exam Averages:" << endl;
    for (unsigned int i = 0; i < NUM_EXAMS; i++) {
        out << right << setw(9) << "Exam " << i + 1 << " Average = " << setw(6) << setprecision(1)
            << fixed << allExamAverages[i] << endl;
    }
    out << "Student Exam Grades:" << endl;
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        out << right << setw(20) << allStudents[i];
        for (unsigned int j = 0; j < NUM_EXAMS; j++) {
            out << setw(6) << examScores[i][j] << "(" << examGrades[i][j] << ")";
        }
        out << endl;
    }
    out << "Exam Grades:" << endl;
    for (unsigned int i = 0; i < NUM_EXAMS; i++) {
        out << setw(10) << right << "Exam  " << i + 1;
        for (int k = 0; k < NUM_LETTER_GRADES; k++) {
            out << setw(5) << right << gradeDistribution[i][k] << "(" << static_cast<char>('A' + k) << ")";
        }
        out << endl;
    }
    out << "Student Final Grades:" << endl;
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        out << right << setw(20) << allStudents[i] << setw(6) << setprecision(1) << fixed << stdAvgExamScore[i]
            << "(" << stdAvgGrade[i] << ")" << endl;
    }
    out << "Class Average Score = " << classCumulativeAvg;

    //Eliminate all memory leaks!!
    delete[] stdAvgGrade;
    delete[] stdAvgExamScore;
    delete[] allStudents;
    delete[] allExamAverages;
    for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
        delete[] examScores[i];
        delete[] examGrades[i];
    }
    for (unsigned int i = 0; i < NUM_EXAMS; i++) {
        delete[] gradeDistribution[i];
    }
    delete[] examScores;
    delete[] examGrades;
    delete[] gradeDistribution;

    return 0;
}
