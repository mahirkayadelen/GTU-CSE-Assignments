#include "SchoolManagerSystem.h"

    int main() {
        using namespace P4;
        SchoolManagerSystem sms;
        sms.run();
        //     // Free memory before exiting
        // for (int i = 0; i < sms.getnumstudents(); i++) {
        //     delete &sms.getstudents(i);
        // }
        // // delete[] sms.students;
        // for (int i = 0; i < sms.getnumcourses(); i++) {
        //     delete &sms.getcourses(i);
        // }
        // // delete[] &sms.getcourse();
        return 0;
    }
