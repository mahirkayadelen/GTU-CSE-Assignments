#include"tetris.h"

int Tetris::getbottomc(){
    return bottomcolumn;
}

vector<Tetromino>& Tetris::gettetrosvector(){// get the vector and its reference
    return tetros;
}

int Tetris::gettotal()const{
    return total;
}

int Tetris::getcol()const {
    return col;
}

int Tetris::getrow()const {
    return row;
}

void Tetris::initBoard(){ // creates empty gameboard surrounded with X
    for(int i = 0;i<row;i++){
        for(int j = 0;j<col;j++){
            if(i == 0 || j == 0 || i == (row-1) || j  == (col-1)){
                gameboard[i][j] = 'X';
            }
            else
                gameboard[i][j] = ' ';
        }
    }
}

Tetris::Tetris(int x,int y){ //Constructs the class based on x and y entries
    total = 0;
    row = y;
    col = x;
    gameboard.resize(y,vector<char>(x));
    bottomcolumn=1;
}

void Tetris::Draw() const{ // prints gameboard to console
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

void Tetris::Fit(vector<Tetromino>&tetros){
    if(total == 1){

        if( tetros[total-1].gettype() == tetrominos::T || // for fix if there is any gap between wall and first tetromino special cases
            tetros[total-1].gettype() == tetrominos::I || 
            tetros[total-1].gettype() == tetrominos::Z){

            tetros[total-1].rotateCW();
            tetros[total-1].rotateCW();
            tetros[total-1].rotateCW();
            tetros[total-1].setposition(3); 
        }
        else if(tetros[total-1].gettype() == tetrominos::J){ // for fix if there is any gap between wall and first tetromino special cases
            tetros[total-1].rotateCW();
            tetros[total-1].rotateCW();
            tetros[total-1].setposition(2);
        }

    }
    else{
        while(!tetros[total-1].canFit(tetros[total-2])){ // checks whether previous and this tetromino fit with canFit func. if not, fit them with rotate func.
            tetros[total-1].rotate('R');
        } 
    }
    for(int i  =0;i<tetros[total-1].getvector().size();i++){ // fill at top-mid to tetromino to the board
            for(int j = 0;j<tetros[total-1].getvector()[0].size();j++){
                    gameboard[1+i][(getcol()/2)+j-1] = tetros[total-1].getvector()[i][j];
            }
    }
}

void Tetris::Animate(vector<Tetromino> &tetros){ //animates the added tetromino dropping to the bottom of the board
    for(int i  =0;i<tetros[total-1].getvector().size();i++){ //clear top mid 
        for(int j = 0;j<tetros[total-1].getvector()[0].size();j++){
                gameboard[1+i][(getcol()/2)+j-1] = ' ';
        }
    }
    Draw();
    Fit(tetros);

    for(int i  =0;i<tetros[total-1].getvector().size();i++){ //clear top mid 
        for(int j = 0;j<tetros[total-1].getvector()[0].size();j++){
                gameboard[1+i][(getcol()/2)+j-1] = ' ';
        }
    }

    for(int r = 1;r<gameboard.size()-(tetros[total-1].getvector().size());r++){//shifts tetromino to the bottom line by line
        for(int i  =0;i<tetros[total-1].getvector().size();i++){ // writes the current tetro to the board
            for(int j = 0;j<tetros[total-1].getvector()[0].size();j++){
                    gameboard[r+i][(getbottomc())+j] = tetros[total-1].getvector()[i][j];
            }
        }
        system("clear");
        Draw();
        usleep(50000); // sleeps 50miliseconds = 50000 microseconds
        if(r != (gameboard.size()-(tetros[total-1].getvector().size())-1)){// if its last row,it will not erase tetro bcz its shifted to bottom
            for(int i  =0;i<tetros[total-1].getvector().size();i++){ // erase the current tetro from the board
                for(int j = 0;j<tetros[total-1].getvector()[0].size();j++){
                        gameboard[r+i][(getbottomc())+j] = ' ';
                }
            }
        }
    }
    int gapctr=0;
    gapctr = fitGaps(gameboard); // if there is any gaps between the tetrominos. merge them.
    bottomcolumn+= tetros[total-1].getvector()[0].size(); // increases bottomcolumn with column size of last added tetromino
    bottomcolumn -= gapctr; // if there is any removed gap column , updates the bottom column ctr
    system("clear");
    Draw();
}

void Tetris::Add(char inp){//  Adds the entered input to the board
    total++;
    tetrominos temp;
    
    if(inp == 'I'){
        temp = tetrominos::I;
    }
    else if(inp == 'O'){
        temp = tetrominos::O;
    }
    else if(inp == 'T'){
        temp = tetrominos::T;
    }
    else if(inp == 'J'){
        temp = tetrominos::J;
    }
    else if(inp == 'L'){
        temp = tetrominos::L;
    }
    else if(inp == 'S'){
        temp = tetrominos::S;
    }
    else if(inp == 'Z'){
        temp = tetrominos::Z;
    }
    tetros.push_back(temp);

    for(int i  =0;i<tetros[total-1].getvector().size();i++){ // writes the current tetro to the board
        for(int j = 0;j<tetros[total-1].getvector()[0].size();j++){
            gameboard[1+i][(getcol()/2)+j-1] = tetros[total-1].getvector()[i][j];
        }
    }
}
