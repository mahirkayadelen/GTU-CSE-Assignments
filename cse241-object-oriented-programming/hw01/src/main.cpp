#include"tetro.h"


int main(){
    vector<Tetromino>tetrovec;
    vector<vector<char>> board(4);
    int inp;
    cout << "How many tetrominos?"<<endl;
    cin >> inp;
    
    setvector(tetrovec,inp); //takes inputs and fills vector arrays

    cout << "Your tetrominos:"<< endl;
    for(int i = 0;i<inp;i++){//printing ready tetrominos
        tetrovec[i].print();
    }
    
    for(int i = 0;i<tetrovec.size()-1;i++){ // turns all the tetrominos in the right direction in order
        while(!(tetrovec[i+1].canFit(tetrovec[i]))){
            tetrovec[i+1].rotate('R');
        }
    }
    createBoard(board,tetrovec); //fills a row of tetrominos to the board
    cleanEmptyColumns(board); //if there is an empty column,deletes it and scrolls vector
    cleanEmptyColumns(board); // for fix the bug(if there is 2 empty column consecutive)
    fitGaps(board); // Merge letters
    cout << "Horizontally best-fit tetrominos"<<endl;
    printBoard(board);
}