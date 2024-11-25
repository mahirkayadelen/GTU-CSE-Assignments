#include"tetris.h"

void setvector(vector<Tetromino> &tetrovec,int inp){ //takes inputs and fills vector arrays
    char cinp;
    vector<char>inpvec;
    cout << "What are the types ?"<<endl;
    for(int i = 0;i<inp;i++){
        cin >> cinp;
        if(cinp == 'I' ||cinp == 'O' ||cinp == 'T' ||cinp == 'J' ||cinp == 'L' ||cinp == 'S' ||cinp == 'Z' ) {
            inpvec.push_back(cinp);
        }
        else{
            i-=1;
            cout << "Wrong input try again." << endl;
        }
        cin.ignore();
    }
    for(int i = 0;i<inp;i++){ // setting tetromino vectors
        if(inpvec[i] == 'I')
            tetrovec.push_back(tetrominos::I);
        else if(inpvec[i] == 'O')
            tetrovec.push_back(tetrominos::O);
        else if(inpvec[i] == 'T')
            tetrovec.push_back(tetrominos::T);
        else if(inpvec[i] == 'J')
            tetrovec.push_back(tetrominos::J);
        else if(inpvec[i] == 'L')
            tetrovec.push_back(tetrominos::L);
        else if(inpvec[i] == 'S')
            tetrovec.push_back(tetrominos::S);
        else if(inpvec[i] == 'Z')
            tetrovec.push_back(tetrominos::Z);
    }
}

void Tetromino::setvector(){ // fills char vectors depends on tetrominos enum
    if(type == tetrominos::I){
        charvec = {{'I','I','I','I'}};
    }
    else if(type == tetrominos::O){
        charvec = { {'O','O'},
                    {'O','O'}};
    }
    else if(type == tetrominos::T){
        charvec = { {'T','T','T'},
                    {'.','T','.'}};
    }
    else if(type == tetrominos::J){
        charvec = { {'.','J'},
                    {'.','J'},
                    {'J','J'}};
    }
    else if(type == tetrominos::L){
        charvec = { {'L','.'},
                    {'L','.'},
                    {'L','L'}};
    }
    else if(type == tetrominos::S){
        charvec = { {'.','S','S'},
                    {'S','S','.'}};
    }
    else if(type == tetrominos::Z){
        charvec = { {'Z','Z','.'},
                    {'.','Z','Z'}};
    }
}

int Tetromino::shiftdown(){ // shifts vector 1 row down
    int flag=0;
    
    for(int i = 0;i<charvec.size();i++){ // if there is no empty row flag1
        if(charvec[3][i] != ' ')
            flag+=1;
    }
    if(flag == 0){ // if there is empty row shift vector 1 row down
        char temp[4];
        for(int i = 0;i<charvec.size();i++){ // take last row
            temp[i] = charvec[3][i];
        }

        for(int i=0;i<charvec.size();i++) 
        {
            for(int j = charvec.size()-1;j>0;j--){ // shift 1 row except last row
                charvec[j][i] = charvec[j-1][i];
            }
        }
        for(int i = 0;i<charvec.size();i++){ // fill first row with last row
            charvec[0][i] = temp[i];
        }
        return 1;
    }
    return 0; // if there is no any empty row
}

int Tetromino::shiftleft(){ // shifts vector 1 column left
    int flag=0;
    
    for(int i = 0;i<charvec.size();i++){ // if there is no empty column flag>1
        if(charvec[i][0] != ' ')
            flag+=1;
    }
    if(flag == 0){ // if there is empty column, shift vector 1 column left
        char temp[4];
        for(int i = 0;i<charvec.size();i++){ // take first column
            temp[i] = charvec[i][0];
        }

        for(int i=0;i<charvec.size();i++)
        {
            for(int j = 0;j<charvec.size()-1;j++){ // shift 1 column except last column
                charvec[i][j] = charvec[i][j+1];
            }
        }
        for(int i = 0;i<charvec.size();i++){
            charvec[i][3] = temp[i]; //fill last row with temp(first row)
        }
        return 1;
    }
    else
        return 0; // if there is no any empty column
}

