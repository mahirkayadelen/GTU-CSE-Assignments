#include<iostream>
#include<cstdlib>
#include<initializer_list>
#include<fstream>

namespace Mahir{
    class DayOfYearSet{
    public:
        class DayOfYear{
            public:
                DayOfYear(int monthv,int dayv);
                DayOfYear(){};
                inline  int getday()const{return day;};
                inline  int getmonth()const{return month;};
                bool operator!=(const DayOfYear &other);
                bool operator<(const DayOfYear &other);
                bool operator>(const DayOfYear &other);
                bool operator==(const DayOfYear &other);
                friend std::ostream& operator<<(std::ostream& os,DayOfYear day);
            private:
                int month;
                int day;
        };
        DayOfYearSet(const std::initializer_list<DayOfYear> &days);
        DayOfYearSet(const DayOfYearSet&);
        DayOfYearSet();
        ~DayOfYearSet();
        friend std::ostream& operator<<(std::ostream& os,DayOfYearSet set); 
        DayOfYear* getDaysSet() const;
        void printDays();
        void setsize(int newsize);
        int getsize() const;
        void remove(const DayOfYear& toRemove);
        bool operator==(const DayOfYearSet&);
        bool operator!=(const DayOfYearSet&);
        DayOfYearSet::DayOfYear operator[](int index)const ;
        DayOfYearSet &operator=(const DayOfYearSet &other);
        DayOfYearSet operator+(const DayOfYear &newDay);
        DayOfYearSet operator+(const DayOfYearSet &newDay);
        DayOfYearSet operator-(const DayOfYear &toRemove);
        DayOfYearSet operator-(const DayOfYearSet &newDay);
    private:
        DayOfYear *daysSet;
        int size;
    };
}