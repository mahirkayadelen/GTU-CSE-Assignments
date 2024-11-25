
#include "Student.h"

#include <iostream>
#include<string>
namespace P4{

    Student::Student() : name(""), id(0), courses(nullptr), numCourses(0) {}

    Student::Student(std::string name, std::string id) : name(name), id(id), courses(nullptr), numCourses(0) {}

    Student::~Student() {
        for (int i = 0; i < numCourses; i++) {
            delete courses[i];
        }
        delete[] courses;
    }

    std::string Student::getName() const {
        return name;
    }

    void Student::setName(std::string name) {
        this->name = name;
    }

    std::string Student::getID() const {
        return id;
    }

    void Student::setID(std::string id) {
        this->id = id;
    }

    void Student::addCourse(Course* course) {
        Course** newCourses = new Course*[numCourses + 1];
        for (int i = 0; i < numCourses; i++) {
            newCourses[i] = courses[i];
        }
        newCourses[numCourses] = course;
        delete[] courses;
        courses = newCourses;
        numCourses++;
    }

    void Student::removeCourse(Course* course) {
        int index = -1;
        for (int i = 0; i < numCourses; i++) {
            if (courses[i] == course) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return;
        }
        Course** newCourses = new Course*[numCourses - 1];
        for (int i = 0; i < index; i++) {
            newCourses[i] = courses[i];
        }
        for (int i = index + 1; i < numCourses; i++) {
            newCourses[i - 1] = courses[i];
        }
        delete[] courses;
        courses = newCourses;
        numCourses--;
    }

    Course** Student::getCourses() const {
        return courses;
    }

    int Student::getNumCourses() const {
        return numCourses;
    }
}