void Tetromino::rotateCW(){
    vector<vector<char>> result;
    for (int i = 0; i < charvec[0].size(); i++) {
        vector<char> row;
        for (int j = charvec.size() - 1; j >= 0; j--) {
            row.push_back(charvec[j][i]);
        }
        result.push_back(row);
    }
    charvec = result;
}

int Tetromino::rotate(char dir){ // takes rotate direction and rotates vector with rotateCW func.
    if(position == 0){
        if(dir == 'L'){
            position = 3;
            rotateCW();
            rotateCW();
            rotateCW();
        }
        else if(dir == 'R'){
            position = 1;
            rotateCW();
        }
        else
            return -1;
    }
    else if(position == 1){
        if(dir == 'L'){
            position = 0;
            rotateCW();
            rotateCW();
            rotateCW();
        }
        else if(dir == 'R'){
            position = 2;
            rotateCW();
        }
        else
            return -1;
    }
    else if(position == 2){
        if(dir == 'L'){
            position = 1;
            rotateCW();
            rotateCW();
            rotateCW();
        }
        else if(dir == 'R'){
            position = 3;
            rotateCW();
        }
        else
            return -1;
    }
    else if(position == 3){
        if(dir == 'L'){
            position = 2;
            rotateCW();
            rotateCW();
            rotateCW();
        }
        else if(dir == 'R'){
            position = 0;
            rotateCW();
        }
        else
            return -1;
    }
    return 1;
}

Tetromino::Tetromino(tetrominos ttype){ //takes an enum type and represent constructs tetromino 
    type = ttype;
    position = 0;
    setvector();
}

vector<vector<char>> Tetromino::getvector(){
    return charvec;
}

tetrominos Tetromino::gettype() const{
    return type;
}

int Tetromino::getposition() const{
    return position;
}

