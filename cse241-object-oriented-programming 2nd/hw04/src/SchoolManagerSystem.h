
#ifndef SCHOOLMANAGERSYSTEM_H
#define SCHOOLMANAGERSYSTEM_H
#include "Student.h"
#include "Course.h"
#include<string>
namespace P4{
    class SchoolManagerSystem {
    public:
        SchoolManagerSystem();
        ~SchoolManagerSystem();

        void run();

    private:
        Student** students;
        int numStudents;
        Course** courses;
        int numCourses;

        void addStudent();
        void selectStudent();
        void deleteStudent(Student& selectedStudent);
        void addSelectedStudentToCourse(Student& selectedStudent);
        void dropSelectedStudentFromCourse(Student& selectedStudent);

        Course* find_course(const std::string& code, const std::string& name) const;

        void addCourse();
        void selectCourse();
        void deleteCourse(Course& selectedCourse);
        void listStudentsRegisteredToSelectedCourse(Course& selectedCourse);
        void listAllStudents();
        void listAllCourses();
    };

}
#endif
