#include "SchoolManagerSystem.h"

#include <iostream>
#include <string>
namespace P4{
    SchoolManagerSystem::SchoolManagerSystem() : students(nullptr), numStudents(0), courses(nullptr), numCourses(0) {}

    SchoolManagerSystem::~SchoolManagerSystem() {
        for (int i = 0; i < numStudents; i++) {
            delete students[i];
        }
        delete[] students;
        for (int i = 0; i < numCourses; i++) {
            delete courses[i];
        }
        delete[] courses;
    }

    void SchoolManagerSystem::run() {
        char choice = '-';
        while (choice!= '0') {
            std::cout << "Main_menu" << std::endl;
            std::cout << "0 exit" << std::endl;
            std::cout << "1 student" << std::endl;
            std::cout << "2 course" << std::endl;
            std::cout << "3 list_all_students" << std::endl;
            std::cout << "4 list_all_courses" << std::endl;
            std::cout << ">> ";
            std::cin >> choice;
            switch (choice) {
                case '0':
                // first 2 for loops are for fixing a bug which causes segmentation fault when time to program ends with user input '0'
                    for(int i = 0;i<numStudents;i++){
                        for(int j = 0;j<numCourses;j++){
                            students[i]->removeCourse(courses[j]);
                        }
                    }
                    for(int i = 0;i<numCourses;i++){
                        for(int j = 0;j<numStudents;j++){
                            courses[i]->removeStudent(students[j]);
                        }
                    }
                    break;

                case '1':
                    choice = '-';
                    do{
                    std::cout << "0 up" << std::endl;
                    std::cout << "1 add_student" << std::endl;
                    std::cout << "2 select_student" << std::endl;
                    std::cout << ">> ";
                    std::cin >> choice;
                    switch (choice) {
                        case '0':
                            choice = '7';
                            break;
                        case '1':
                            addStudent();
                            break;
                        case '2':
                            selectStudent();
                            break;
                        default:
                            std::cout << "Invalid choice" << std::endl;
                            break;
                    }
                    }while(choice != '7');
                    break;
                case '2':
                    choice = '-';
                    do{
                    std::cout << "0 up" << std::endl;
                    std::cout << "1 add_course" << std::endl;
                    std::cout << "2 select_course" << std::endl;
                    std::cout << ">> ";
                    std::cin >> choice;
                    switch (choice) {
                        case '0':
                            choice = '7';
                            break;
                        case '1':
                            addCourse();
                            break;
                        case '2':
                            selectCourse();
                            break;
                        default:
                            std::cout << "Invalid choice" << std::endl;
                            break;
                    }
                    }while(choice != '7');
                    break;
                case '3':
                    listAllStudents();
                    break;
                case '4':
                    listAllCourses();
                    break;
                default:
                    std::cout << "Invalid choice" << std::endl;
                    break;
            }
        }
    }

    void SchoolManagerSystem::addStudent() {
        std::string name;
        std::string id;
        std::string input;
        std::cout << ">> ";


                        
        std::cin.ignore(); // for clean buffer
        std::getline(std::cin, input); // get input
        std::size_t firstSpace = input.find(' '); // find  1st space for parse id and name of course
        std::size_t secondSpace = input.find(' ', firstSpace + 1); // find 2nd space
        name = input.substr(0, secondSpace); // name = before ' '
        id = input.substr(secondSpace + 1); // id = after 2nd ' ' char



        Student** newStudents = new Student*[numStudents + 1];
        for (int i = 0; i < numStudents; i++) {
            newStudents[i] = students[i];
        }
        newStudents[numStudents] = new Student(name, id);
        delete[] students;
        students = newStudents;
        numStudents++;
    }

