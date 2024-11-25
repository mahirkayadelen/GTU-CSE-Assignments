#include"AbstractTetris.h"
#include"TetrisArray1D.h"
#include"TetrisVector.h"
#include"TetrisAdapter.cpp"

using namespace Mahir;
using namespace Array;
using namespace Vector;
using namespace Adapter;

int main(){
    char inp;
    Tetromino temp(tetrominos::Z);
    Tetromino temp2(tetrominos::J);
    Tetromino temp3(tetrominos::I);

    cout << "Tetris Array objesi olusturup draw fonksiyonu çağırıyorum:" << endl;
    TetrisArray a(10,10);
    a.draw();

    cout << "+= operatorü ile Z tetrominosu ekleyip draw çağırıyorum:" << endl;
    a += temp;
    a.draw();

    cout << "animate fonksiyonu çağırıyorum ve Z yi animate ediyorum:" << endl;
    a.animate(temp);

    cout << "numberOfMoves fonksiyonu degeri:" << a.numberOfMoves()<<endl;

    cout << "writeToFile fonksiyonu ile suanki boardu mahir.txt ye yazıyorum"<<endl;
    a.writeToFile("mahir.txt");

    cout << "TetrisVector 'e geçmek için bir tuşa basın.";
    cin >> inp;


    cout << "Tetris Vector objesi olusturup draw fonksiyonu çağırıyorum:" << endl;
    TetrisVector b(10,10);
    b.draw();

    cout << "+= operatorü ile J tetrominosu ekleyip draw çağırıyorum:" << endl;
    b += temp2;
    b.draw();

    cout << "animate fonksiyonu çağırıyorum ve J yi animate ediyorum:" << endl;
    b.animate(temp2);

    cout << "numberOfMoves fonksiyonu degeri:" << b.numberOfMoves()<<endl;

    cout << "readFromFile fonksiyonu ile mahir.txt'deki boardu çekiyorum ve drawlıyorum:"<<endl;

    b.readFromFile("mahir.txt");
    b.draw();


    cout << "TetrisAdapter 'e geçmek için bir tuşa basın.";
    cin >> inp;

    cout << "TetrisAdapter objesi olusturup draw fonksiyonu çağırıyorum:" << endl;
    TetrisAdapter<vector<vector<char>>> c(10,10);
    c.draw();

    cout << "+= operatorü ile I tetrominosu ekleyip draw çağırıyorum:" << endl;
    c += temp3;
    c.draw();

    cout << "animate fonksiyonu çağırıyorum ve I yi animate ediyorum:" << endl;
    c.animate(temp3);

    cout << "numberOfMoves fonksiyonu degeri:" << c.numberOfMoves()<<endl;

}