#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include<string>
namespace P4{
    class Course;

    class Student {
    public:
        Student();
        Student(std::string name, std::string id);
        ~Student();

        std::string getName() const;
        void setName(std::string name);

        std::string  getID() const;
        void setID(std::string id);

        void addCourse(Course* course);
        void removeCourse(Course* course);
        Course** getCourses() const;
        int getNumCourses() const;

    private:
        std::string name;
        std::string id;
        Course** courses;
        int numCourses;
    };
}
#endif
