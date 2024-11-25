#include"AbstractTetris.h"
#include"TetrisVector.h"
#include<iostream>
#include<unistd.h>
#include<vector>
#include<time.h>
#include<cstdlib>
#include<fstream>

using namespace Mahir;

namespace Vector{
int TetrisVector::getcol() const{ 
    return col;
}

int TetrisVector::getrow() const{ 
    return row;
}


TetrisVector::TetrisVector(int x,int y){//Constructs the class based on x and y entries
    totalmoves = 0;
    row = y;
    col = x;
    gameboard.resize(y,vector<char>(x));
    initBoard();
}

int TetrisVector::numberOfMoves()const{
        return totalmoves;
    }

void TetrisVector::operator+=(Tetromino add){
    totalmoves+=1;
    for(int i  =0;i<add.getrow();i++){ // writes the current tetro to the top mid of gameboard
        for(int j = 0;j<add.getcol();j++){
            gameboard[1+i][(getcol()/2)+j-1] = add.getvector()[i][j];
        }
    }
}

void TetrisVector::initBoard(){ // creates empty gameboard surrounded with X
    for(int i = 0;i<row;i++){
        for(int j = 0;j<col;j++){
            if (i == 0 ||i == row-1)
                gameboard[i][j] = 'X';
            else if (j == 0 || j == col-1)
                gameboard[i][j] = 'X';
            else
                gameboard[i][j] = ' ';
        }
    }
}

void TetrisVector::draw() const{ // prints gameboard to console
    for(int i = 0;i<row;i++){
        for(int j = 0;j<col;j++){
            if(gameboard[i][j] != '.')
                cout << gameboard[i][j];
            else
                cout << ' ';
        }
        cout << endl;
    }
}

int TetrisVector::animate(Tetromino &a){
    char rotatedir,movedir;
    int rotatetimes,movetimes,isValid,tetrocolumn;
    draw();
    totalmoves+=1;

    for(int i  =0;i<a.getrow();i++){ // clears top mid of gameboard
        for(int j = 0;j<a.getcol();j++){
            gameboard[1+i][(getcol()/2)+j-1] = ' ';
        }
    }

    
    int isValidinp;
    do{
        cout << "\nPlease enter rotation direction('R' for right,'L' for left):";
        cin >> rotatedir;
        if(rotatedir != 'R' && rotatedir != 'L'){
            cout <<endl<< "Wrong input! please try again."<<endl;
            cin.ignore();
            isValidinp = 1;
        }
        else
            isValidinp = 0;
    }while(isValidinp);


    cout << "\nPlease enter rotation count:";
        cin >> rotatetimes;
        while(cin.fail() || rotatetimes < 0)
        {
            cin.clear();
            cin.ignore();
            cout << "\nBad entry.  Enter rotation count again: ";
            cin >> rotatetimes;
        }


    while(rotatetimes>0){ // rotates tetromino with user input
        if(rotatedir == 'R'){
            a.rotateCW();
        }
        else{
            a.rotateCW();
            a.rotateCW();
            a.rotateCW();
        }
        rotatetimes--;
    }

    do{ // The loop continues until the user enters valid move
        int isValidinp;
        
        do{
            cout << "\nPlease enter move direction:('R' for right, 'L' for left):";
            cin >> movedir;
            if(movedir != 'R' && movedir != 'L'){
                cout <<endl<< "Wrong input! please try again."<<endl;
                cin.ignore();
                isValidinp = 1;
            }
            else
                isValidinp = 0;
        }while(isValidinp);

        cout << "\nPlease enter move times:"<<endl;
        cin >> movetimes;
        while(cin.fail() || movetimes < 0)
        {
            cin.clear();
            cin.ignore();
            cout << "\nBad entry.  Enter move times again: ";
            cin >> movetimes;
        }

        tetrocolumn=(getcol()/2)-1; 
        
        if(movedir == 'L'){
            tetrocolumn -= movetimes;
        }
        else if(movedir == 'R'){
            tetrocolumn += movetimes;
        }
        if(a.getcol() + tetrocolumn >= getcol() || tetrocolumn <1){
            isValid = 0;
            cout << "Out of board!!"<<endl;
        }
        else
            isValid = 1;
    }while(isValid==0);
    
    for(int r = 1;r<getrow()-(a.getrow());r++){//shifts tetromino to the bottom line by line
        int flag = 0; // flag for check whether tetromino stops
        for(int i  =0;i<a.getrow();i++){ // writes the current tetro to the board
            for(int j = 0;j<a.getcol();j++){
                    gameboard[r+i][(tetrocolumn)+j] = a.getvector()[i][j];
            }
        }
        for(int i  =a.getrow()-1;i<a.getrow();i++){ // increment flag if tetromino can not shift 1 line down
            for(int j = 0;j<a.getcol();j++){
                if(!(gameboard[r+i+1][(tetrocolumn)+j] == ' ' || gameboard[r+i+1][(tetrocolumn)+j] == '.')){
                    flag +=1;
                    if(r == 1){ // if there is no move in first row it means game finished.
                        draw();
                        totalmoves+=1;
                        cout << "Game Over"<<endl;
                        return 0;
                    }
                }
            }
        }
        system("clear");
        draw();
        totalmoves+=1;
        usleep(50000); // sleeps 50miliseconds = 50000 microseconds
        if(flag == 0){// if its last row,it will not erase tetro bcz its shifted to bottom
            for(int i  =0;i<a.getrow();i++){ // erase the current tetro from the board
                for(int j = 0;j<a.getcol();j++){
                        gameboard[r+i][(tetrocolumn)+j] = ' ';
                }
            }
        }
        else{ // if flag is not 0 means shift operation finished so animate also.
            return 1;
        }
    }
    return 1;
}

bool TetrisVector::writeToFile(const string & filename){
    ofstream outp(filename);

    try{
        if(!outp)
            throw ErrorFile{};
        for(int i = 0;i<getrow();i++){
            for(int j = 0;j<getcol();j++){
                if(gameboard[i][j] == '.')
                    outp << " ";
                else
                    outp << gameboard[i][j];
            }
            outp << endl;
        }

        outp.close();
    }

    catch(ErrorFile){
        cout << "Error!" << endl;
        return false;
    }
    return true;
}

bool TetrisVector::readFromFile(const string & filename){
    ifstream input(filename);
    vector<string> rowsize;
    string onerow;

    try{
        if(!input)
            throw ErrorFile{};

        while(getline(input,onerow,'\n'))
            rowsize.push_back(onerow);
        input.close();
    }
    catch(ErrorFile){
        cout << "Error!" << endl;
    }

    row = rowsize.size();
    col = rowsize[0].size();
    *this = TetrisVector(col,row);

    for(int i  =0 ; i < row;i++){
        for(int j = 0;j<col ; j++){
            gameboard[i][j] = rowsize[i][j];
        }
    }
    return true;
}

}