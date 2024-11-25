#ifndef _TETRIS_ADAPTER_
#define _TETRIS_ADAPTER_

using namespace Mahir;

namespace Adapter{
    template<class T>
    class TetrisAdapter : public AbstractTetris{
        public:
        TetrisAdapter(int colinp,int rowinp);
        void draw() const override;
        void operator+=(Tetromino add) override;
        int animate(Tetromino &a) override;
        void initBoard();
        int getcol() const;
        int getrow() const;
        virtual bool writeToFile(const string & filename) override{return true;};
        virtual bool readFromFile(const string & filename)override {return true;};
        int numberOfMoves()const;
    private:
        int totalmoves;
        T gameboard; // tetris board
        int col; // column of the tetris board
        int row; // row of the tetris board
    };
    template class TetrisAdapter<vector<vector<char>>>;
}






#endif