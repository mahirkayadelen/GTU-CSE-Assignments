#ifndef TetrisArray1D
#define TetrisArray1D
using namespace Mahir;

namespace Array{
class TetrisArray : public AbstractTetris{
    private:
        int totalmoves;
        char *gameboard;
        int col; // column of the tetris board
        int bottomcolumn; // keeps the current column in the bottom row
        int row; // row of the tetris board
        int total; // keeps the number of total tetrominos added
    public:
        int numberOfMoves()const;
        TetrisArray(int colinp,int rowinp);
        void draw() const;
        void operator+=(Tetromino add);
        int animate(Tetromino &a);
        int getcol() const {return col;};
        void initBoard();
        int getrow() const {return row;};
        int gettotal() const {return total;};
        bool writeToFile(const string & filename)override;
        bool readFromFile(const string & filename)override;
};
}




#endif