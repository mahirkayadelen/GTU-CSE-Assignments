#include"AbstractTetris.h"
#include"TetrisAdapter.h"
#include<iostream>
#include<unistd.h>
#include<vector>
#include<time.h>
#include<cstdlib>

using namespace Mahir;

namespace Adapter{
template<class T>
int TetrisAdapter<T>::getcol() const{ 
    return col;
}

template<class T>
int TetrisAdapter<T>::getrow() const{ 
    return row;
}

template<class T>
TetrisAdapter<T>::TetrisAdapter(int x,int y){//Constructs the class based on x and y entries
    totalmoves=0;
    row = y;
    col = x;
    gameboard.resize(y,vector<char>(x));


    // for(int i=0; i<y; i++){ 
    //     vector<char> row;
    //     for(int j=0; j<x; j++){
    //         row.push_back(' ');
    //     }
    // gameboard.push_back(row);
    // }



    initBoard();
}

template<class T>
int TetrisAdapter<T>::numberOfMoves()const{
        return totalmoves;
    }

template<class T>
void TetrisAdapter<T>::operator+=(Tetromino add){
    totalmoves+=1;
    for(int i  =0;i<add.getrow();i++){ // writes the current tetro to the top mid of gameboard
        for(int j = 0;j<add.getcol();j++){
            gameboard[1+i][(getcol()/2)+j-1] = add.getvector()[i][j];
        }
    }
}
template<class T>
void TetrisAdapter<T>::initBoard(){ // creates empty gameboard surrounded with X
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
template<class T>
void TetrisAdapter<T>::draw() const{ // prints gameboard to console
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
template<class T>
int TetrisAdapter<T>::animate(Tetromino &a){
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

}