void Tetromino::print() const{ // prints tetrominos to the console
    int flag;
    for(int i = 0;i<charvec.size();i++){
        flag = 0;
        for(int j = 0;j<charvec[i].size();j++){
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

bool Tetromino::canFit(const Tetromino &relative) const{ // takes other tetromino and chechks whether they're fit together or not
    if(relative.type == tetrominos::O){
        if(type == tetrominos::O)
            return true;
        if(type == tetrominos::T){
            if(position == 3)
                return true;
            else
                return false;
        }
        else if(type == tetrominos::J){
            if(position == 2)
                return true;
            else
                false;
        }
        else if(type == tetrominos::L){
            if(position == 0)
                return true;
            else
                false;
        }
        else if(type == tetrominos::S){
            if(position == 0 || position==2)
                return true;
            else
                false;
        }
        else if(type == tetrominos::Z){
            if(position == 1 || position==3)
                return true;
            else
                false;
        }
        else if(type == tetrominos::I){
            if(position == 1 || position==3)
                return true;
            else
                false;
        }
    }

        if(relative.type == tetrominos::T && relative.position == 0){
            if(type == tetrominos::T){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::J){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::T && relative.position == 1){
            if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == tetrominos::T && relative.position == 2){
            if(type == tetrominos::T){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::T && relative.position == 3){
            if(type == tetrominos::T){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::J){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::J && relative.position == 0){
            if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == tetrominos::J && relative.position == 1){
            if(type == tetrominos::J){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::J && relative.position == 2){
            if(type == tetrominos::J){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::J && relative.position == 3){
            if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::L && relative.position == 0){
            if(type == tetrominos::L){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::L && relative.position == 1){
            if(type == tetrominos::L){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::L && relative.position == 2){
            if(type == tetrominos::L){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::L && relative.position == 3){
            if(type == tetrominos::L){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::S && (relative.position == 0 || relative.position == 2)){
            if(type == tetrominos::S){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position==1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position==0 || position==0)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::S && (relative.position == 1 || relative.position == 3)){
            if(type == tetrominos::S){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == tetrominos::Z && (relative.position == 0 || relative.position == 2)){
            if(type == tetrominos::Z){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == tetrominos::Z && (relative.position == 1 || relative.position == 3)){
            if(type == tetrominos::Z){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position==0 || position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::I){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == tetrominos::I && (relative.position == 0 || relative.position == 2)){
            if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 0)
                    return true;
                else
                    return false;
        }
    }

    if(relative.type == tetrominos::I && (relative.position == 1 || relative.position == 3)){
            if(type == tetrominos::I){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::O){
                return true;
            }
            else if(type == tetrominos::T){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::J){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::S){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::Z){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == tetrominos::L){
                if(position == 0)
                    return true;
                else
                    return false;
            }
    }

    return false;
}

void Tetromino::setposition(int i){
    position = i;
};

void createBoard(vector<vector<char>> &board, vector<Tetromino> &tetrovec){// fill result board with tetrominos
    if(tetrovec[0].gettype() == tetrominos::T || tetrovec[0].gettype() == tetrominos::I|| tetrovec[0].gettype() == tetrominos::Z){
        tetrovec[0].rotateCW();
        tetrovec[0].rotateCW();
        tetrovec[0].rotateCW(); 
    }
    else if(tetrovec[0].gettype() == tetrominos::J){
        tetrovec[0].rotateCW();
        tetrovec[0].rotateCW();
    }
    for(int row = 0;row<4;row++){
        for(int j = 0;j<tetrovec.size();j++){
            vector<vector<char>> temp(4);
            temp = tetrovec[j].getvector();
            for(int d=0;d<4;d++){
                board[row].push_back(temp[row][d]);
            }
        }
    }
}

void printBoard(const vector<vector<char>> &board){//prints final board
    for(int i = 0;i<4;i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == '.')
                cout <<' ';
            else
                cout << board[i][j];
        }
        cout << endl;
    }
}

void cleanEmptyColumns(vector<vector<char>> &board){// removes fully empty columns and shift vector to left 
    int flag;
    for(int j = 0;j<board[0].size()-1;j++){
        flag = 0;
        for(int r = 0;r<4;r++){
            if(board[r][j] != ' ')
                flag = 1;
        }
        if(flag == 0){
            for(int row = 0;row<4;row++){
                for(int tj = j;tj<board[0].size()-1;tj++){
                    board[row][tj] = board[row][tj+1];
                }
            }
        }
    }
}

int fitGaps(vector<vector<char>> &board){ // removes spaces between letters
    int flag;
    int returnflag = 0;
    for(int j=1;j<board[0].size()-1-1;j++){
        flag = 0;
        for(int i = board.size()-6;i<board.size()-1;i++){
            if((board[i][j]>=65) && (board[i][j]<=90) && (board[i][j+1]>=65) && (board[i][j+1]<=90))
                flag +=1;
        }
        if(flag == 0){
            for(int i = board.size()-6;i<board.size()-1;i++){
                if(board[i][j+1]>=65 && (board[i][j+1]<=90)){
                    board[i][j] = board[i][j+1];
                    returnflag+=1;
                }
            }
            for(int c = j+1;c<board[0].size()-1-1;c++){
                for(int r = board.size()-6;r<board.size()-1;r++){
                    board[r][c] = board[r][c+1];
                    // if(board[r][c+2] == 'X'){ // added
                    //     for(int i = 1;i<board.size()-1;i++)
                    //     board[i][c+1] == ' ';
                    // }
                }
            }
            for(int i = 1;i<board.size()-1;i++){ //if there is any shifted gap, last row will be  ' '(for fix bug) 
                board[i][board[0].size()-2] = ' ';
            }
            //returnflag+=1; // ADDED
        }
    }
    if(returnflag!=0)
        return returnflag;
    else
        return 0;
}