#ifndef _TETRIS_VECTOR_
#define _TETRIS_VECTOR_




using namespace Mahir;

namespace Vector{
class TetrisVector : public AbstractTetris{
    public:
        TetrisVector(int colinp,int rowinp);
        void draw() const override;
        void operator+=(Tetromino add) override;
        int animate(Tetromino &a) override;
        void initBoard();
        int getcol() const;
        int getrow() const;
        bool writeToFile(const string & filename)override ;
        bool readFromFile(const string & filename) override;
        int numberOfMoves()const;
    private:
        int totalmoves;
        vector<vector<char>> gameboard; // tetris board
        int col; // column of the tetris board
        int row; // row of the tetris board

};
}

#endif