    void SchoolManagerSystem::selectStudent() {
        std::string name;
        std::string id;
        std::string input;
        std::cout << ">> ";

        std::cin.ignore(); // for clean buffer
        std::getline(std::cin, input); // get input
        std::size_t firstSpace = input.find(' '); // find  1st space for parse student name and surname
        std::size_t secondSpace = input.find(' ', firstSpace + 1); // find 2nd space
        name = input.substr(0, secondSpace); // name = before 2nd ' '
        id = input.substr(secondSpace + 1); // id = after 2nd ' ' char

        Student* selectedStudent = nullptr;
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->getName() == name && students[i]->getID() == id) {
                selectedStudent = students[i];
                break;
            }
        }
        if (selectedStudent == nullptr) {
            return;
        }
        char choice = '-';
        do{
            std::cout << "0 up" << std::endl;
            std::cout << "1 delete_student" << std::endl;
            std::cout << "3 add_selected_student_to_a_course" << std::endl;
            std::cout << "4 drop_selected_student_from_a_course" << std::endl;
            std::cout << ">> ";
            std::cin >> choice;
            switch (choice) {
                case '0':
                    break;
                case '1':
                    deleteStudent(*selectedStudent);
                    break;
                case '3':
                    addSelectedStudentToCourse(*selectedStudent);
                    break;
                case '4':
                    dropSelectedStudentFromCourse(*selectedStudent);
                    break;
                default:
                    std::cout << "Invalid choice" << std::endl;
                    break;
            }
        }while(choice != '0');
        
    }

    void SchoolManagerSystem::deleteStudent(Student& selectedStudent) {
        int index = -1;
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->getID() == selectedStudent.getID()) {
                index = i;
                break;
            }
        }
        Student** newStudents = new Student*[numStudents - 1];
        for (int i = 0; i < index; i++) {
            newStudents[i] = students[i];
        }
        for (int i = index + 1; i < numStudents; i++) {
            newStudents[i - 1] = students[i];
        }
        delete &selectedStudent;
        delete[] students;
        students = newStudents;
        numStudents--;
    }

    void SchoolManagerSystem::addSelectedStudentToCourse(Student& selectedStudent) {

        std::string name;
        std::string code;
        int selectedcrs;

        std::cout << "0 up" << std::endl;
        for(int i = 0;i<numCourses;i++){
            std::cout << i+1 << " " << courses[i]->getCode() << " " << courses[i]->getName() << std::endl;
        }
        std::cout << ">> ";
        std::cin >> selectedcrs;

        if(selectedcrs == 0)
            return;

        Course* selectedCourse = nullptr;
        selectedCourse = courses[selectedcrs-1];



        for (int i = 0; i < selectedStudent.getNumCourses(); i++) {
            if (selectedStudent.getCourses()[i] == selectedCourse) {
                std::cout << "Error: student is already registered for this course" << std::endl;
                return;
            }
        }
        selectedCourse->addStudent(&selectedStudent);
        selectedStudent.addCourse(selectedCourse);
    }

    void SchoolManagerSystem::dropSelectedStudentFromCourse(Student& selectedStudent) {

        std::string name;
        std::string code;
        int selectedcrs;

        std::cout << "0 up" << std::endl;
        
        for(int i = 0;i<selectedStudent.getNumCourses();i++){
            std::cout << i+1 << " " << selectedStudent.getCourses()[i]->getCode() << " " << selectedStudent.getCourses()[i]->getName() << std::endl;
        }
        std::cout << ">> ";
        std::cin >> selectedcrs;
        if(selectedcrs == 0)
            return;



        Course* selectedCourse = nullptr;
        selectedCourse = courses[selectedcrs-1];

        if (selectedCourse == nullptr) {
            return;
        }

        bool found = false;
        for (int i = 0; i < selectedStudent.getNumCourses(); i++) {
            if (selectedStudent.getCourses()[i] == selectedCourse) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Error: student is not registered for this course" << std::endl;
            return;
        }
        selectedCourse->removeStudent(&selectedStudent);
        selectedStudent.removeCourse(selectedCourse);
    }

    void SchoolManagerSystem::addCourse() {
        std::string name;
        std::string code;
        std::string input;
        std::cout << ">> ";
        
        std::cin.ignore(); // for clean buffer
        std::getline(std::cin, input); // get input
        std::size_t firstSpace = input.find(' '); // find  1st space for parse course id and name
        code = input.substr(0, firstSpace); // code = before 1st ' '
        name = input.substr(firstSpace + 1); // name = after 1st ' ' char



        Course** newCourses = new Course*[numCourses + 1];
        for (int i = 0; i < numCourses; i++) {
            newCourses[i] = courses[i];
        }
        newCourses[numCourses] = new Course(name, code);
        delete[] courses;
        courses = newCourses;
        numCourses++;
    }

    void SchoolManagerSystem::selectCourse() {
        std::string name;
        std::string code;
        std::string input;


        std::cin.ignore(); // for clean buffer
        std::getline(std::cin, input); // get input
        std::size_t firstSpace = input.find(' '); // find  1st space for parse course id and name
        code = input.substr(0, firstSpace); // code = before 1st ' '
        name = input.substr(firstSpace + 1); // name = after 1st ' ' char




        Course* selectedCourse = nullptr;
        for (int i = 0; i < numCourses; i++) {
            if (courses[i]->getName() == name && courses[i]->getCode() == code) {
                selectedCourse = courses[i];
                break;
            }
        }
        if (selectedCourse == nullptr) {
            return;
        }
        int choice = -1;
        while (choice != 0) {
            std::cout << "0 up" << std::endl;
            std::cout << "1 delete_course" << std::endl;
            std::cout << "2 list_students_registered_to_the_selected_course" << std::endl;
            std::cin >> choice;
            switch (choice) {
                case 0:
                    break;
                case 1:
                    deleteCourse(*selectedCourse);
                    choice = 0;
                    break;
                case 2:
                    listStudentsRegisteredToSelectedCourse(*selectedCourse);
                    break;
                default:
                    std::cout << "Invalid choice" << std::endl;
                    break;
            }
        }
    }

    void SchoolManagerSystem::deleteCourse(Course& selectedCourse) {
        
        int index = -1;
        for (int i = 0; i < numCourses; i++) {
            if (courses[i]->getCode() == selectedCourse.getCode()) {
                index = i;
                break;
            }
        }
        Course** newCourses = new Course*[numCourses - 1];
        for (int i = 0; i < index; i++) {
            newCourses[i] = courses[i];
        }
        for (int i = index + 1; i < numCourses; i++) {
            newCourses[i - 1] = courses[i];
        }
        delete &selectedCourse;
        delete[] courses;
        courses = newCourses;
        numCourses--;
    }

    void SchoolManagerSystem::listAllStudents() {
        if (numStudents == 0) {
            std::cout << "No students registered yet." << std::endl;
            return;
        }
        std::cout << "List of all students:" << std::endl;
        for (int i = 0; i < numStudents; i++) {
            std::cout << "Student " << i+1 << ":" << std::endl;
            std::cout << "Name: " << students[i]->getName() << std::endl;
            std::cout << "ID: " << students[i]->getID() << std::endl;
            std::cout << "Courses taken: " << std::endl;
            if (students[i]->getNumCourses() == 0) {
                std::cout << "None" << std::endl;
            } else {
                for (int j = 0; j < students[i]->getNumCourses(); j++) {
                    std::cout << "- " << students[i]->getCourses()[j]->getName() << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }

    void SchoolManagerSystem::listStudentsRegisteredToSelectedCourse(Course& selectedCourse)  {

        if (selectedCourse.getNumStudents() == 0) {
            std::cout << "No students registered for this course yet." << std::endl;
            return;
        }
        std::cout << "List of students registered for " << selectedCourse.getName() << ":" << std::endl;
        for (int i = 0; i < selectedCourse.getNumStudents(); i++) {
            std::cout << "- " << selectedCourse.getStudents()[i]->getName() << " (ID: " << selectedCourse.getStudents()[i]->getID() << ")" << std::endl;
        }
    }




    void SchoolManagerSystem::listAllCourses() {
        if (numCourses == 0) {
            std::cout << "No courses available yet." << std::endl;
            return;
        }
        std::cout << "List of all courses:" << std::endl;
        for (int i = 0; i < numCourses; i++) {
            std::cout << "Course " << i+1 << ":" << std::endl;
            std::cout << "Code: " << courses[i]->getCode() << std::endl;
            std::cout << "Name: " << courses[i]->getName() << std::endl;
            std::cout << "Students registered: " << std::endl;
            if (courses[i]->getNumStudents() == 0) {
                std::cout << "None" << std::endl;
            } else {
                for (int j = 0; j < courses[i]->getNumStudents(); j++) {
                    std::cout << "- " << courses[i]->getStudents()[j]->getName() << " (ID: " << courses[i]->getStudents()[j]->getID() << ")" << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }


    Course* SchoolManagerSystem::find_course(const std::string& code, const std::string& name) const {
        for (int i = 0; i < numCourses; i++) {
            if (courses[i]->getCode() == code && courses[i]->getName() == name) {
                return courses[i];
            }
        }
        return nullptr;
    }
}