#include"PFArray.h"

int main(){
    PFArray<int> box;

    box.push_back(1);
    box.push_back(2);
    box.push_back(3);
    box.push_back(4);


    cout << "box size: " << box.size()<<endl;
    cout << "box empty: " << box.empty()<<endl;
    

    auto it = box.begin();
    cout << "First element: " << *it << endl;
    it += 2;
    cout << "iterator +=2 element: " << *it << endl;

    it -= 1;
    cout << "iterator -=1 element: " << *it << endl;

    it = box.end() - 1;
    cout << "Last element: " << *it << endl;

    box.erase(it);
    cout << "After erase function box:"<<endl;
    for(const auto& x : box){
        cout << x <<' ';
    }
    cout<<endl;

    cout << "NOW I WILL TRY TO ERASE INVALİD ITERATOR(for testing exception):"<<endl;
    try{
        box.erase(it+5);
    }
    catch(const out_of_range& e){
        cout << "Invalid iter!"<<endl;
    }

    cout <<endl;

    box.clear();
    cout << "BOX CLEARED."<<endl;

    cout << "Box size after clear: "<< box.size()<<endl;
    cout << "Box empty after clear: "<< box.empty()<<endl;

    box.push_back(3);
    box.push_back(1);
    box.push_back(4);
    box.push_back(1);
    cout << "New box filled with (3,1,4,1)"<<endl;
    
    sort(box.begin(),box.end());
    cout << "After sorted box:"<< endl;
    for (const auto& x : box) {
        cout << x << ' ';
    }
    cout << endl;
}