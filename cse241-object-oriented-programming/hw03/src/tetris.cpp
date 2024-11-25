#include"tetris.h"

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
    
    gameboard = new char*[row]; // for memory allocation every row of board
    for(int i = 0;i<row;i++){ // for memory allocate every column of board
        gameboard[i] = new char[col];
    }

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
    initBoard(); // fills empty gameboard surrounded by 'X'
    bottomcolumn=1;
}

void Tetris::Draw() const{ // prints gameboard to console
    cout<<endl;
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

void Tetris::operator+=(Tetromino add){
    for(int i  =0;i<add.getrow();i++){ // writes the current tetro to the top mid of gameboard
        for(int j = 0;j<add.getcol();j++){
            gameboard[1+i][(getcol()/2)+j-1] = add.getvector()[i][j];
        }
    }
}

int Tetris::Animate(Tetromino &a){
    char rotatedir,movedir;
    int rotatetimes,movetimes,isValid,tetrocolumn;
    Draw();

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

        cout << "\nPlease enter move times:";
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
                        Draw();
                        cout << "Game Over"<<endl;
                        return 0;
                    }
                }
            }
        }
        system("clear");
        Draw();
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
