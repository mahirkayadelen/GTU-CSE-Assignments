#include<iostream>
#include<vector>

using namespace std;

enum class tetrominos  {I,O,T,J,L,S,Z};

class Tetromino{
    public:
        Tetromino(tetrominos); //takes an enum type and represent constructs tetromino 
        char** getvector();
        int getcol() const;
        int getrow() const;
        void print() const; // prints tetromino to the console
        void set2dtetro(); // fills char vectors depends on tetrominos enum
        void rotateCW(); // transposing and reversing = rotates clockwise 90degree to a vector
    private:
        char **charvec; // includes 
        tetrominos type; // includes type of tetromino (I,O,T,J...)
        int row; // includes number of row tetromino array
        int col; // includes number of column tetromino array
};


