

public class Tetromino{
    private char[][] charvec;
    private int row;
    private int col;
    private char type; // includes type of tetromino (I,O,T,J...)
    private int position; // includes rotation info of each tetromino
    public Tetromino(char ttype){
        type = ttype;
        position = 0;
        setvector();
    }
    public char gettype(){
        return type;
    }
    public int getposition() {
        return position;
    }
    public void setposition(int i ){
        position = i;
    }
    
    public void print(){ // prints tetrominos to the console
        int flag;
        for (int i = 0;i<row;i++) {
            flag = 0;
            for (int j = 0;j<col;j++) {
                if(charvec[i][j] != ' ' && charvec[i][j] != '.'){
                    System.out.print(charvec[i][j]);
                    flag = 1;
                }
                else if(charvec[i][j] == '.')
                    System.out.print(" ");
            }
            if(flag == 1)
                System.out.println();
        }
        System.out.println();
    }
    public int getrow(){ return row;}
    public int getcol(){ return col;}
    public char[][] getvector(){
        return charvec;
    }
    public void setvector(){
        if(type == 'I'){
            row = 1;
            col = 4;
            charvec = new char[][]{
                {'I','I','I','I'}
            };
        }
        else if(type == 'O'){
            row = 2;
            col = 2;
            charvec = new char[][]{
                        {'O','O'},
                        {'O','O'}};
        }
        
        else if(type == 'T'){
            row = 2;
            col = 3;
            charvec = new char[][]{ 
                        {'T','T','T'},
                        {'.','T','.'}};
        }
        else if(type == 'J'){
            row = 3;
            col = 2;
            charvec = new char[][]{ 
                        {'.','J'},
                        {'.','J'},
                        {'J','J'}};
        }
        else if(type == 'L'){
            row = 3;
            col = 2;
            charvec = new char[][]{ 
                        {'L','.'},
                        {'L','.'},
                        {'L','L'}};
        }
        else if(type == 'S'){
            row = 2;
            col = 3;
            charvec = new char[][]{ 
                        {'.','S','S'},
                        {'S','S','.'}};
        }
        else if(type == 'Z'){
            row = 2;
            col = 3;
            charvec = new char[][]{ 
                        {'Z','Z','.'},
                        {'.','Z','Z'}};
        }
    }
    public void rotateCW(){
        char[][] result = new char[col][row];
        
        for (int i = 0; i < col; i++) {
            char[] temp = new char[row];
            int ti = 0;
            for (int j = row - 1; j >= 0; j--) {
                temp[ti] = charvec[j][i];
                ti++;
            }
            for(int m = 0;m<row;m++){
                result[i][m] = temp[m];
            }
        }
        charvec = result;
        int temprow;
        temprow = row;
        row = col;
        col = temprow;
    }
    
    public int rotate(char dir){// takes rotate direction and rotates vector with rotateCW func.
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

    public boolean canFit(Tetromino relative) { // takes other tetromino and chechks whether they're fit together or not
    if(relative.type == 'O'){
        if(type == 'O')
            return true;
        if(type == 'T'){
            if(position == 3)
                return true;
            else
                return false;
        }
        else if(type == 'J'){
            if(position == 2)
                return true;
            else
                return false;
        }
        else if(type == 'L'){
            if(position == 0)
                return true;
            else
                return false;
        }
        else if(type == 'S'){
            if(position == 0 || position==2)
                return true;
            else
                return false;
        }
        else if(type == 'Z'){
            if(position == 1 || position==3)
                return true;
            else
                return false;
        }
        else if(type == 'I'){
            if(position == 1 || position==3)
                return true;
            else
                return false;
        }
    }

        if(relative.type == 'T' && relative.position == 0){
            if(type == 'T'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'J'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'T' && relative.position == 1){
            if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == 'T' && relative.position == 2){
            if(type == 'T'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'T' && relative.position == 3){
            if(type == 'T'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'J'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'J' && relative.position == 0){
            if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == 'J' && relative.position == 1){
            if(type == 'J'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'J' && relative.position == 2){
            if(type == 'J'){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'J' && relative.position == 3){
            if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'L' && relative.position == 0){
            if(type == 'L'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'L' && relative.position == 1){
            if(type == 'L'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'L' && relative.position == 2){
            if(type == 'L'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'L' && relative.position == 3){
            if(type == 'L'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'S' && (relative.position == 0 || relative.position == 2)){
            if(type == 'S'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position==1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position==0 || position==0)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'S' && (relative.position == 1 || relative.position == 3)){
            if(type == 'S'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == 'Z' && (relative.position == 0 || relative.position == 2)){
            if(type == 'Z'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
        }

        if(relative.type == 'Z' && (relative.position == 1 || relative.position == 3)){
            if(type == 'Z'){
                if(position == 1)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position==0 || position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'I'){
                if(position==1 || position == 3)
                    return true;
                else
                    return false;
            }
        }
        if(relative.type == 'I' && (relative.position == 0 || relative.position == 2)){
            if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 0)
                    return true;
                else
                    return false;
        }
    }

    if(relative.type == 'I' && (relative.position == 1 || relative.position == 3)){
            if(type == 'I'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'O'){
                return true;
            }
            else if(type == 'T'){
                if(position == 3)
                    return true;
                else
                    return false;
            }
            else if(type == 'J'){
                if(position == 2)
                    return true;
                else
                    return false;
            }
            else if(type == 'S'){
                if(position == 0 || position==2)
                    return true;
                else
                    return false;
            }
            else if(type == 'Z'){
                if(position == 1 || position==3)
                    return true;
                else
                    return false;
            }
            else if(type == 'L'){
                if(position == 0)
                    return true;
                else
                    return false;
            }
    }

    return false;
}

    public static void main(String[] args){
        Tetromino mytetro = new Tetromino('J');
        mytetro.print();

        mytetro.rotateCW();
        mytetro.print();
    }
}