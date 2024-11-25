#include<iostream>
#include<vector>
#include<unistd.h>
#include"tetro.h"
#include<time.h>
using namespace std;

class Tetris{
    public:
        Tetris(int x,int y); // Constructs the class based on x and y inputs
        void Add(char inp); //  Adds the entered input to the board
        void Fit(vector<Tetromino>&);
        void Draw() const; // prints the board
        void initBoard(); // creates empty gameboard surrounded with X
        void Animate(vector<Tetromino>&); //animates the added tetromino dropping to the bottom of the board
        int getcol() const;
        int getrow() const;
        vector<Tetromino>& gettetrosvector(); // get the vector and its reference
        int gettotal() const;
        int getbottomc();
    private:
        vector<vector<char>> gameboard; // tetris board
        vector<Tetromino>tetros; // includes added tetrominos
        int col; // column of the tetris board
        int bottomcolumn; // keeps the current column in the bottom row
        int row; // row of the tetris board
        int total; // keeps the number of total tetrominos added
};




