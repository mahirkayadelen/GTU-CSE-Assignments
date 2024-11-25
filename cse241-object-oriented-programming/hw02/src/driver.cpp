#include"tetris.h"

int main(){
    char see;
    vector<Tetromino>tetrominovec;
    tetrominovec.push_back(tetrominos::T);
    //tetrominovec.push_back(tetrominos::S);
    Tetris mytetris(10,10);

    cout << "(+)tetro.h print function of T tetromino:"<<endl;
    tetrominovec[0].print();

    cout << "(+)tetro.h rotate(L) used tetromino:"<<endl;
    tetrominovec[0].rotate('L');
    tetrominovec[0].print();

    cout <<"(+)tetro.h canFit result:"<< tetrominovec[0].canFit(tetrominovec[0])<<endl<<endl;

    cout << "(+)tetris.h initBoard function and after Draw function:"<<endl;
    mytetris.initBoard();
    mytetris.Draw();

    cout << "(+)tetris.h Add function after Draw:"<<endl;
    mytetris.Add('T');
    mytetris.Draw();

    cout << "press enter any character to see animate function";
    cin >> see;
    
    cout <<"(+)tetris.h Animate function:"<<endl;
    mytetris.Animate(tetrominovec);
    
    cout <<endl<< "(+)tetris.h Fit function after Draw:"<<endl;
    mytetris.Fit(tetrominovec);
    mytetris.Draw();

    cout <<"(+)tetris.h Animate function:"<<endl;
    mytetris.Animate(tetrominovec);
}