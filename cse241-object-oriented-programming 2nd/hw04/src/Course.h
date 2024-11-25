#ifndef COURSE_H
#define COURSE_H



#include "Student.h"
#include<string>
namespace P4{
    class Student;

    class Course {
    public:
        Course(); // default constructor
        Course(std::string name, std::string code); // constructor
        ~Course(); // destructor

        std::string getName() const; // course name getter
        void setName(std::string name); // course name setter

        std::string getCode() const; // course code getter
        void setCode(std::string code); // course code setter

        void addStudent(Student* student); // for adding student to a course
        void removeStudent(Student* student); // for removing student from a course
        Student** getStudents() const; // dynamic students array getter
        int getNumStudents() const; // total number of student getter

    private:
        std::string name; // course name
        std::string code; // course code
        Student** students; // dynamic students array
        int numStudents; // number of students in course
    };
}
#endif
