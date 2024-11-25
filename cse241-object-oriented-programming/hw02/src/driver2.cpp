#include"tetris.h"

int main(){
    srand(time(0));
    int x,y;
    int endctr=0;
    cout << "Please enter the dimensions of the board (first input column, second input row)"<<endl;
    cin >> x;
    cin >> y;

    cout << "Game starting.."<<endl;
    sleep(1);

    Tetris mytetris(x,y);
    mytetris.initBoard();

    while(endctr <= (x-2)){
        char tetroinp;
        cout << "Tetromino type (I, O, T, J, L, S, Z).You may enter R for random Tetromino, Q for quit. : ";
        cin >> tetroinp;
        if(tetroinp == 'Q'){
            cout <<"Exiting..."<<endl;
            sleep(1);
            return 1;
        }
        else if(tetroinp != 'I' && tetroinp != 'O' && tetroinp != 'T' && tetroinp != 'J' && tetroinp != 'L' && tetroinp != 'S' && tetroinp != 'Z' && tetroinp != 'R' ){
            cout << "Wrong input! please try again."<<endl;
            continue;
        }
        if(tetroinp == 'R'){
            switch(rand() % 7){
                case 0:
                    tetroinp = 'I';
                    break;
                case 1:
                    tetroinp = 'O';
                    break;
                case 2:
                    tetroinp = 'T';
                    break;
                case 3:
                    tetroinp = 'J';
                    break;
                case 4:
                    tetroinp = 'L';
                    break;
                case 5:
                    tetroinp = 'S';
                    break;
                case 6:
                    tetroinp = 'Z';
                    break;
            }
        }
        mytetris.Add(tetroinp);
        if(mytetris.gettetrosvector()[(mytetris.gettotal())-1].getvector()[0].size() + mytetris.getbottomc() > x-1){
            break;
        }
        mytetris.Animate(mytetris.gettetrosvector());
    }
    cout << "Game Over"<<endl;
}