#ifndef AbstractTetris1
#define AbstractTetris1
#include"tetromino.h"
#include"deque"
using namespace std;
namespace Mahir{
class AbstractTetris{
    private:

    public:
        virtual int numberOfMoves() const = 0; 
        virtual void draw() const = 0;
        virtual void operator+=(Tetromino add) = 0;
        virtual int animate(Tetromino &a) = 0;
        virtual bool writeToFile(const string & filename) = 0;
        virtual bool readFromFile(const string & filename) = 0;
};

class ErrorFile {};
}


#endif