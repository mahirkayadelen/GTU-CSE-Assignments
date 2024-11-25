#include"DayOfYearSet.h"
using namespace Mahir;
using namespace std;
int main(){
    ofstream output;
    output.open("mahir.txt");
    DayOfYearSet days1;
    days1 = days1 + DayOfYearSet::DayOfYear(3,2);
    days1 = days1 + DayOfYearSet::DayOfYear(3,4);
    days1 = days1 + DayOfYearSet::DayOfYear(2,4);


    decltype(days1) days2 = {DayOfYearSet::DayOfYear(7,9),DayOfYearSet::DayOfYear(1,1),DayOfYearSet::DayOfYear(2,21),DayOfYearSet::DayOfYear(5,17)};
    cout << "overloaded stream insertion for days1"<<endl;
    output << "overloaded stream insertion for days1"<<endl;

    cout << days1<<endl;
    output << days1<<endl;

    cout << "overloaded stream insertion for days2"<<endl;
    output << "overloaded stream insertion for days2"<<endl;

    cout << days2<<endl;
    output << days2<<endl;

    cout << "overloaded == operator use for days1 and days2 result: "<<endl;
    output << "overloaded == operator use for days1 and days2 result: "<<endl;
    cout << (days1 == days2)<<endl;
    output << (days1 == days2)<<endl;

    cout << "overloaded != operator use for days1 and days2 result: "<<endl;
    output << "overloaded != operator use for days1 and days2 result: "<<endl;
    cout << (days1 != days2)<<endl;
    output << (days1 != days2)<<endl;

    cout << "remove function removes february 4 in days1"<<endl;
    output << "remove function removes february 4 in days1"<<endl;
    days1.remove(DayOfYearSet::DayOfYear(2,4));
    cout << "new days1 set:"<<endl;
    output << "new days1 set:"<<endl;
    cout << days1;
    output << days1;

    cout << "size function for days1:";
    output << "size function for days1:";
    cout << days1.getsize()<<endl;
    output << days1.getsize()<<endl;

    cout << "overloaded binary operator+ and adds july 20 element to days1:"<<endl;
    output << "overloaded binary operator+ and adds july 20 element to days1:"<<endl;
    days1 = days1 + DayOfYearSet::DayOfYear(7,20);
    cout << days1;
    output << days1;

    DayOfYearSet days3;
    days3 = days1 + days2;
    cout << "binary operator+ on days3 set(days1 + days2):"<<endl;
    output <<"binary operator+ on days3 set(days1 + days2):"<<endl;
    cout << days3;
    output << days3;

    days3 = days1 - days2;
    cout << "binary operator- on days3 set(days1 - days2):"<<endl;
    output <<"binary operator- on days3 set(days1 - days2):"<<endl;
    cout << days3;
    output << days3;

    cout << "overloaded binary operator- and deletes march 2 element to days3:"<<endl;
    output << "overloaded binary operator- and deletes march 2 element to days3:"<<endl;
    days3 = days3 - DayOfYearSet::DayOfYear(3,2);
    cout << days3;
    output << days3;

    cout << "overloaded binary operator[] for days3[1]:"<<endl;
    output << "overloaded binary operator[] for days3[1]:"<<endl;
    cout << days3[1];
    output << days3[1];

    // std::cout << "size: "<< days3.getsize()<<std::endl;
    // days3 = days + days2;

    // std::cout << days3 << "days"<< std::endl;
    // std::cout << days;

    // for(int i = 0;i<days.getsize();i++){
    //     output << days.getDaysSet()[i];
    // }
    // output << days;

    // DayOfYearSet days3;
    // days3 = days1 - days2;
    // std::cout << days3;


    output.close();
    
}