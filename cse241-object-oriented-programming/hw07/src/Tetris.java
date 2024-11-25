import java.util.Vector;
public class Tetris {
    private char[][] gameboard;
    private Vector<Tetromino> tetros;
    private int col;
    private int row;
    private int bottomcolumn;
    private int total;
    /**
     * constructs the class based on x and y inputs
     * x takes column and y takes row
     * @param x
     * @param y
     */
    public Tetris(int x,int y){// Constructs the class based on x and y inputs
        total = 0;
        row = y;
        col = x;
        gameboard = new char[row][col];
        tetros = new Vector<Tetromino>();
        bottomcolumn = 1;
        initBoard();
    }
    public int getcol(){return col;}
    public int getrow(){return row;}
    public int gettotal(){return total;}
    public int getbottomc(){return bottomcolumn;}

    public Vector<Tetromino> gettetrosvector(){return tetros;}
    /**
     * Prints the current gameboard to the console
     */
    public void Draw(){
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++){
                if(gameboard[i][j] != '.')
                    System.out.print(gameboard[i][j]);
                else
                    System.out.print(' ');
            }
            System.out.println();
        }
    }
    /**
     * fills empty gameboard surrounded with X's 
     */
    void initBoard(){
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

    /**
     * Adds tetromino to the gameboard with input parameter
     * @param inp
     */
    void Add(char inp){
        total++;
        tetros.add(new Tetromino(inp));
    
        for(int i  =0;i<tetros.get(total-1).getrow();i++){ // writes the current tetro to the board
            for(int j = 0;j<tetros.get(total-1).getcol();j++){
                gameboard[1+i][(getcol()/2)+j-1] = tetros.get(total-1).getvector()[i][j];
            }
        }
    }

    /**
     * checks whether tetromino can fit with previous one, if it is not rotates till best position
     */
    public void Fit(){
        if(total == 1){// for fix if there is any gap between wall and first tetromino special cases
            if(tetros.get(total-1).gettype() == 'T' ||
            tetros.get(total-1).gettype() == 'I'    ||
            tetros.get(total-1).gettype() == 'Z'){
                tetros.get(total-1).rotateCW();
                tetros.get(total-1).rotateCW();
                tetros.get(total-1).rotateCW();
                tetros.get(total-1).setposition(3);
            }
            else if(tetros.get(total-1).gettype() == 'J'){// for fix if there is any gap between wall and first tetromino special cases
                tetros.get(total-1).rotateCW();
                tetros.get(total-1).rotateCW();
                tetros.get(total-1).setposition(2);
            }
        }

        else{
            while(!tetros.get(total-1).canFit(tetros.get(total-2))){ // checks whether previous and this tetromino fit with canFit func. if not, fit them with rotate func
                tetros.get(total-1).rotate('R');
            }
        }
        for(int i  =0;i<tetros.get(total-1).getrow();i++){ // fill at top-mid to tetromino to the board
            for(int j = 0;j<tetros.get(total-1).getcol();j++){
                gameboard[1+i][(getcol()/2)+j-1] = tetros.get(total-1).getvector()[i][j];
            }
        }
        
    }
    /**
     * Animates shifts added tetromino till the bottom of the gameboard
     */
    public void Animate(){
        for(int i  =0;i<tetros.get(total-1).getrow();i++){ // clear top mid
            for(int j = 0;j<tetros.get(total-1).getcol();j++){
                gameboard[1+i][(getcol()/2)+j-1] = ' ';
            }
        }
        Draw();
        Fit();

        for(int i  =0;i<tetros.get(total-1).getrow();i++){ // clear top mid
            for(int j = 0;j<tetros.get(total-1).getcol();j++){
                gameboard[1+i][(getcol()/2)+j-1] = ' ';
            }
        }
        for(int r= 1;r<getrow()-tetros.get(total-1).getrow();r++){//shifts tetromino to the bottom line by line
            for(int i  =0;i<tetros.get(total-1).getrow();i++){ // writes the current tetro to the board
                for(int j = 0;j<tetros.get(total-1).getcol();j++){
                    gameboard[r+i][bottomcolumn+j] = tetros.get(total-1).getvector()[i][j];
                }
            }
        
            System.out.print("\033[H\033[2J");
            System.out.flush();
            Draw();
            try {
                Thread.sleep(300);
            } 
            catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(r!=(row-tetros.get(total-1).getrow()-1)){// if its last row,it will not erase tetro bcz its shifted to bottom
                for(int i  =0;i<tetros.get(total-1).getrow();i++){ // erase the current tetro to the board
                    for(int j = 0;j<tetros.get(total-1).getcol();j++){
                        gameboard[r+i][bottomcolumn+j] = ' ';
                    }
                }
            }
        }
        int gapctr=0;
        gapctr = fitGaps(); // if there is any gaps between the tetrominos. merge them.
        bottomcolumn+= tetros.get(total-1).getcol(); // increases bottomcolumn with column size of last added tetromino
        bottomcolumn -= gapctr;
        System.out.print("\033[H\033[2J");
        System.out.flush();
        Draw();
    }
    /**
     * If there is any gap and if it could fix fixes merges tetrominos
     */
    public int fitGaps(){
        int flag;
        int returnflag = 0;
        for(int j=1;j<col-1-1;j++){
            flag = 0;
            for(int i = row-6;i<row-1;i++){
                if((gameboard[i][j]>=65) && (gameboard[i][j]<=90) && (gameboard[i][j+1]>=65) && (gameboard[i][j+1]<=90))
                    flag +=1;
            }
            if(flag == 0){
                for(int i = row-6;i<row-1;i++){
                    if(gameboard[i][j+1]>=65 && (gameboard[i][j+1]<=90)){
                        gameboard[i][j] = gameboard[i][j+1];
                        returnflag+=1;
                    }
                }
                for(int c = j+1;c<col-1-1;c++){
                    for(int r = row-6;r<row-1;r++){
                        gameboard[r][c] = gameboard[r][c+1];
                    }
                }
                for(int i = 1;i<row-1;i++){  
                    gameboard[i][col-2] = ' ';
                }
            }
        }
        if(returnflag!=0)
            return returnflag;
        else
            return 0;
    }
}
