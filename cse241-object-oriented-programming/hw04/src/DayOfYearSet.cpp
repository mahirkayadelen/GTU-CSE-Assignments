#include"DayOfYearSet.h"
using namespace std;
namespace Mahir{

    DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet &newDay){
        DayOfYearSet temp;
        int currentindex = 0;
        temp.daysSet = new DayOfYear[this->getsize()];

        for(int i = 0;i<this->getsize();i++){
            int check = 0;
            for(int j =0;j<newDay.getsize();j++){
                if(!(this->getDaysSet()[i] == newDay.getDaysSet()[j]))
                    check++;
            }
            if(check == newDay.getsize()){
                temp.daysSet[currentindex] = this->getDaysSet()[i];
                currentindex++; 
            }
        }
        temp.setsize(currentindex);
        return temp;
    }

    DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet &newDay){
        DayOfYearSet temp;
        int currentindex = 0;
        temp.daysSet = new DayOfYear[newDay.getsize() + this->getsize()];
        for(int i = 0;i<this->getsize();i++){
            temp.getDaysSet()[i] = this->getDaysSet()[i];
        }
        currentindex += this->getsize();
        for(int i = 0;i<this->getsize();i++){
            int check = 0;
            for(int j = 0;j<newDay.getsize();j++){
                if(!(temp.getDaysSet()[i] == newDay.getDaysSet()[j]))
                    check+=1;
            }
            if(check == newDay.getsize()){
                temp.getDaysSet()[currentindex] = newDay.getDaysSet()[i];
                currentindex++;
            }
        }
        temp.setsize(currentindex);
        return temp;
    }

    std::ostream& operator<<(std::ostream& os,DayOfYearSet set){
        for(int i = 0;i<set.getsize();i++){
            os << i+1<<")" <<set.getDaysSet()[i]<<std::endl;
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os,Mahir::DayOfYearSet::DayOfYear day){
        if(day.getmonth() == 1)
            os << "Month : January" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 2)
            os << "Month : February" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 3)
            os << "Month : March" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 4)
            os << "Month : April" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 5)
            os << "Month : May" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 6)
            os << "Month : June" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 7)
            os << "Month : July" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 8)
            os << "Month : August" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 9)
            os << "Month : September" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 10)
            os << "Month : October" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 11)
            os << "Month : November" <<  ", Day: " << day.getday() << std::endl;
        else if(day.getmonth() == 12)
            os << "Month : December" <<  ", Day: " << day.getday() << std::endl;
        return os;
    }
    DayOfYearSet::DayOfYear DayOfYearSet::operator[](int index)const{
        if(index >= size){
            std::cout << "Out of bond, exiting..";
            exit(0);
        }
        return this->daysSet[index];
    }

    void DayOfYearSet::remove(const DayOfYear& toRemove){
        int remove_index,flag=0;
        DayOfYearSet removedSet;
        removedSet.daysSet = new DayOfYear[size-1];
        removedSet.size = (this->size)-1;
        for(int i = 0;i<this->size;i++){
            if(daysSet[i] == toRemove){
                remove_index = i;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            std::cout << "cannot find day"<<std::endl;
            //delete[] &removedSet;
            return;
        }
        else{
            flag = 0;
            for(int i  =0;i<this->size;i++){
                if(i == remove_index){
                    flag = 1;
                }
                else{
                    if(flag == 0){
                        removedSet.getDaysSet()[i] = this->getDaysSet()[i];
                    }
                    else{
                        removedSet.getDaysSet()[i-1] = this->getDaysSet()[i];
                    }
                }
            }
            free(this->daysSet);
            this->size -=1;
            this->daysSet = new DayOfYearSet::DayOfYear[this->size];
            for(int i = 0;i<this->size;i++){
                this->getDaysSet()[i] = removedSet.getDaysSet()[i]; 
            }
        }
    }

    bool DayOfYearSet::DayOfYear::operator!=(const DayOfYear &other){
        if(this->month == other.getmonth() && this->day == other.getday())
            return false;
        else
            return true;
    }

    bool DayOfYearSet::operator!=(const DayOfYearSet& other){
        if(this->getsize() == other.getsize()){
            for(int i = 0;i<this->getsize();i++){
                if(this->getDaysSet()[i] != other.getDaysSet()[i]){
                    return true;
                }
            }
        }
        else{
            return true;
        }
        return false;
    }

    bool DayOfYearSet::operator==(const DayOfYearSet& other){
        if(this->getsize() == other.getsize()){
            for(int i = 0;i<this->getsize();i++){
                if(this->getDaysSet()[i] == other.getDaysSet()[i])
                    true;
                else
                    return false;
            }
            return true;
        }
        return false;
    }

    int DayOfYearSet::getsize() const{
        return size;
    }

    void DayOfYearSet::setsize(int newsize){
        size = newsize;
    }
    DayOfYearSet::DayOfYearSet(const DayOfYearSet& other){
        this->daysSet = new DayOfYear[other.getsize()];
        for(int i = 0;i<other.getsize();i++){
            this->getDaysSet()[i] = other.getDaysSet()[i];
        }
        this->size = other.getsize();
    }

    DayOfYearSet::~DayOfYearSet(){
        delete[] daysSet;
        daysSet = nullptr;
    }

    DayOfYearSet& DayOfYearSet::operator=(const DayOfYearSet &other){
        this->daysSet = new DayOfYear[other.getsize()];
        for(int i = 0;i<other.getsize();i++){
            this->getDaysSet()[i] = other.getDaysSet()[i];
        }
        this->size = other.getsize();

        return *this;
    }
    DayOfYearSet::DayOfYear* DayOfYearSet::getDaysSet()const{
        return daysSet;
    }

    void DayOfYearSet::printDays(){
        for(int i = 0;i<this->getsize();i++){
            std::cout << i+1 << ")Month= "<<this->daysSet[i].getmonth()<< ", Day = "<< this->daysSet[i].getday() <<std::endl;
        }
    }

    bool DayOfYearSet::DayOfYear::operator==(const DayOfYearSet::DayOfYear &other){
        if(this->getmonth() == other.getmonth()){
            if(this->getday() == other.getday())
                return true;
            else
                return false;
        }
        else
            return false;
        return false;
    }

    bool DayOfYearSet::DayOfYear::operator<(const DayOfYearSet::DayOfYear &other){
        if(this->getmonth() < other.getmonth())
            return true;
        else if(this->getmonth() > other.getmonth())
            return false;
        else{
            if(this->getday() < other.getday())
                return true;
            else if(this->getday() > other.getday())
                return false;
            else
                return false;
        }
        return false;
    }

    bool DayOfYearSet::DayOfYear::operator>(const DayOfYearSet::DayOfYear &other){
        if(this->getmonth() > other.getmonth())
            return true;
        else if(this->getmonth() < other.getmonth())
            return false;
        else{
            if(this->getday() > other.getday())
                return true;
            else if(this->getday() < other.getday())
                return false;
            else
                return false;
        }
        return false;
    }


    DayOfYearSet  DayOfYearSet::operator-(const DayOfYear &toRemove){
        this->remove(toRemove);
        return *this;
    }

    DayOfYearSet DayOfYearSet::operator+(const DayOfYear &newDay){
        int newplace,flag =-1;
        size +=1;
        if(daysSet == NULL){
            daysSet = new DayOfYearSet::DayOfYear(newDay.getmonth(),newDay.getday());
        }
        else{
            for(int i = 0;i<getsize()-1;i++){
                if(daysSet[i] == newDay)
                {
                    std::cout << "cannot add its available";
                    size-=1;
                    return *this;
                }

                else if(daysSet[i] > newDay){
                    newplace = i;
                    break;
                }

                else if(daysSet[i] < newDay){
                    if(i == getsize()-2)
                        newplace = i+1;
                    continue;
                }
                
                
            }
            DayOfYearSet newSet;
            newSet.daysSet = new DayOfYearSet::DayOfYear[size];
            newSet.setsize(size);
            for(int i = 0;i<size;i++){
                if(i == newplace){
                    newSet.daysSet[i] = newDay;
                    if(i < size-1){
                        flag = i;
                        break;
                    }
                }
                else{
                    newSet.daysSet[i] = this->daysSet[i];
                }
            }
            if(flag != -1){
                for(int i = flag;i<size-1;i++){
                    newSet.daysSet[i+1] = this->daysSet[i];
                }
            }
            free(this->daysSet);
            return newSet;
        }
        return *this;
    }
    DayOfYearSet::DayOfYear::DayOfYear(int monthv,int dayv){
        if(monthv == 1){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 2){
            if(dayv > 0 && dayv <= 28 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 3){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 4){
            if(dayv > 0 && dayv <= 30 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 5){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 6){
            if(dayv > 0 && dayv <= 30 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 7){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 8){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 9){
            if(dayv > 0 && dayv <= 30 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 10){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 11){
            if(dayv > 0 && dayv <= 30 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else if(monthv == 12){
            if(dayv > 0 && dayv <= 31 ){
                month = monthv;
                day = dayv;
            }
            else{
                cout << "Wrong day.";
                exit(1);
            }
        }
        else{
            cout << "Wrong month.";
            exit(1);
        }
    }

    DayOfYearSet::DayOfYearSet()
    {
        daysSet = NULL;
        size = 0;
    }

    DayOfYearSet::DayOfYearSet(const std::initializer_list<DayOfYear> &days){
        daysSet = new DayOfYear[days.size()];
        int i = 0;
        for(auto &temp : days){
            this->daysSet[i++] = const_cast<DayOfYear&>(temp);
        }
        size = i;
    }

}
