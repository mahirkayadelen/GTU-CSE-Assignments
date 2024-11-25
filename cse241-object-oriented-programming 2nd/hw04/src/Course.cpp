
#include "Course.h"

#include <iostream>
#include<string>
namespace P4{
    Course::Course() : name(""), code(""), students(nullptr), numStudents(0) {}

    Course::Course(std::string name, std::string code) : name(name), code(code), students(nullptr), numStudents(0) {}

    Course::~Course() {
        for (int i = 0; i < numStudents; i++) {
            delete students[i];
        }
        delete[] students;
    }

    std::string Course::getName() const {
        return name;
    }

    void Course::setName(std::string name) {
        this->name = name;
    }

    std::string Course::getCode() const {
        return code;
    }

    void Course::setCode(std::string code) {
        this->code = code;
    }

    void Course::addStudent(Student* student) {
        Student** newStudents = new Student*[numStudents + 1];
        for (int i = 0; i < numStudents; i++) {
            newStudents[i] = students[i];
        }
        newStudents[numStudents] = student;
        delete[] students;
        students = newStudents;
        numStudents++;
    }

    void Course::removeStudent(Student* student) {
        int index = -1;
        for (int i = 0; i < numStudents; i++) {
            if (students[i] == student) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return;
        }
        Student** newStudents = new Student*[numStudents - 1];
        for (int i = 0; i < index; i++) {
            newStudents[i] = students[i];
        }
        for (int i = index + 1; i < numStudents; i++) {
            newStudents[i - 1] = students[i];
        }
        delete[] students;
        students = newStudents;
        numStudents--;
    }

    Student** Course::getStudents() const {
        return students;
    }

    int Course::getNumStudents() const {
        return numStudents;
    }
}