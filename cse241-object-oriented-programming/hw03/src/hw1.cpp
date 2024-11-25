#include"tetris.h"

void Tetromino::set2dtetro(){ // fills char arrays depends on tetrominos enum
    if(type == tetrominos::I){
        charvec = new char*[1]; 
        row = 1;
        col = 4;
        charvec[0] = new char[4];
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                charvec[i][j] = 'I';
            }
        }
    }
    else if(type == tetrominos::O){
        row = 2;
        col = 2;

        charvec = new char*[row]; 
        for(int i = 0;i<row;i++)
            charvec[i] = new char[col];
        
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                charvec[i][j] = 'O';
            }
        }
    }
    else if(type == tetrominos::T){
        row = 2;
        col = 3;

        charvec = new char*[row]; 
        for(int i = 0;i<row;i++)
            charvec[i] = new char[col];
        
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                if((i == 1 && j == 0) || (i == 1 && j == 2))
                    charvec[i][j] = '.';
                else
                    charvec[i][j] = 'T';
            }
        }
    }
    else if(type == tetrominos::J){
        row = 3;
        col = 2;

        charvec = new char*[row]; 
        for(int i = 0;i<row;i++)
            charvec[i] = new char[col];
        
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                if((i == 0 && j == 0) || (i == 1 && j == 0))
                    charvec[i][j] = '.';
                else
                    charvec[i][j] = 'J';
            }
        }
    }
    else if(type == tetrominos::L){
        row = 3;
        col = 2;

        charvec = new char*[row]; 
        for(int i = 0;i<row;i++)
            charvec[i] = new char[col];
        
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                if((i == 0 && j == 1) || (i == 1 && j == 1))
                    charvec[i][j] = '.';
                else
                    charvec[i][j] = 'L';
            }
        }
    }
    else if(type == tetrominos::S){
        row = 2;
        col = 3;

        charvec = new char*[row]; 
        for(int i = 0;i<row;i++)
            charvec[i] = new char[col];
        
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                if((i == 0 && j == 0) || (i == 1 && j == 2))
                    charvec[i][j] = '.';
                else
                    charvec[i][j] = 'S';
            }
        }
    }
    else if(type == tetrominos::Z){
        row = 2;
        col = 3;

        charvec = new char*[row]; 
        for(int i = 0;i<row;i++)
            charvec[i] = new char[col];
        
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                if((i == 0 && j == 2) || (i == 1 && j == 0))
                    charvec[i][j] = '.';
                else
                    charvec[i][j] = 'Z';
            }
        }
    }
}

void Tetromino::rotateCW(){
    char **result;
    result = new char*[col];
    for(int i = 0;i<col;i++)
        result[i] = new char[row];

    for (int i = 0; i < row;++i) {
        for (int j = 0;j<col;++j) {
            result[j][row - 1 -i] = charvec[i][j];
        }
    }
    for(int i = 0;i<row;i++){
        delete[] charvec[i];
    }
    delete[] charvec;
    charvec = result;
    int temp;
    temp = row;
    row = col;
    col = temp;
}

Tetromino::Tetromino(tetrominos ttype){ //takes an enum type and represent constructs tetromino 
    type = ttype;
    set2dtetro();
}

int Tetromino::getcol() const{
    return col;
}

int Tetromino::getrow() const{
    return row;
}

char** Tetromino::getvector(){
    return charvec;
}

void Tetromino::print() const{ // prints tetrominos to the console
    int flag;
    for(int i = 0;i<row;i++){
        flag = 0;
        for(int j = 0;j<col;j++){
            if(charvec[i][j] != ' ' && charvec[i][j] != '.'){
                cout << charvec[i][j];
                flag = 1;
            }
            else if(charvec[i][j] == '.')
                cout << ' ';
        }
        if(flag == 1)
            cout << endl;
    }
    cout<< endl;
}



