#include<iostream>
#include<vector>
#include<unistd.h>
#include"tetro.h"
#include<time.h>
#include<cstdlib>
using namespace std;
namespace Mahir{
    class Tetris{
        public:
            Tetris(int x,int y); // Constructs the class based on x and y inputs
            void Add(char inp); //  Adds the entered input to the board
            void Draw() const; // prints the board
            void initBoard(); // creates empty gameboard surrounded with X
            int Animate(Tetromino &a);
            int getcol() const;
            int getrow() const;
            int gettotal() const;
            void operator+=(Tetromino add);
        private:
            char **gameboard;
            int col; // column of the tetris board
            int bottomcolumn; // keeps the current column in the bottom row
            int row; // row of the tetris board
            int total; // keeps the number of total tetrominos added
    };
}

using namespace Mahir;