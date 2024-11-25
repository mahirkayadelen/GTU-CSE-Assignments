#include<iostream>
#include<vector>

using namespace std;

enum class tetrominos  {I,O,T,J,L,S,Z};

class Tetromino{
    public:
        Tetromino(tetrominos); //takes an enum type and represent constructs tetromino 
        tetrominos gettype() const;
        int getposition() const;
        vector<vector<char>> getvector();
        void setposition(int);
        void print() const; // prints tetrominos to the console
        int rotate(char dir); // takes rotate direction and rotates vector with rotateCW func
        void setvector(); // fills char vectors depends on tetrominos enum
        bool canFit(const Tetromino &relative) const; // takes other tetromino and chechks whether they're fit together or not
        void rotateCW(); // transposing and reversing = rotates clockwise 90degree to a vector
        int shiftleft(); // shifts vector 1 column left
        int shiftdown(); // shifts vector 1 row down
        

    private:
        vector<vector<char>> charvec;
        tetrominos type; // includes type of tetromino (I,O,T,J...)
        int position; // includes rotation info of each tetromino
};

void createBoard(vector<vector<char>> &board,vector<Tetromino> &tetrovec); // fill result board with tetrominos
void setvector(vector<Tetromino> &tetrovec,int inp); //takes inputs and fills vector arrays
void printBoard(const vector<vector<char>> &board); //prints final board
void cleanEmptyColumns(vector<vector<char>> &board); // removes fully empty columns and shift vector to left 
void fitGaps(vector<vector<char>> &board); // removes spaces between letters
