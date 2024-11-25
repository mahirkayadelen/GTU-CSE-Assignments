#include"tetris.h"

int main(){
    cout << "Tetromino object created";
    Tetromino temp(tetrominos::I);
    cout <<endl<< "print function tetromino:"<<endl;
    temp.print();

    cout <<endl<< "Rotated right 1 times"<<endl;
    temp.rotateCW();
    temp.print();

    cout << "Tetromino board created created (20,10)";
    Tetris mytetris(20,10);
    cout << "Draw function draws gameboard:"<<endl;
    mytetris.Draw();
    mytetris += temp;
    cout << "Added tetromino I to the board and draw:"<<endl;
    mytetris.Draw();

    mytetris.Animate(temp);
    cout <<"Animate function called."<<endl;
}