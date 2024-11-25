#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
    srand(time(NULL));
    int exact = 0,misplaced = 0;
    int number[9],digit = 0;
    if(argc != 3 || argv[1][0] != '-' || (argv[1][1] != 'r' && argv[1][1] != 'u') ){ // checks if there is problem about arguments
        cout << "E0" << endl;
        exit(-1);
    }

    if(argv[1][1] == 'r'){ // if user enters -r
        if( !(argv[2][0]> '0' && argv[2][0] <= '9' && argv[2][1] == '\0') ){ // checks if 0<N≤9
            cout << "E0"<<endl;
            exit(-1);
        }
        digit = argv[2][0] - '0'; // converts input char to integer
        for(int i = 0;i<(argv[2][0] - '0');i++){//create random number
            if(i == 0) // it can't be 0 special situation
                number[i] = '0' + (rand() % 8 + 1);
            else{
                int flag=0;
                do{
                    number[i] = '0' + (rand() % 9);
                    flag = 0;
                    for(int j=i-1;j>=0;j--){
                        if(number[i] == number[j]){
                            flag++;
                        }
                    }
                }while(flag!=0);
            }
        }
    }
    
    else{ // if user enters -u
        for(int i  = 0;i<argv[2][i];i++){ // checks the argument is legal number and counts digit of number
            digit++;
            if(!(argv[2][i] >= '0' && argv[2][i] <= '9')){
                if(!(argv[2][i] == '\0')){
                    cout << "E0"<<endl;
                    exit(-1);
                }
            }
        }
        for(int i = 0;i<digit;i++){ // checks any digit appears only once in the number.
            for(int j = i+1;j<digit;j++){
                if(argv[2][i] == argv[2][j]){
                    cout << "E0" <<endl;
                    exit(-1);
                }
            }
        }
        if(!(digit >0 && digit <=9)){ // checks if 0<N≤9
            cout << "E0"<<endl;
            exit(-1);
        }
        for(int i = 0;i<digit;i++) // take input from argument to a number array
            number[i] =argv[2][i];
    }
    int iterations=0;
    string inputs;
    while(iterations < 100){ // game turns 100 times if user cant find in 100 times, game finishes
        iterations++;
        cin >> inputs;
        if(inputs.length() != digit){ //inputcheck -> entered digit control
            cout << "E1"<<endl;
            exit(-1);
        }
        for(int i = 0;i<digit;i++){//inputcheck -> If the user enters something but not an integer
            if(!(inputs[i] >= '0' && inputs[i] <= '9')){
                cout << "E2" << endl;
                exit(-1);
            }
        }

        for(int i = 0;i<digit;i++){ //inputcheck -> checks any digit appears only once in the number.
            for(int j = i+1;j<digit;j++){
                if(inputs[i] == inputs[j]){
                    cout << "E1" <<endl;
                    exit(-1);
                }
            }
        }

        for(int i = 0;i<digit;i++){ // counts exact digits
            if(inputs[i] == number[i])
                exact++;
        }
        for(int i = 0;i<digit;i++){ // counts misplaced digits
            for(int j = 0;j<digit;j++){
                if(i != j){
                    if(inputs[i] == number[j]){
                        misplaced++;
                    }
                }
            }
        }
        if(exact == digit){ // means user found the secret number
            cout << "FOUND "<< iterations<<endl;
            exit(1);
        }
        cout << exact << " " << misplaced << endl;
        exact = 0;
        misplaced = 0 ;
    }
    cout << "FAILED"<<endl;
    return 0;
}